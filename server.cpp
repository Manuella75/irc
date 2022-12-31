/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettien <mettien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:54:49 by mettien           #+#    #+#             */
/*   Updated: 2022/12/31 06:17:19 by mettien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/server.hpp"
Server::Server(std::string input_port, std::string input_passwd)
{
	if (valid_args(input_port, input_passwd) == false)
		throw NotValidArgsException();
	this->_port = atoi(input_port.c_str());
	this->_passwd = input_passwd;
	this->_listenerSock = 0;
	this->_sock = 0; // * utile? *
	// this->_fdCount = 1;
}

Server::~Server() {}

void Server::run()
{
	if (Server::createSocket() == -1)                 // Creation du socket du serveur
		throw SocketFailedException();
	// Server::setEvent(_listenerSock, POLLIN);         // Ajout du sock serveur a la liste des fds
	while (true)
	{
		if (Server::waitConnection() == -1)
			throw ClientConnectionFailedException();
	}
}

int Server::createSocket()
{
	///////  Creation du socket  ////////

	int val = 1;
	_listenerSock = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenerSock == -1)
		return -1;
	if (setsockopt(_listenerSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &val, sizeof(val)) < 0)
		return -1;
	if(fcntl(_listenerSock, F_SETFL, O_NONBLOCK) < 0) 	// set le socket en mode non bloquant
		return -1;
	std::cout << std::endl << " 1) Socket created" << std::endl;

	/////// Set up des caracteristiques du socket //////

	struct sockaddr_in listenerInfo;				  	// sous forme d'une struct
	memset(&listenerInfo, 0, sizeof(listenerInfo));	  	// initialisation de la struct de 0
	listenerInfo.sin_family = AF_INET;				  	// son type : Internet Protocol V4
	listenerInfo.sin_port = htons(this->_port);		  	// son port d'ecoute: argv[1]
	listenerInfo.sin_addr.s_addr = htonl(INADDR_ANY); 	// son Ip : Localhost //
	if (listenerInfo.sin_addr.s_addr == INADDR_NONE)  	// traitement d'erreur
		return -1;

	//////// Lier le socket aux caract fournies( adresse IP + port) ////////

	if (bind(_listenerSock, (struct sockaddr *)&listenerInfo, sizeof(listenerInfo)) < 0)
		return -1;
	std::cout << std::endl << " 2) Socket bounded" << std::endl;

	//// Socket en mode ecoute ////

	if (listen(_listenerSock, SOMAXCONN) < 0) /* check max listened sockets */
		return -1;
	Server::add_fd(_listenerSock, POLLIN, 1);
	return 0;
}

void Server::add_fd(int sock, int event, int isServer) /* changer le nom par add user/fd */
{
	/////   Set up des evenements du fd   /////
	
	if (!isServer)
	{
		User *new_user =  new User("hello",sock);
		if (Users.count(sock) > 0)						// check si Users deja existant
			return;
		Users.insert(std::pair<int, User *>(sock, new_user));
		// std::string response = "001 mettien :welcome to the network, mettien[!mettien@] \r\n";
		// send(sock, response.c_str(), response.size(), 0);
	}
	_pfds.push_back(pollfd());
	_pfds.back().fd = sock;
	_pfds.back().events = event;
	_pfds.back().revents = 0;
	std::cout << std::endl << "New Client on socket #" << sock << "." << std::endl;
	std::cout << "-----------------" << std::endl;
	std::vector<pollfd> :: iterator it;
   	for(it = _pfds.begin(); it != _pfds.end(); it++)
	
	{
	    std::cout << "| Fd: " << it->fd << "| Event:  " << it->events << std::endl;
	}
	std::cout << "------------------" << std::endl << std::endl;
}

int Server::waitConnection()
{
	int nb_event = 0;
	std::cout << std::endl<< "3) -----------   Server waiting for some event ... --------------" << std::endl;
	Server::sendPing();
	nb_event = poll(&_pfds[0], _pfds.size(), 5000);  /* changer le timeout */
	std::cout << "Poll result : " << nb_event << std::endl;
	if (nb_event == -1)
	{
		std::cout << "Poll failed " << std::endl;
		return -1;
	}
	if (nb_event == 0)
	{
		std::cout << "Time out for socket" << std::endl; /* voir retour de ce cas */
		return -1;
	}

	/////  Boucle d'attente de connexions entrantes ou existantes   ///////
	int currentSize = _pfds.size();
	for (int i = 0; i < currentSize; i++)
	{
		if (_pfds[i].revents == 0) 								// Ce socket n'a pas fait d'appel
			continue;
		if (_pfds[i].revents != POLLIN)
		{
			std::cout << "Error! Revent: " << _pfds[i].revents << " on index " << i << std::endl;
			return -1;
		}
		if (_pfds[i].fd == _listenerSock)
		{
			if (Server::newClient() == -1)						// Cas du socket du serveur
				return -1;
		}
		else
		{
			if (Server::rcvFromClient(i, _pfds[i].fd) == -1)		// Cas du socket d'un client
				return -1;
		}
	}
	return 0;
}

