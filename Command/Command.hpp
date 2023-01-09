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
#include "Utils.hpp"
#include "Channel.hpp"
#include "../includes/server.hpp"

class Channel;
// class User;
class Server;

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
		int topic(User *U);
		int privmsg(User *U);
		int	oper(User *U);
		int privmsg_user(User *U, std::string msg);
		int	kick(User *U);
		void	send_message_chan(User *U, std::string message, Channel chan);
		int setUser_name(User *U);
		void	send_message(User *U, std::string message, std::string arg);
		int	nicknameisue();
		int	check_operator(User *U);
		/* Destructor */
		~Command(void);
};

#endif
