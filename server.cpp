/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettien <mettien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:54:49 by mettien           #+#    #+#             */
/*   Updated: 2022/12/16 19:18:19 by mettien          ###   ########.fr       */
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
	this->_fdCount = 0;
}

Server::~Server() {}

void Server::run()
{
	if (Server::createSocket() == -1)                 // Creation du socket du serveur
		throw SocketFailedException();
	Server::setEvent(_listenerSock, POLLIN);         // Ajout du sock serveur a la liste des fds
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
	Server::setEvent(_listenerSock, POLLIN);
	return 0;
}

void Server::setEvent(int sock, int event) /* changer le nom par add user/fd */
{
	/////   Set up des evenements du fd   /////
	
	_pfds[_fdCount].fd = sock;
	_pfds[_fdCount].events = event;
	std::cout << "New fd = " << sock << " with event = " << _pfds[_fdCount].events << std::endl;
	_fdCount++; 										// incrementation du nb de fd //
}

int Server::waitConnection()
{
	std::cout << std::endl<< " 3) Server waiting for some event ..." << std::endl;
	
	int res_event = poll(&_pfds[0], _fdCount, -1);  /* changer le timeout */
	std::cout << "Poll result : " << res_event << std::endl;
	std::cout << "Fd revent : " << _pfds[0].revents << std::endl;
	if (res_event == -1)
	{
		std::cout << "Poll failed " << std::endl;
		return -1;
	}
	if (res_event == 0)
	{
		std::cout << "Time out for socket" << std::endl; /* voir retour de ce cas */
		return -1;
	}

	/////  Boucle d'attente de connexions entrantes ou existantes   ///////
	
	for (int i = 0; i < _fdCount; i++)
	{
		if (_pfds[i].revents == POLLIN) 				// Un socket en attente de lecture
		{
			if (_pfds[i].fd == _listenerSock) 			
			{
				if (Server::newClient() == -1)			// Cas du socket du serveur
					return -1;
			}
			else 										
			{
				if (Server::rcvFromClient(_pfds[i].fd) == -1)		// Cas du socket d'un client
					return -1;
			}
		}
		else
		{
			std::cout << " Error! Revent" << _pfds[i].revents << std::endl;
			return -1;
		}
	}
	return 0;
}

int Server::rcvFromClient(int fd)
{
	std::cout << std::endl << " 3) Server receving data ..." << std::endl;
	
	char buf[4096];
	
	/////  Reception de toutes les donnees sur le socket client   /////
	
	while (true)
	{
		memset(buf, 0, 4096); 			// * size adequate? *
		int byteRcv = recv(_listenerSock, buf, 4096, 0);		// Reception des string
		if (byteRcv == -1)
			return -1;
		else if (byteRcv == 0)
		{
			std::cout << "The client disconnected" << std::endl;
			break;
		}
		User *U = new User("hello");
		Users.insert(std::pair<int, User *>(fd, U));
		std::cout << "Received from Client: " << std::string(buf, 0, byteRcv) << std::endl;
		Command cmd(buf, Users);
	}
	return 0;
}

int Server::newClient()
{
	int newClient = 0;
	// struct sockaddr_in Client;
	// socklen_t ClientSize = sizeof(Client);

	///// Accepte les requetes de connexion entrante /////
	
	std::cout << std::endl << " 3) Server waiting for the client ..." << std::endl;
	std::cout << newClient << std::endl;
	do
	{
		std::cout << newClient << std::endl;
		newClient = accept(_listenerSock, NULL, NULL); 		// Creation du socket d'ecoute client
		std::cout << newClient << std::endl;
		if (newClient < 0)
			return -1;
		std::cout << std::endl << " 4) Server accepting one connection ..." << std::endl;
		Server::setEvent(newClient, POLLIN);

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