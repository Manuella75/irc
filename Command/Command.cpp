#include "Command.hpp"
std::vector<std::string> split_splace1(std::vector<std::string>& v)
{
	std::vector<std::string>::iterator it;
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::string &str = *it;
		size_t pos = str.find(" ");
		while (pos != std::string::npos)
		{
			str.erase(pos, 1);
			pos = str.find(" ");
		}
		pos = str.find("\n");
		while (pos != std::string::npos)
		{
			str.erase(pos, 1);
			pos = str.find("\n");
		}
	}
	return v;
}


int Command::mode(User *U)
{
	std::cout << "COMMAND MODE" << std::endl;
	(void)U;
	return -1;
}

std::map<int, User *>  Command::get_Users()
{
	return this->Users;
}

std::map<std::string, Channel *>  Command::get_Chan()
{
	return this->Chan;
}

int	Command::ft_exec_cmd(int clientSock)
{
	std::string command[12] = {"NICK", "USER", "JOIN",
	 "PART" , "MODE", "PING", "PRIVMSG", "TOPIC", "KICK", "OPER" ,
	  "PONG", "NOTICE"};

	std::map<int, User *>::iterator it = Users.find(clientSock);
	int	(Command::*functptr[])(User*) = {&Command::nick, &Command::user,
		 &Command::join, &Command::part, &Command::mode,&Command::ping, &Command::privmsg,
		 &Command::topic, &Command::kick, &Command::oper, &Command::pong, &Command::notice};

	int	ret;
	for (int i = 0; i < 13; i++)
	{
		if (command[i] == _command)
		{
			ret = (this->*functptr[i ])(it->second);
			std::cout << "Retour cmd = " << ret << std::endl;
			return (ret);
		}
	}
	return 0;
}


Command::Command(std::string msg, std::map<int, User*> Us, int clientSock, std::map<std::string, Channel *> Chann) : _BrutMsg(msg)
{
	std::istringstream ss(msg);
	std::string token;

	Users = Us;
	Chan = Chann;
	while (std::getline(ss, token, ' '))
		arguments.push_back(token);
	arguments = split_splace1(arguments);
	_command = arguments[0];
	arguments.erase(arguments.begin());
	ft_exec_cmd(clientSock); // code retour ??
	arguments.clear();
	return ;
}


Command::~Command(void)
{
	return ;
}
