#include "Command.hpp"

int	Command::nick(User *U)
{
	// Vérifie qu'il y a bien un argument
	if (arguments.empty()) {
		U->reply(431);
		return -1;
	}
	for (size_t i = 0; i < arguments[0].size(); i++)
	{
		char c = arguments[0][i];
		if (c < '!' || c == '[' || c == ']' || c == '\\' || c == '`' || c == '_' || c == '<' || c =='>')
		{
			U->reply(432, arguments[0]);
			return -1;
		}
	}
	if (U->getUserNick() == "")
		return -1;
	if(arguments[0].size() > 9)
	{
		U->reply(432, arguments[0]);
		return -1;
	}
	// verifie si le user est deja utilise
	if (this->nicknameisue() == -1)
	{
		U->reply(433, arguments[0]);
		return -1;
	}
	std::string arg = " :" + arguments[0];
	this->send_message_all(U, "NICK", arg);
	U->setUserNick(arguments[0]);
	return 0;
}

int	Command::user(User  *U)
{
	std::string tmp = arguments[0];
	if (arguments.empty())
	{
		U->reply(461, _command);
		return (-1);
	}
	if (U->getUserNick().size() != 0)
		return (-1);
	U->realname = "Remi Darnet";
	this->setUser_name(U);
	U->setUserNick(arguments[0]);
	U->setUserHost(arguments[1]);
	 std::string message = ":localhost " + U->getUserNick() +
	  " " + U->getUserNick() + " " + U->getUserNick() + " " + U->getUserHost() + " * :" + U->realname;
	std::cout << " User message =" << message << std::endl;
	if (tmp != arguments[0])
	{
		std::string msg = ":" + tmp + "!" + U->getUserHost() + "@localhost "
		+ "NICK :" + arguments[0]  + "\r\n";
		send(U->getUserSocket(), msg.c_str(), msg.length(), 0);
	}
	std::string reponse = "001 " + U->getUserNick() + " :Welcome to the Network, " + U->getUserNick() + "[!" + U->getUserHost() + "@] \r\n";
	send(U->getUserSocket(), reponse.c_str(), reponse.size(), 0);
	U->cmduser = 1;
	return (1);
}

int Command::ping(User *U)
{
	this->send_message(U, "PONG", " :redarnet");
	return 0;
}

int Command::pong(User *U)
{
	std::cout << "User is " << U->_connected << std::endl;
	if (U->_connected == 0)
		U->_connected = 1;
	return 0;
}

int	Command::oper(User *U)
{
	if (arguments.empty() && arguments.size() < 1)
		return (U->reply(461, _command), -1);
	if (U->oper == 1)
		return 0;
	if (arguments[1] == "mdp")
	{
		std::string msg = ":" + U->getUserNick() + "!" + U->getUserHost() + "@localhost "
			+  "New OPER \r\n";
		std::cout << "msg =" << msg << " socket = " << U->getUserSocket() << std::endl;
		send(U->getUserSocket(), msg.c_str(), msg.length(), 0);
		U->oper = 1;
		// debann from all chan ?
		return 0;
	}
	U->reply(462);
	return -1;
}
