#include "Command.hpp"


void	Command::send_message_chan(User *U, std::string message, Channel chan)
{
	std::string msg;
	std::map<int, User *>::const_iterator itUser;

	for (itUser = chan.getUsers().begin(); itUser != chan.getUsers().end(); itUser++)
	{
		msg = ":" + U->getUserNick() + "!" + U->getUserHost() + "@localhost "
		 + message + " " + chan.getName() + "\r\n";
		std::cout << "msg =" << msg << " socket = " << itUser->second->getUserSocket() << std::endl;
		send(itUser->second->getUserSocket(), msg.c_str(), msg.length(), 0);
		msg.clear();
	}
}

void	Command::send_message(User *U, std::string message, std::string arg)
{
	std::string msg;

	msg = ":" + U->getUserNick() + "!" + U->getUserHost() + "@localhost "
	 + message + arg + "\r\n";
	std::cout << "msg =" << msg << " socket = " << U->getUserSocket() << std::endl;
	send(U->getUserSocket(), msg.c_str(), msg.length(), 0);
}

int	Command::setUser_name(User *U)
{
	std::map<int, User *>::iterator it;
	for (it = Users.begin(); it != Users.end(); ++it)
	{
		if (arguments[0] == it->second->getUserNick())
		{
			arguments[0] += "1";
			this->setUser_name(U);
			return 0;
		}
	}
	return 0;
}

int	Command::nicknameisue()
{
	std::map<int, User *>::iterator it;
	for (it = Users.begin(); it != Users.end(); ++it)
	{
		if (arguments[0] == it->second->getUserNick())
			return -1;
	}
	return 0;
}

int	Command::check_operator(User *U)
{
	if (U->getUserlastChannelOpe() == 1)
		return 1;
	if (U->oper == 1)
		return 1;

	return 0;
}
