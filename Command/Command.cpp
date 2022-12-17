#include "Command.hpp"



// 431: ERR_NONICKNAMEGIVEN: No nickname given
// 432: ERR_ERRONEUSNICKNAME: Erroneous nickname
// 433: ERR_NICKNAMEINUSE: Nickname is already in use
// 436: ERR_NICKCOLLISION: Nickname collision KILL from <nickname>@<hostname>
// 437: ERR_UNAVAILRESOURCE: Nick/channel is temporarily unavailable
// 482: ERR_CHANOPRIVSNEEDED: You're not channel operator

int	Command::nick(User  U)
{
	// Vérifie qu'il y a bien un argument
	if (arguments.empty()) {
		reply(431);
	return -1;
	}
	std::map<int, User *>::const_iterator it;
  	for (it = Users.begin(); it != Users.end(); ++it)
	{
		if (arguments[0] == it->second->getUserNick())
			reply(433);
		return (-1);
	}
	U.getUserNick() = arguments[1];

	return (0);
}
//USER <username> <mode> <unused> <realname>
/// ?USER <username> <hostname> <realname>
int	Command::user(User  U)
{
	// error 461
	if (arguments.empty())
	{
		reply(461);
		return (-1);
	}
	if (U.username.size() != 0)
	{
		reply(462);
		return (-1);
	}


	U.username = arguments[0];
	U.mode = atoi(arguments[1].c_str());
	U.realname = arguments[2];

	return (1);
}

int	Command::whois(User U)
{
	// a voir pour l envoie au client
	std::cout << U.getUserNick() << std::endl;
	 std::string reponse = ":localhost 311 " + U.username +
	 " utilisateur utilisateur * :Nom réel\r\n";
	send(U.socket, reponse.c_str(), reponse.size(), 0);
	return (0);
}


template <typename T>
void printVector(const std::vector<T>& v) {
  typename std::vector<T>::const_iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int	Command::ft_exec_cmd(int clientSock)
{
	std::string command[3] = {"NICK", "USER", "WHOIS"};

	std::map<int, User *>::iterator it = Users.find(clientSock);
	int	(Command::*functptr[])(User) = {&Command::nick, &Command::user, &Command::whois};

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

Command::Command(std::string msg, std::map<int, User*> Us, int clientSock) : _BrutMsg(msg)
{
	 std::string reponse = ":localhost 311";
	send(clientSock, reponse.c_str(), reponse.size(), 0);
	std::istringstream ss(msg);
	Users = Us;
	std::string token;
	while (std::getline(ss, token, ' '))
	{
		arguments.push_back(token);
	}
	_command = arguments[0];
	arguments.erase(arguments.begin());
	printVector(arguments);
	std::cout << "Constructeur called for : " << this->_BrutMsg << std::endl; // A supp
	ft_exec_cmd(clientSock); // code retour ??
	return ;
}

/* Destructor */

Command::~Command(void)
{
	return ;
}
