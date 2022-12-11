#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <cctype>
#include <map>
#include "../includes/server.hpp"
#include "User.hpp"

class	Command
{
	private :
	std::string	_BrutMsg;
	std::string	_cmd;
	std::string	_args;
	// User		_User;


	public :

	/* Constructor */
	Command(std::string cmd, std::map<int, User*> Users, int clientSock, struct sockaddr_in clientInfo);
	/* Destructor */
	~Command(void);
};

#endif
