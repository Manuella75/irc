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
#include "Channel.hpp"

void reply(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");
class Channel;
class User;

class	Command
{
	private :
		std::string	_BrutMsg;
		std::string _command;
		std::vector<std::string> arguments;
		std::map<int, User *> Users;
		std::map<std::string, Channel *> Chan;
	// User		_User;



	public :
		/* Constructor */
		Command(std::string cmd, std::map<int, User*> Users, int clientSock, std::map<std::string, Channel *> Chan);
		int	ft_exec_cmd(int clientSock);
		int	find_User_string(std::string target);
		std::map<int, User *> set_Users();
		std::map<std::string, Channel *> set_Chan();
		int	nick(User *U);
		int	user(User *U);
		int	whois(User *U);
		int join(User *U);
		int part(User *U);
		int ping(User *U);
		int mode(User *U);
		int privmsg(User *U);
		/* Destructor */
		~Command(void);
};

#endif
