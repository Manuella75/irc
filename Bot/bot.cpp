
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>



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

int main()
{
	std::vector<std::string> question;
	std::vector<std::string> reponse;
	std::string contenu;
	std::string rep;

	std::ifstream ifs("question.txt");
	if (!ifs)
		return 0;

	while (getline(ifs, contenu))
	{
		question.push_back(parse(contenu));
		reponse.push_back(parse2(contenu));
	}

	int socketDes;

	socketDes = socket(AF_INET,SOCK_DGRAM, 0);
	if (socketDes < 0)
		std::cout << "fail" << std::endl;
	char msg[3];
	struct sockaddr_in serverAddress;
	// <snipped/>
	if (sendto(socketDes, msg, strlen(msg), 0,
	(struct sockaddr *) &serverAddress,
	sizeof(serverAddress)) < 0)
	{
		std::cout << "Émission du message impossible\n";
		close(socketDes);
		return 0;
	}
		int numRead;
	numRead = recv(socketDes, msg, 3, 0);
	if (numRead < 0) {
		std::cout << "Aucune réponse du serveur ?\n";
		close(socketDes);
		return 0;
	 }

	return 0;
}
