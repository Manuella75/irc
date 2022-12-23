#include "Command.hpp"


int	Command::find_User_string(std::string target)
{
	std::map<int, User *>::iterator it = Users.begin();
	for (; it != Users.end(); it++)
	{
		if (it->second->getUserNick() == target)
			return it->first;
	}
	return -1;
}

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
	U.setUserMode(atoi(arguments[1].c_str()));
	U.realname = arguments[2];
	return (1);
}

int	Command::whois(User U)
{
	// a voir pour l envoie au client
	std::cout << U.getUserNick() << std::endl;
	 std::string reponse = ":localhost 311 " + U.username +
	 " utilisateur utilisateur * :Nom réel\r\n";
	send(U.getUserSocket(), reponse.c_str(), reponse.size(), 0);
	return (0);
}

//Le client n'a pas les permissions nécessaires pour rejoindre le canal cible :
// vous pouvez envoyer au client un message d'erreur "475"
//Le client a déjà rejoint le canal cible : vous pouvez envoyer au client un message d'erreur "442" (You're already on that channel)
// indiquant qu'il est déjà membre du canal cible.
// note si le User est deja dans un channel ? > mode = 2

int Command::join(User U)
{
	if (arguments.empty())
		return -1;
	// si le channel n existe pas > on le cree
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		Channel *Cha =new Channel(arguments[0], U);
		Chan.insert(std::pair<std::string, Channel *>(arguments[0], Cha));
		return (0);
	}
	// si le User est deja dans le channel
	std::map<int, User *>::const_iterator itUser = it->second->getUsers().find(U.getUserSocket());
	if (itUser != it->second->getUsers().end())
		return -1;
	//on rajoute le User dans le Channel
	U.setUserMode(1);
	U.setUserChannel(arguments[0]);
	User  *Us =  new  User(U);
	it->second->getUsers().insert(std::pair<int, User *>(U.getUserSocket(), Us));
	return (0);
}

//permet de quitter un chanell
int Command::part(User U)
{
	if (arguments.empty())
		return -1;
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	//si le channel exist pas
	if (it == Chan.end())
		return -1;
	// on trouve le User et on le delete
	std::map<int, User *>::const_iterator itUser = it->second->getUsers().find(U.getUserSocket());
	if (itUser != it->second->getUsers().end())
		delete itUser->second;
	it->second->getUsers().erase(U.getUserSocket());
	U.setUserMode(2);
	U.setUserChannel("");
	// si plus de Users delete le channel
	if (it->second->getUsers().size() == 0)
	{
		delete it->second;
		Chan.erase(it);
	}
	return 0;
}

//permet de donner le mode ope a un user normal
// <target> <mode>
int Command::mode(User U)
{
	int Use;

	// si le mode est pas ope ca sert a rien
	if (arguments[1] != "2")
		return -1;
	if (arguments.empty() && arguments.size() != 2)
		return -1;
		// si le user n est pas un ope ou n est pas dans un channel
	if (U.getUserMode() != 1)
		return -1;
	// on regarde si les 2 users sont dans le meme channel
	std::map<std::string, Channel *>::iterator it = Chan.find(U.getUserChannel());
	//on cherche le User et on le met ope
	Use = find_User_string(arguments[1]);
	std::map<int, User *>::const_iterator itUser = it->second->getUsers().find(Use);
	if (itUser != it->second->getUsers().end())
	{
		itUser->second->setUserMode(2);
		return 0;
	}
	return -1;
}

int	Command::ft_exec_cmd(int clientSock)
{
	std::string command[5] = {"NICK", "USER", "WHOIS", "JOIN", "PART" "MODE"};

	std::map<int, User *>::iterator it = Users.find(clientSock);
	int	(Command::*functptr[])(User) = {&Command::nick, &Command::user, &Command::whois, &Command::join, &Command::part, &Command::mode};

	int	ret;
	for (int i = 0; i < 5; i++)
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
	 std::string reponse = ":sender PRIVMSG redarnet ee\r\n";
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
