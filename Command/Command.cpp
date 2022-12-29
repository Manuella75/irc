#include "Command.hpp"
std::vector<std::string> split_splace1(std::vector<std::string>& v) {
  std::vector<std::string>::iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
	std::string &str = *it;
		size_t pos = str.find(" ");
        // Enlever tous les espaces de la chaîne
        while (pos != std::string::npos) {
            str.erase(pos, 1);
            pos = str.find(" ");
        }
        // // Trouver l'index des retours à la ligne dans la chaîne
        pos = str.find("\n");
        // Enlever tous les retours à la ligne de la chaîne
        while (pos != std::string::npos) {
            str.erase(pos, 1);
            pos = str.find("\n");
        }
 	 }
	 return v;
}
void sendConfirmationMessage(int clientSocket, const std::string& confirmationMessage, std::string Username) {
  // Construisez le message de confirmation en suivant le format du protocole IRC
  std::string message = ": 001 "  + Username + " " + confirmationMessage + "\r\n";

  // Envoyez le message au client en utilisant la fonction send()
  send(clientSocket, message.c_str(), message.length(), 0);
}
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

int	Command::nick(User *U)
{
	std::cout << "COMMAND NICK" << std::endl;
	// Vérifie qu'il y a bien un argument
	if (arguments.empty()) {
		reply(431);
		return -1;
	}
	// verifie si le user est deja utilise
	std::map<int, User *>::const_iterator it;
  	for (it = Users.begin(); it != Users.end(); ++it)
	{
		// std::cout << "USER = " << it->second->getUserNick() << std::endl;
		if (arguments[0] == it->second->getUserNick())
		{
			arguments[0] += "1";
			nick(U);
			return (0);
		}
	}
	U->setUserNick(arguments[0]);
	std::cout << "New Nick is " << U->getUserNick() << std::endl;
	sendConfirmationMessage(U->getUserSocket(), "new NICK", U->getUserNick() );
	return 0;
}

//USER <username> <mode> <unused> <realname>
/// ?USER <username> <hostname> <realname>
int	Command::user(User  *U)
{
	std::cout << "COMMAND USER" << std::endl;
	// error 461
	if (arguments.empty())
	{
		reply(461);
		return (-1);
	}
	if (U->username.size() != 0)
	{
		reply(462);
		return (-1);
	}
	U->username = arguments[0];
	U->setUserMode(atoi(arguments[1].c_str()));
	U->realname = arguments[2];
	return (1);
}

int	Command::whois(User *U)
{
	std::cout << "COMMAND WHHOIS" << std::endl;
	// a voir pour l envoie au client
	std::cout << U->getUserNick() << std::endl;
	 std::string reponse = ":" + U->username +
	 " utilisateur utilisateur * :Nom réel\r\n";
	send(U->getUserSocket(), reponse.c_str(), reponse.size(), 0);
	return (0);
}

//Le client n'a pas les permissions nécessaires pour rejoindre le canal cible :
// vous pouvez envoyer au client un message d'erreur "475"
//Le client a déjà rejoint le canal cible : vous pouvez envoyer au client un message d'erreur "442" (You're already on that channel)
// indiquant qu'il est déjà membre du canal cible.
// note si le User est deja dans un channel ? > mode = 2

int Command::join(User *U)
{
	std::cout << "COMMAND JOIN" << std::endl;
	if (arguments.empty())
		return -1;
	// si le channel n existe pas > on le cree
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		Channel *Cha =new Channel(arguments[0], U);
		Chan.insert(std::pair<std::string, Channel *>(arguments[0], Cha));
		std::string message = "JOIN " + arguments[0] + "\r\n";
		// std::string message = "JOIN #le\r\n";
		std::cout << "message = " << message << std::endl;
		send(U->getUserSocket(), message.c_str(), message.length(), 0);
		return (0);
	}
	// si le User est deja dans le channel
	std::map<int, User *>::const_iterator itUser = it->second->getUsers().find(U->getUserSocket());
	if (itUser != it->second->getUsers().end())
		return -1;
	//on rajoute le User dans le Channel
	U->setUserMode(1);
	U->setUserChannel(arguments[0]);
	User  *Us =  new  User(U);
	it->second->getUsers().insert(std::pair<int, User *>(U->getUserSocket(), Us));
	return (0);
}