void	Server::setUserInfo(std::string buff, int fd)
{
	buff.erase(buff.size() -1);
	std::vector<std::string> vec;
	std::istringstream ss(buff);
    std::string string;

    while (std::getline(ss, string, '\n'))
    {
        vec.push_back(string );
    }
	std::vector<std::string>::iterator it = vec.begin();
	for (; it != vec.end();it++)
	{
		Command cmd(*it, Users, fd, Chan);
		Users =  cmd.set_Users();
		Chan =  cmd.set_Chan();
	}
	vec.clear();
}

int Server::rcvFromClient(int pos, int fd)
{
	std::cout << std::endl << "4) Server receving data ..." << std::endl;
	
	char buf[BUFFERSIZE + 1];								/* size adequate? */
	ssize_t byteRcv;
	
	/////  Reception de toutes les donnees sur le socket client   /////
	
	memset(buf, 0, BUFFERSIZE + 1); 			
	byteRcv = recv(fd, buf, BUFFERSIZE + 1, 0);							// Reception des strings
	if (byteRcv == -1)
		return -1;
	else if (byteRcv == 0)
	{
		std::cout << "5) The client disconnected" << std::endl;
		_pfds.erase(_pfds.begin() + pos);
		Users.erase(fd);
		return 0;
	}
	// std::cout << "Received from Client: " << std::string(buf, 0, byteRcv) << std::endl;
	// Server::getUser(fd)->setBuf(std::string(buf));
	// std::cout << "Received from Client: " << std::string(buf, 0, byteRcv) << std::endl;
	std::string str = buf;
	size_t po = str.find("\r");
    while (po != std::string::npos) {
        str.erase(po, 1);
        po = str.find("\r");
    }
	std::map<int, User *>::iterator it = Users.find(fd);
	if (it->second->getUserNick() == "")
		setUserInfo(str, fd);
	else
	{
		Command cmd(str, Users, fd, Chan);
		Users =  cmd.set_Users();
		Chan =  cmd.set_Chan();
	}
	return 0;
}

int Server::newClient()
{
	int newClient = 0;

	///// Accepte les requetes de connexion entrante /////

	std::cout << std::endl << "4) Server waiting for the client ..." << std::endl;
	do
	{
		newClient = accept(_listenerSock, NULL, NULL); 		// Creation du socket d'ecoute client
		// if (fcntl(newClient, F_SETFL, O_NONBLOCK) < 0) 		// set le socket en mode non bloquant
			// return -1;
		// std::cout << "Accept() = "<< newClient << std::endl;
		if (newClient < 0)
		{
			if (errno != EWOULDBLOCK)
				return -1;
			// std::cout << errno << " - " << strerror(errno) << std::endl;
			break;
		}
	std::cout << std::endl << "5) Server accepting one connection ..." << std::endl;
	Server::add_fd(newClient, POLLIN, 0);
	} while (newClient != -1);
	return 0;
}

void Server::sendmsg(int newClient, std::string msg)
{
	send(newClient, msg.c_str(), msg.length(), 0); // * a revoir pour le non bloquant + flag + erreurs (msg.cstr + 1?) *
}

int Server::getPort() const
{
	return (this->_port);
}

std::string Server::getPasswd() const
{
	return (this->_passwd);
}

User *Server::getUser(int fd) const
{
	std::map<int, User*>::const_iterator	it;

	it = Users.find(fd);
	if (it == Users.end())
		return NULL;
	return it->second;
}

bool Server::hasPasswd() const
{
	return (!this->_passwd.empty());
}

bool Server::valid_args(std::string input_port, std::string input_passwd)
{
	(void)input_passwd; // * a surement enlever *
	char *port_str = const_cast<char *>(input_port.c_str());

	if (input_port.length() == 4 && isdigit(port_str[0]))
	{
		int port = atoi(input_port.c_str());
		if (port < 6665 || port > 6669) // * c'est ok? *
			return false;
		return true;
	}
	return false;
}

const char *Server::NotValidArgsException::what() const throw()
{
	return "Argument aren't valid";
}

const char *Server::SocketFailedException::what() const throw()
{
	return "Socket Failed";
}

const char *Server::ClientConnectionFailedException::what() const throw()
{
	return "Client connection Failed";
}
