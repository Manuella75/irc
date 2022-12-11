/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <redarnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:54:49 by mettien           #+#    #+#             */
/*   Updated: 2022/12/11 22:09:54 by redarnet         ###   ########.fr       */
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
	this->_sock = 0;
	this->_lastFd = 0;

}

Server::~Server(){}

void	Server::run()
{
	if (Server::createSocket() == -1)
		throw SocketFailedException();
	Server::set_Event(_listenerSock, POLLIN);
	while (true)
	{
		// if (Server::polling() == -1);
			// throw ClientConnectionFailedException();
		// if (Server::waitClient() == -1)
			// throw ClientConnectionFailedException();
		int clientSock = Server::connection();
		if (clientSock == -1)
			throw ClientConnectionFailedException();
	}
}

int Server::createSocket()
{
	///////  Creation du socket  ////////

	_listenerSock = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenerSock == -1)
		return -1;
	// if(fcntl(_listenerSock, F_SETFL, O_NONBLOCK) < 0) 	// set le socket en non bloquant
		// return -1;
	std::cout << std::endl << " 1) Socket created" << std::endl;

	/////// Set up des caracteristiques du socket //////

	struct sockaddr_in listenerInfo;  					// sous forme d'une struct
	memset(&listenerInfo, 0, sizeof(listenerInfo)); 	// initialisation de la struct de 0
	listenerInfo.sin_family = AF_INET;  				// son type : Internet Protocol V4
	listenerInfo.sin_port = htons(this->_port);  		// son port d'ecoute: argv[1]
	listenerInfo.sin_addr.s_addr = htonl(INADDR_ANY); 	// son Ip : Localhost //
	if (listenerInfo.sin_addr.s_addr == INADDR_NONE)	// traitement d'erreur
    	return -1;

	//////// Lier le socket aux caract fournies( adresse IP + port) ////////

	if (bind(_listenerSock, (struct sockaddr *)&listenerInfo, sizeof(listenerInfo)) < 0)
		return -1;
	std::cout << std::endl << " 2) Socket bounded" << std::endl;

	//// Socket en mode ecoute ////

	if(listen(_listenerSock, SOMAXCONN) < 0) // check max listened sockets
		return -1;
	Server::set_Event(_listenerSock, POLLIN);
	return 0;
}

void	Server::set_Event(int sock, int event) //changer le nom par add user/fd
{
	_pfds[_lastFd].fd = sock;
	_pfds[_lastFd].events = event;
	std::cout<< "back" << _pfds[_lastFd].fd << std::endl;
	std::cout<< "back" << _pfds[_lastFd].events << std::endl;
	_lastFd++;
}

int		Server::polling()
{
	// static int i;

	int i = 0;
	// _pfds[i].fd = sock;
	// _pfds[i].events = event;
	// std::cout<< "back" << _pfds[0].fd << std::endl;
	// std::cout<< "back" << _pfds[0].events << std::endl;
	int res_event = poll(&_pfds[i], _lastFd , -1); // changer le timeout
	std::cout << res_event << std::endl;
	std::cout << _pfds[i].revents << std::endl;
	if (res_event == -1)
		return -1;
	if (res_event == 0)
	{
		std::cout << "Time out for socket" << std::endl;
	}
	// for (i = 0; i < _lastFd; i++)
	// {
		// if (_pfds[i].revents == POLLERR|POLLHUP)
			// std::cout << " Revent socket problem" << std::endl;
		// if (_pfds[i].events == POLLIN) 							// A socket waiting for read
		// {
			// if (_pfds[i].fd == _listenerSock)					// Server socket waiting read
			// {
				// if (Server::connection() == -1)
					// return -1;
			// }
			// else
			// {
				//
			// }												//Client socket waiting for read
//
			//
		// }

	// }
	return 0;
}

int		Server::waitClient()
{
	Server::polling();

	return 0;
}

int		Server::connection()
{
	struct sockaddr_in clientInfo;
	socklen_t clientSize = sizeof(clientInfo);
	char buf[4096];

	std::cout << std::endl << " 3) Server waiting for client ..." << std::endl;
	 ///// Accepte une requete de connexion entrante /////

	int clientSock = accept(_listenerSock, (struct sockaddr*)&clientInfo, &clientSize);
	if (clientSock < 0)
		return -1;
	std::cout << std::endl << " 3) Server accepting one connection ..." << std::endl;

	std::string hello = "hello";
	///// Boucle de lecture des msg recus ///////
	while (true)
	{
		memset (buf, 0, 4096); // size adequate?
		int byteRcv = recv(clientSock, buf, 4096, 0);
		if (byteRcv == -1)
			return -1;
		else if (byteRcv == 0)
		{
			std::cout << "The client disconnected" << std::endl;
			break;
		}
		else
		{
			User  *U =  new  User(hello);
			Users.insert(std::pair<int, User*>(clientSock, U));
			std::cout << "Received from Client: " << std::string(buf, 0, byteRcv) << std::endl;
			Command cmd(buf, Users, clientSock, clientInfo);
		}
	}
	// close(clientSock); // a enlever

	return 0;

}

void    Server::sendmsg(int clientSock, std::string msg)
{
	send(clientSock, msg.c_str(), msg.length(), 0); // a revoir pour le non bloquant + flag + erreurs (msg.cstr + 1?)
}

int		Server::getPort() const
{
    return(this->_port);
}

std::string Server::getPasswd() const
{
    return(this->_passwd);
}

bool Server::hasPasswd() const
{
	return (!this->_passwd.empty());
}

bool Server::valid_args(std::string input_port, std::string input_passwd)
{
	(void)input_passwd; // a surement enlever
	char* port_str = const_cast<char*>(input_port.c_str());

	if (input_port.length() == 4 && isdigit(port_str[0]))
	{
		int port = atoi(input_port.c_str());
		if (port < 6665 || port > 6669) // c'est ok?
			return false;
		return true;
	}
	// check des criteres de password ?? Idk
	return false;
}

const char* Server::NotValidArgsException::what() const throw()
{
  return "Argument aren't valid";
}

const char* Server::SocketFailedException::what() const throw()
{
  return "Socket Failed";
}

const char* Server::ClientConnectionFailedException::what() const throw()
{
  return "Client connection Failed";
}
