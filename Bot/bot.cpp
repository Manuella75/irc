
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <limits>
#include <cstdlib>
#include <map>
#include <regex.h>
#include <time.h>
#include <csignal>

int	socketDescriptor = 0;

std::string		parse(std::string contenu)
{
	std::string find = "<|#()#|>";
	size_t found = contenu.find(find);

	contenu.erase(found);
	return contenu;
}

std::string		parse2(std::string contenu)
{
	std::string find = "<|#()#|>";
	size_t found = contenu.find(find);

	contenu.erase(0, found -1);
	contenu.erase(0, 9);
	return contenu;
}

int	send_msg(std::string msg, int socketDescriptor)
{
	const char * test;
	test =  const_cast<char *>(msg.c_str());
	if (send(socketDescriptor, test, strlen(test), 0) < 0)
	{
		std::cout << "Émission du message impossible\n";
		close(socketDescriptor);
		return (-1);
 	}
	return 0;
}
std::string pars_msg(std::string message)
{
	size_t po = message.find("#BOTCHAN ::");

	message.erase(0, po);
	message.erase(0, 11);
	po = message.find("\r");
	while (po != std::string::npos)
	{
		message.erase(po, 1);
		po = message.find("\r");
	}
	po = message.find("\n");
	while (po != std::string::npos)
	{
		message.erase(po, 1);
		po = message.find("\n");
	}
	po = message.find(" ");
	while (po != std::string::npos)
	{
		message.erase(po, 1);
		po = message.find(" ");
	}
	return message;
}

void	send_question(std::map<std::string, std::string> question, int socketDescriptor)
{
	int ale;
	char msg[4096];
	std::string message;

	std::map<std::string, std::string>::iterator it = question.begin();

	srand(time(NULL));
	ale = (rand() % question.size()) + 1;
	for (int i = 0; i != ale - 1; i++)
		it++;
	send_msg("PRIVMSG #BOTCHAN ::" +it->first, socketDescriptor);
	usleep(1000000);
	while (1)
	{
		if (send_msg("PONG \n", socketDescriptor) < 0)
			return ;
		if (recv(socketDescriptor, msg, 4096, 0) < 0)
				std::cout << "** Le serveur n'a répondu dans la seconde.\n";
		message = pars_msg(msg);
		std::cout << "reponse = " << message << std::endl;
		std::cout << "reponse = " << it->second << std::endl;
		size_t po = it->second.find(" ");
		while (po != std::string::npos)
		{
			it->second.erase(po, 1);
			po = it->second.find(" ");
		}
		if (message == "")
			;
		else if (message == it->second)
		{
			std::string ms = "Bravo ! La réponse était bien : "  + it->second +  "!" ;
			send_msg("PRIVMSG #BOTCHAN ::" + ms +" \r\n", socketDescriptor);
			memset(msg, 0 , 4096);
			return ;
		}
		else
		{
			std::cout << "Mauvaise reponse" << std::endl;
			std::string ms = "Bravo ! La réponse était bien : "  + it->second +  "!" ;
			send_msg("PRIVMSG #BOTCHAN ::" + ms +" \r\n", socketDescriptor);
			memset(msg, 0 , 4096);
			return ;
		}
		memset(msg, 0 , 4096);
		usleep(1000000);
	}
}

	std::map<std::string, std::string> question;
	std::string contenu;
void signal_handler(int signal)
{
	(void)signal;
	std::cout << " quit sockt" << socketDescriptor << std::endl;
	send_msg("QUIT :Lost terminal\n", socketDescriptor);
	exit(0);
}

int main(int argc, char **argv)
{
	std::signal(SIGINT, signal_handler);
	std::string message;
	char msg[4096];
	int port = atoi(argv[1]);
	struct sockaddr_in serverAddress;
	struct hostent *hostInfo;

	if (argc != 2)
	{
		std::cerr << "Must be: \"./bot <port> <password>\"" << std::endl;
		exit (EXIT_FAILURE);
	}
	std::ifstream ifs("question.txt");
	if (!ifs)
	{
		std::cout << "error ifs\n" ;
		return 0;
	}
	while (getline(ifs, contenu))
		question.insert(std::pair<std::string, std::string> (parse(contenu), parse2(contenu)));
	ifs.close();
	if ((hostInfo = gethostbyname("127.0.0.1")) == NULL)
		return (std::cout << "error host \n", -1);
	if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (std::cout << "Socker error\n" , -1);
	serverAddress.sin_family = hostInfo->h_addrtype;
	memcpy((char *) &serverAddress.sin_addr.s_addr,
	hostInfo->h_addr_list[0], hostInfo->h_length);
	serverAddress.sin_port = htons(port);
	connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (send_msg("USER BOT\n", socketDescriptor) < 0)
		return 0;
	if (send_msg("JOIN #BOTCHAN\n", socketDescriptor) < 0)
		return 0;
	if(recv(socketDescriptor, msg, 4096, 0) < 0)
		std::cout << "** Le serveur n'a répondu dans la seconde.\n";
	std::cout << "msg = " << msg << std::endl;
	memset(msg, 0 , 4096);
	while (1)
	{
		if (send_msg("PONG \n", socketDescriptor) < 0)
			return 0;
		if(recv(socketDescriptor, msg, 4096, 0) == 0)
		{
			if (send_msg("QUIT :Lost terminal\n", socketDescriptor) < 0)
				return 0;
			return (std::cout << "** Le serveur n'a répondu dans la seconde.\n", 0);
		}
		std::cout << "msg = " << msg << std::endl;
		message = pars_msg(msg);
		std::cout << "message = " << message << std::endl;
		 if (message ==  "!question")
		 	send_question(question, socketDescriptor);
		memset(msg, 0 , 4096);
		usleep(1000000);
	}
	if (send_msg("QUIT :Lost terminal\n", socketDescriptor) < 0)
		return 0;
	return 0;
}
