
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <limits>
#include <cstdlib>
#include <map>
#include <time.h>

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

	contenu.erase(0, found);
	contenu.erase(0, 8);
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

void	send_question(std::map<std::string, std::string> question, int socketDescriptor)
{
	int ale;
	char msg[4096];
	const char * s;

	std::map<std::string, std::string>::iterator it = question.begin();

	srand(time(NULL));
	ale = (rand() % question.size()) + 1;
	for (int i = 0; i != ale; i++)
		it++;
	send_msg(it->first, socketDescriptor);
	s =  const_cast<char *>(it->second.c_str());
	if (recv(socketDescriptor, msg, 4096, 0) < 0)
			std::cout << "** Le serveur n'a répondu dans la seconde.\n";
	if (strncmp(msg , s, strlen(s)) == 0)
		std::cout << "GJ" << std::endl;
	else
		std::cout << "wrong" << std::endl;

}

int main()
{
	std::map<std::string, std::string> question;
	std::string contenu;
	int	socketDescriptor = 0;
	struct sockaddr_in serverAddress;
	struct timeval timeVal;

	std::ifstream ifs("question.txt");
	if (!ifs)
		return 0;

	while (getline(ifs, contenu))
		question.insert(std::pair<std::string, std::string> (parse(contenu), parse2(contenu)));
	struct hostent *hostInfo;

	if ((hostInfo = gethostbyname("127.0.0.1")) == NULL)
		return (std::cout << "error host \n", -1);
	if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (std::cout << "Socker error\n" , -1);
	serverAddress.sin_family = hostInfo->h_addrtype;
	memcpy((char *) &serverAddress.sin_addr.s_addr,
	hostInfo->h_addr_list[0], hostInfo->h_length);
	serverAddress.sin_port = htons(6667);
	connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (send_msg("test", socketDescriptor) < 0)
		return 0;
	std::string ind;
	char msg[4096];
	char *s = strdup("!question");
	timeVal.tv_sec = 1;
	timeVal.tv_usec = 0;
	while (1)
	{
		std::cout << "Msg" << std::endl;
		std::getline(std::cin , ind);
		if (std::cin.eof() == 1)
			return -1;
		if (send_msg(ind, socketDescriptor) < 0)
			return 0;
		if(recv(socketDescriptor, msg, 4096, 0) < 0)
			std::cout << "** Le serveur n'a répondu dans la seconde.\n";
		std::cout << "msg = " << msg << std::endl;
		if (strncmp(msg , s, strlen(s)) == 0)
			send_question(question, socketDescriptor);
		memset(msg, 0 , 4096);

		usleep(100);
	}
	return 0;
}
//code pour envoyer au bot
/*
	const char * test;
	test =  const_cast<char *>(cmd.c_str());
	std::cout << "cmd = " << cmd << std::endl;
	usleep(1000);
	if (it != Users.end())
	{
		if ((send(it->first, test, strlen(test), 0)) < 0)
			std::cout << "Impo" << std::endl;
	}
	*/
