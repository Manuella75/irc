#include "Command.hpp"

// int	admin(void){return (0);}
// int	akill(void){return (0);}
// int	away(void){return (0);}
// int	cleandead(void){return (0);}
// int	clearakills(void){return (0);}
// int	connect(void){return (0);}
// int	die(void){return (0);}
// int	expban(void){return (0);}
// int	globops(void){return (0);}
// int	help(void){return (0);}
// int	importmotd(void){return (0);}
// int	info(void){return (0);}
// int	invite(void){return (0);}
// int	isbanned(void){return (0);}
// int	ison(void){return (0);}
// int	join(void){return (0);}
// int	kick(void){return (0);}
// int	kill(void){return (0);}
// int	killban(void){return (0);}
// int	kline(void){return (0);}
// int	links(void){return (0);}
// int	list(void){return (0);}
// int	lusers(void){return (0);}
// int	me(void){return (0);}
// int	mode(void){return (0);}
// int	motd(void){return (0);}
// int	msg(void){return (0);}
// int	names(void){return (0);}
int	nick(User  U)
{
	std::cout <<  U.getUserHost() << std::endl;
	return (0);
	}
// int	notice(void){return (0);}
// int	oper(void){return (0);}
// int	part(void){return (0);}
// int	pass(void){return (0);}
// int	privmsg(void){return (0);}
// int	query(void){return (0);}
// int	quit(void){return (0);}
// int	rakill(void){return (0);}
// int	rehash(void){return (0);}
// int	shun(void){return (0);}
// int	silence(void){return (0);}
// int	squit(void){return (0);}
// int	stats(void){return (0);}
// int	summon(void){return (0);}
// int	time(void){return (0);}
// int	topic(void){return (0);}
// int	unban(void){return (0);}
// int	unkline(void){return (0);}
// int	userhost(void){return (0);}
// int	users(void){return (0);}
// int	version(void){return (0);}
// int	wall(void){return (0);}
// int	wallops(void){return (0);}
// int	who(void){return (0);}
// int	whois(void){return (0);}
// int	whowas(void){return (0);}

int	ft_exec_cmd(std::string cmd,std::map<int, User *> Users, int clientSock)
{
	// std::string command[55] = {"ADMIN", "AKILL", "AWAY", "CLEANDEAD", "CLEARAKILLS", "CONNECT", "DIE", "EXPBAN", "GLOBOPS", "HELP", "IMPORTMOTD", "INFO", "INVITE", "ISBANNED", "ISON", "JOIN", "KICK", "KILL", "KILLBAN", "KLINE", "LINKS", "LIST", "LUSERS", "ME", "MODE", "MOTD", "MSG", "NAMES", "NICK", "NOTICE", "OPER", "PART", "PASS", "PRIVMSG", "QUERY", "QUIT", "RAKILL", "REHASH", "SHUN", "SILENCE", "SQUIT", "STATS", "SUMMON", "TIME", "TOPIC", "UNBAN", "UNKLINE", "USERHOST", "USERS", "VERSION", "WALL", "WALLOPS", "WHO", "WHOIS", "WHOWAS"};
	std::string command[1] = {"NICK"};

	std::map<int, User *>::iterator it = Users.find(clientSock);

	// int	(*functptr[])() = {&admin, &akill, &away, &cleandead, &clearakills, &connect, &die, &expban, &globops, &help, &importmotd, &info, &invite, &isbanned, &ison, &join, &kick, &kill, &killban, &kline, &links, &list, &lusers, &me, &mode, &motd, &msg, &names, &nick, &notice, &oper, &part, &pass, &privmsg, &query, &quit, &rakill, &rehash, &shun, &silence, &squit, &stats, &summon, &time, &topic, &unban, &unkline, &userhost, &users, &version, &wall, &wallops, &who, &whois, &whowas};
	int	(*functptr[])(User) = {&nick};

	std::cout << "second = " << it->second->getUserHost() <<  std::endl;
	int	ret;
	(void)cmd;
	// for (int i = 0; i < 55; i++)
	// {
		// if (command[i] == cmd)
		//
			ret = (*functptr[0])(*it->second);
			return (ret); // verifier code d'erreurs dans la doc IRC
		// }
	// }
	return (-1) ; // aucune commande ne correspond // verifier code d'erreur dans la doc IRC
}

/* Constructor */

Command::Command(std::string msg, std::map<int, User*> Users, int clientSock) : _BrutMsg(msg), _cmd("") ,_args("")
{
	size_t	pos;

	std::cout << "Constructeur called for : " << this->_BrutMsg << std::endl; // A supp
	(void)Users;
	if (msg[0] == '/')
	{
		pos = msg.find(' '); // Si la fonction find trouve la premiere occurance elle renvoie sa position, sinon elle renvoie la valeur npos qui vaut -1
		if (pos == msg.npos)
		{
			this->_cmd = msg.substr(1);
		}
		else
		{
			std::cout << "pos = " << pos << std::endl;
			this->_cmd = msg.substr(1, pos);
			this->_args = msg.substr(pos + 1);
		}
	}
	/* Convertir la commande en Majuscule */
	for (size_t i = 0; i < this->_cmd.length(); ++i)
	{
		this->_cmd[i] = toupper(this->_cmd[i]);
	}
	std::cout << "CMD = " << this->_cmd << std::endl << "ARGS = " << this->_args << std::endl; // A supp

	ft_exec_cmd(this->_cmd, Users, clientSock); // code retour ??
	return ;
}

/* Destructor */

Command::~Command(void)
{
	return ;
}
