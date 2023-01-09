#include "Command.hpp"

int Command::notice_user(User *U, std::string msg)
{
	int user = find_User_string(arguments[0]);
	std::map<int, User *>::iterator it = Users.find(user);
	if (it == Users.end())
	{
		U->reply(411);
		return -1;
	}
	if (it->second->getUserNick() == U->getUserNick())
	{
		return -1;
	}
	std::string message =  U->getUserNick() + " " + msg;
	send_message(it->second, "NOTICE ", message);
	return 0;
}

int Command::notice(User *U)
{
	if (arguments.empty() && arguments.size() < 1)
		return (U->reply(461, _command), -1);
	if (U->oper != 1)
	{
		U->reply(482);
		return 0;
	}
	std::string msg;
	std::vector<std::string>::iterator itvec = arguments.begin();
	itvec++;
	for (; itvec != arguments.end(); itvec++)
		msg +=   *itvec + " ";
	//si le user est dans aucun channel
	if (arguments[0][0] != '#')
		return (notice_user(U, msg));
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		U->reply(401, arguments[0]);
		return (-1);
	}
	// envoie un msg a tous les user dans le channel
	std::map<int, User *>::iterator itUser = it->second->getUsers().begin();

	for (;itUser != it->second->getUsers().end(); itUser++)
	{
		std::string message = ":"+ U->getUserNick() +" NOTICE " + arguments[0] + " :" + msg + "\r\n";
		std::cout << " message =  " << message << itUser->second->getUserSocket() << std::endl;
		if (itUser->second->getUserSocket() != U->getUserSocket())
			send(itUser->second->getUserSocket(), message.c_str(), message.length(), 0);
	}
	return 0;
}

int Command::privmsg_user(User *U, std::string msg)
{
	int user = find_User_string(arguments[0]);
	std::map<int, User *>::iterator it = Users.find(user);
	if (it == Users.end())
	{
		U->reply(411);
		return -1;
	}
	// on peut pas s envoyer des msg a soit meme
	if (it->second->getUserNick() == U->getUserNick())
		return -1;
	std::string message =  U->getUserNick() + " " + msg;
	it->second->setUserChannel("");
	it->second->reply(502, message);
	return 0;
}

int Command::privmsg(User *U)
{
	U->setUserChannel(arguments[0]);
	if (arguments.empty() && arguments.size() < 1)
		return (U->reply(461, _command), -1);
	std::string msg;
	std::vector<std::string>::iterator itvec = arguments.begin();
	itvec++;
	for (; itvec != arguments.end(); itvec++)
		msg +=   *itvec + " ";
	//si le user est dans aucun channel
	if (arguments[0][0] != '#')
		return (privmsg_user(U, msg));
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		U->reply(401, arguments[0]);
		return (-1);
	}
	//verifie que le User est dans le chan
	if (it->second->verif_user(U->getUserSocket()) != 1)
		return (-1);

	// envoie un msg a tous les user dans le channel
	std::map<int, User *>::iterator itUser = it->second->getUsers().begin();

	for (;itUser != it->second->getUsers().end(); itUser++)
	{
		std::string message = ":"+ U->getUserNick() +" PRIVMSG " + arguments[0] + " :" + msg + "\r\n";
		std::cout << " message =  " << message << itUser->second->getUserSocket() << std::endl;
		if (itUser->second->getUserSocket() != U->getUserSocket())
			send(itUser->second->getUserSocket(), message.c_str(), message.length(), 0);
	}
	return 0;
}