//permet de quitter un chanell
int Command::part(User *U)
{
	std::cout << "COMMAND PART" << std::endl;
	if (arguments.empty())
		return -1;
	// std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	std::map<std::string, Channel *>::iterator it = Chan.begin();
	//si le channel exist pas
	if (it == Chan.end())
		return -1;
	// std::string message = "PART" + U->getUserChannel() + "\r\n";
	std::string message = "PART " + arguments[0] + "\r\n";
	std::cout << "message = " << message << std::endl;
	send(U->getUserSocket(), message.c_str(), message.length(), 0);
	std::cout << "message = " << message << std::endl;
	send(U->getUserSocket(), message.c_str(), message.length(), 0);
	// on trouve le User et on le delete
	std::map<int, User *>::const_iterator itUser = it->second->getUsers().find(U->getUserSocket());
	if (itUser != it->second->getUsers().end())
		delete itUser->second;
	it->second->getUsers().erase(U->getUserSocket());
	U->setUserMode(2);
	U->setUserChannel("");
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
int Command::mode(User *U)
{
	std::cout << "COMMAND MODE" << std::endl;
	int Use;

	// si le mode est pas ope ca sert a rien
	if (arguments[1] != "2")
		return -1;
	if (arguments.empty() && arguments.size() != 2)
		return -1;
		// si le user n est pas un ope ou n est pas dans un channel
	if (U->getUserMode() != 1)
		return -1;
	// on regarde si les 2 users sont dans le meme channel
	std::map<std::string, Channel *>::iterator it = Chan.find(U->getUserChannel());
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

int Command::ping(User *U)
{
	std::cout << "COMMAND PING" << std::endl;
	std::cout << " Ping =" << U->getUserSocket() << std::endl;
	sendConfirmationMessage(U->getUserSocket(), "PONG", U->getUserNick());
	return 0;
}

int Command::privmsg_user(User *U, std::string msg)
{
	int user = find_User_string(arguments[0]);
	std::map<int, User *>::iterator it = Users.find(user);
	if (it == Users.end())
		return -3;
	std::string message = "PRIVMSG " + U->getUserNick()  + msg;
	sendConfirmationMessage(it->second->getUserSocket(), message, it->second->getUserNick() );
	return 0;
}
int Command::privmsg(User *U)
{
	if (arguments.empty() && arguments.size() < 1)
		return -2;
	std::string msg;
	std::vector<std::string>::iterator itvec = arguments.begin();
	itvec++;
	for (; itvec != arguments.end(); itvec++)
		msg =  msg+ *itvec + " ";
	//si le user est dans aucun channel
	std::cout << "COMMAND PRIVMSG" << std::endl;
	if (arguments[0][0] != '#')
		return (privmsg_user(U, msg));
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
		return (-1);
	// envoie un msg a tous les user dans le channel
	std::map<int, User *>::iterator itUser = it->second->getUsers().begin();

	for (;itUser != it->second->getUsers().end(); itUser++)
	{
		std::string message = ":"+ U->getUserNick() +" PRIVMSG " + arguments[0] + " :" + msg + "\r\n";
		std::cout << " message =  " << message << itUser->second->getUserSocket() << std::endl;
		std::cout << " user itus =  " <<  itUser->second->getUserNick() << std::endl;
		if (itUser->second->getUserSocket() != U->getUserSocket())
			send(itUser->second->getUserSocket(), message.c_str(), message.length(), 0);
	}
	return 0;
}

std::map<int, User *>  Command::set_Users()
{
	return this->Users;
}

std::map<std::string, Channel *>  Command::set_Chan()
{
	return this->Chan;
}

int	Command::ft_exec_cmd(int clientSock)
{
	std::string command[8] = {"NICK", "USER", "WHOIS", "JOIN", "PART" , "MODE", "PING", "PRIVMSG"};

	std::map<int, User *>::iterator it = Users.find(clientSock);
	int	(Command::*functptr[])(User*) = {&Command::nick, &Command::user, &Command::whois, &Command::join, &Command::part, &Command::mode,&Command::ping, &Command::privmsg};

	int	ret;
	for (int i = 0; i < 8; i++)
	{
		if (command[i] == _command)
		{
			ret = (this->*functptr[i ])(it->second);
			std::cout << "Retour cmd = " << ret << std::endl;
			return (ret); // verifier code d'erreurs dans la doc IRC
		}
	}
	std::map<int, User *>::const_iterator ite;
  	for (ite = Users.begin(); ite != Users.end(); ++ite)
		std::cout << "USERs in serv = " << ite->second->getUserNick() << std::endl;
	return 0;
}

/* Constructor */

Command::Command(std::string msg, std::map<int, User*> Us, int clientSock, std::map<std::string, Channel *> Chann) : _BrutMsg(msg)
{
	std::istringstream ss(msg);
	Users = Us;
	Chan = Chann;
	std::string token;

	while (std::getline(ss, token, ' '))
	{
		arguments.push_back(token);
	}
	arguments = split_splace1(arguments);
	_command = arguments[0];
	arguments.erase(arguments.begin());
	printVector(arguments);
	ft_exec_cmd(clientSock); // code retour ??
	arguments.clear();
	return ;
}

/* Destructor */

Command::~Command(void)
{
	return ;
}
