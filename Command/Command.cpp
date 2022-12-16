#include "Command.hpp"

// 431: ERR_NONICKNAMEGIVEN: No nickname given
// 432: ERR_ERRONEUSNICKNAME: Erroneous nickname
// 433: ERR_NICKNAMEINUSE: Nickname is already in use
// 436: ERR_NICKCOLLISION: Nickname collision KILL from <nickname>@<hostname>
// 437: ERR_UNAVAILRESOURCE: Nick/channel is temporarily unavailable
// 482: ERR_CHANOPRIVSNEEDED: You're not channel operator

int	Command::nick(User  U)
{
	std::cout << " here" << std::endl;
	if (_cmd.size())
	{
		reply(431);
		return -1;
	}
	U.getUserNick() = _cmd[0];
	std::cout <<  U.getUserNick() << std::endl;
	return (0);
}
//USER <username> <mode> <unused> <realname>

int	Command::user(User  U)
{
	// error 461
	// error 462
	//maybe more
	// U.username = _cmd[1];
	// U.mode = _cmd[2];
	// U.realname = _cmd[3];
	(void)U;


	return (1);
}
// int	whois(void){return (0);}


template <typename T>
void printVector(const std::vector<T>& v) {
  typename std::vector<T>::const_iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}
int	Command::ft_exec_cmd(std::map<int, User *> Users, int clientSock)
{
	std::string command[2] = {"NICK", "USER"};

	std::map<int, User *>::iterator it = Users.find(clientSock);

	// int	(*functptr[])() = {&admin, &akill, &away, &cleandead, &clearakills, &connect, &die, &expban, &globops, &help, &importmotd, &info, &invite, &isbanned, &ison, &join, &kick, &kill, &killban, &kline, &links, &list, &lusers, &me, &mode, &motd, &msg, &names, &nick, &notice, &oper, &part, &pass, &privmsg, &query, &quit, &rakill, &rehash, &shun, &silence, &squit, &stats, &summon, &time, &topic, &unban, &unkline, &userhost, &users, &version, &wall, &wallops, &who, &whois, &whowas};
	int	(Command::*functptr[])(User) = {&Command::nick, &Command::user};

	int	ret;
	for (int i = 0; i < 2; i++)
	{
		if (command[i] == _command)
		{
			ret = (this->*functptr[i])(*it->second);
			return (ret); // verifier code d'erreurs dans la doc IRC
		}
	}
	return 0;
}

/* Constructor */

Command::Command(std::string msg, std::map<int, User*> Users, int clientSock) : _BrutMsg(msg)
{
	std::istringstream ss(msg);

	std::string token;
	while (std::getline(ss, token, ' '))
	{
		_cmd.push_back(token);
	}
	_command = _cmd[0];
	printVector(_cmd);
	std::cout << "Constructeur called for : " << this->_BrutMsg << std::endl; // A supp
	ft_exec_cmd(Users, clientSock); // code retour ??
	return ;
}

/* Destructor */

Command::~Command(void)
{
	return ;
}
