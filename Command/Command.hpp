#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <cctype>
#include <map>
#include "../includes/server.hpp"
#include "User.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Utils.hpp"

void reply(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");

class	Command
{
	private :
	std::string	_BrutMsg;
	std::string _command;
	std::vector<std::string> _cmd;
	// User		_User;


	public :

	/* Constructor */
	Command(std::string cmd, std::map<int, User*> Users, int clientSock);
	int	ft_exec_cmd(std::map<int, User *> Users, int clientSock);
	int	nick(User U);
	int	user(User U);
	/* Destructor */
	~Command(void);
};

#endif
