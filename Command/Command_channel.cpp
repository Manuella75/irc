#include "Command.hpp"

int Command::join(User *U)
{
	if (arguments.empty())
		return (U->reply(461, _command), -1);
	if (arguments[0][0] != '#')
		return (U->reply(461, _command), -1);
	U->setUserChannel(arguments[0]);
	// si le channel n existe pas > on le cree
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		Channel *Cha = new Channel(arguments[0], U);
		Chan.insert(std::pair<std::string, Channel *>(arguments[0], Cha));
		send_message_chan(U, "JOIN", "", Cha);
		return (0);
	}
	//check si User est banni
	std::vector<int>::const_iterator itbanni = it->second->getBanni().begin();
	for (;itbanni != it->second->getBanni().end(); itbanni++)
		if (itbanni != it->second->getBanni().end())
			return (U->reply(474, it->first), -1);

	// si le User est deja dans le channel
	std::map<int, User *>::const_iterator itUser = it->second->getUsers().find(U->getUserSocket());
	if (itUser != it->second->getUsers().end())
		return -1;
		//on previent les autres dans le channel
	it->second->getUsers().insert(std::pair<int , User *>(U->getUserSocket(), U));
	send_message_chan(U, "JOIN", "", it->second);
	if (it->second->getTopic() != "")
		U->reply(332, it->second->getTopic());
	return (0);
}

int Command::part(User *U)
{
	U->setUserChannel(arguments[0]);
	if (arguments.empty())
		return (U->reply(461, _command), -1);
	//si le channel exist pas
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		U->reply(403, arguments[0]);
		return -1;
	}
	send_message_chan(U, "PART", "", it->second);
	// on trouve le User et on le delete
	std::map<int, User *>::const_iterator itUser;
	itUser = it->second->getUsers().find(U->getUserSocket());
	it->second->getUsers().erase(U->getUserSocket());
	return 0;
}

int Command::topic(User *U)
{
	U->setUserChannel(arguments[0]);

	if (arguments.empty())
		return (U->reply(461, _command), -1);
	if (check_operator(U, getChannel(arguments[0])) != 1)
	{
		U->reply(482);
		return 0;
	}
	std::string message;
	message = ":" + U->getUserNick() + " TOPIC " + arguments[0]  + " :"  + arguments[1] +"\r\n";
	std::cout << "lo" << message << std::endl;
	std::map<std::string, Channel *>::iterator it = Chan.find(U->getUserChannel());
	it->second->setTopic(arguments[0]);
	send_message_chan(U, "TOPIC " ," :" + arguments[1],  it->second);
	return 0;
}



int	Command::kick(User *U)
{
	if (arguments.empty() && arguments.size() < 1)
		return (U->reply(461, _command), -1);
	U->setUserChannel(arguments[0]);
	//check si chann exist
	std::map<std::string, Channel *>::iterator it = Chan.find(arguments[0]);
	if (it == Chan.end())
	{
		U->reply(401, arguments[0]);
		return (-1);
	}
	//check si le user est un modo
	if (check_operator(U, getChannel(arguments[0])) == 0)
	{
		U->reply(482, U->getUserNick());
		return -1;
	}
	std::map<int, User *>::iterator itUser = it->second->getUsers().begin();
	for (;itUser != it->second->getUsers().end(); itUser++)
	{
		if (arguments[1] == itUser->second->getUserNick())
		{
			if (check_operator(itUser->second, getChannel(arguments[0])) == 1)
				return(-1);
			if (itUser->second->getUserNick() == U->getUserNick())
				return -1;
			std::string	msg = ":" + U->getUserNick() + "!" + U->getUserHost() + "@localhost "
			+ "KICK " + it->second->getName() + " :" + itUser->second->getUserNick() +"\r\n";
			std::cout << "message = " << msg << std::endl;
			send(itUser->second->getUserSocket(), msg.c_str(), msg.length(), 0);
			//on ajoute le client dans un vec _banni
			it->second->addBanni(itUser->second->getUserSocket());
			// on delete le chann du users
			std::map<int, User *>::iterator ir;
			ir = this->get_Users().find(itUser->first);
			//on le delete du chann
			it->second->getUsers().erase(itUser->second->getUserSocket());
			return (0);
		}
	}
	U->reply(401, arguments[1]);
	return -1;
}



