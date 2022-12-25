/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <redarnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:54:49 by mettien           #+#    #+#             */
/*   Updated: 2022/12/23 22:21:59 by redarnet         ###   ########.fr       */
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
	this->_fdCount = 1;
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

	_listenerSock = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenerSock == -1)
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
	Server::add_fd_ToList(_listenerSock, POLLIN, 1);
	return 0;
}

void Server::add_fd_ToList(int sock, int event, int isServer) /* changer le nom par add user/fd */
{
	/////   Set up des evenements du fd   /////

	// pollfd  pfd;
	// pfd.fd = sock;
	// pfd.events = event;
	if (isServer)
		_fdCount = 0;
	std::cout << _fdCount << std::endl;
	// _pfds.insert(std::pair<int, pollfd>(_fdCount, pfd));
	_pfds.push_back(pollfd());
	_pfds.back().fd = sock;
	_pfds.back().events = event;
	_pfds.back().revents = 0;
	std::cout << "New fd = " << sock << " with event = " << _pfds[_fdCount].events << std::endl;
	std::cout << "----- FD MAP -----" << std::endl;
	std::vector<pollfd> :: iterator it;
   	for(it = _pfds.begin(); it != _pfds.end(); it++)
	{
	    std::cout << "| Fd: " << it->fd << "| Event:  " << it->events << std::endl;
	}
	std::cout << "------------------" << std::endl << std::endl;
	// if (!isServer)
	// {
		//
		// Users.insert(std::pair<int, User *>(sock, U));
	// }
	_fdCount++;
	std::cout << _fdCount << std::endl;
}

int Server::waitConnection()
{
	int nb_event = 0;
	std::cout << std::endl<< "3) -----------   Server waiting for some event ... --------------" << std::endl;
	_pfds[0].revents = 0;
	for (int i = 0; i < _fdCount; i++)
	{
		std::cout << "Pos: " << i << " ------ " << _pfds[i].revents << std::endl;
	}
	nb_event = poll(&_pfds[0], _fdCount, -1);  /* changer le timeout */
	std::cout << "Poll result : " << nb_event << std::endl;
	// std::cout << "Fd revent : " << _pfds[0].revents << std::endl;
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
	// std::cout << _fdCount << "|" << current_size << std::endl;
	int currentSize = _fdCount;
	for (int i = 0; i < currentSize; i++)
	{
		// std::cout << _fdCount << "|" << currentSize << std::endl;
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

int Server::rcvFromClient(int pos, int fd)
{
	std::cout << std::endl << "4) Server receving data ..." << std::endl;

	char buf[4096];								/* size adequate? */

	/////  Reception de toutes les donnees sur le socket client   /////

	memset(buf, 0, 4096);
	int byteRcv = recv(fd, buf, 4096, 0);							// Reception des strings
	if (byteRcv == -1)
		return -1;
	else if (byteRcv == 0)
	{
		std::cout << "5) The client disconnected" << std::endl;
		_pfds.erase(_pfds.begin() + pos);
		_fdCount--;
		return 0;
	}
	std::cout << "Received from Client: " << std::string(buf, 0, byteRcv) << std::endl;
	// User *U =  new User("hello", byteRcv);
	// Users.push_back(U);
			// send(clientSock, reponse.c_str(), reponse.size(), 0);
	User  *U =  new  User("hello", fd);
	std::map<int, User *>::iterator it = Users.find(byteRcv);
	if (it == Users.end())
		Users.insert(std::pair<int, User*>(byteRcv, U));
	std::string reponse = "001 redarnet :Welcome to the <> Network, redarnet[!redarnet@] \r\n";
	//  reponse = ":127.0.0.1 002 redarnet :Your host is server, running version <version>\r\n";
	send(fd, reponse.c_str(), reponse.size(), 0);
	// std::cout << "Received from Client: " << std::string(buf, 0, byteRcv) << std::endl;
	Command cmd(buf, Users ,byteRcv);
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
		std::cout << "Accept() = "<< newClient << std::endl;
		if (newClient < 0)
		{
			if (errno != EWOULDBLOCK)
				return -1;
			// std::cout << errno << " - " << strerror(errno) << std::endl;
			break;
		}
			// ":<server> 001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]"
		//    reponse = ":127.0.0.1 003 redarnet :This server was created <datetime>\r\n";
		// 	send(clientSock, reponse.c_str(), reponse.size(), 0);
		// 	reponse = ":127.0.0.1 004 redarnet server <version> <available umodes> <available cmodes> [<cmodes with param>]";
		// 	send(clientSock, reponse.c_str(), reponse.size(), 0);
	// close(clientSock); // a enlever
	std::cout << std::endl << "5) Server accepting one connection ..." << std::endl;
	Server::add_fd_ToList(newClient, POLLIN, 0);
	} while (newClient != -1); // * condition a revoir * //
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
	// check des criteres de password ?? Idk
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
