
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

int	send_msg(std::string msg, int socketDescriptor, struct sockaddr_in serverAddress)
{
	const char * test;
	test =  const_cast<char *>(msg.c_str());
	if (sendto(socketDescriptor, test, 5, 0,
	(struct sockaddr *) &serverAddress,
	sizeof(serverAddress)) < 0)
	{
		std::cout << "Émission du message impossible\n";
		close(socketDescriptor);
		return (-1);
 	}
	return 0;
}
int main()
{
	std::map<std::string, std::string> question;
	std::string contenu;
	int	socketDescriptor = 0;
	struct sockaddr_in serverAddress;

	int numRead;
	fd_set readSet;
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
	if (send_msg("test", socketDescriptor, serverAddress) < 0)
		return 0;
	std::string ind;
	char msg[240];
	FD_ZERO(&readSet);
	FD_SET(socketDescriptor, &readSet);
	timeVal.tv_sec = 1;
	timeVal.tv_usec = 0;
	std::cout << "here.\n";
		numRead = recv(socketDescriptor, msg, 240, 0);
		if (numRead < 0)
			std::cout << "** Le serveur n'a répondu dans la seconde.\n";
	std::cout << "here\n";
	while (1)
	{
		std::cout << "Msg" << std::endl;
		std::getline(std::cin , ind);
		if (std::cin.eof() == 1)
			return -1;
		if (send_msg(ind, socketDescriptor, serverAddress) < 0)
			return 0;
		usleep(100);
	}
	return 0;
}
