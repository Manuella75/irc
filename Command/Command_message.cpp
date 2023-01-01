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
