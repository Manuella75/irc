// $Id: udp-client.cc 1473 2010-03-03 23:03:07Z latu $
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <limits>
#include <iostream>
#include <cstdlib>
#include <cstring>
  #include <sys/socket.h>
#define MAX_MSG 100
// 3 caractères pour les codes ASCII 'cr', 'lf' et '\0'
#define MSG_ARRAY_SIZE (MAX_MSG+3)
using namespace std;
int main()
{
 int socketDescriptor;
//  int numRead;
 unsigned short int serverPort;
 struct sockaddr_in serverAddress;
 struct hostent *hostInfo;
 struct timeval timeVal;
 fd_set readSet;
 // gethostbyname() reçoit un nom d'hôte ou une adresse IP en notation
 // standard 4 octets en décimal séparés par des points puis renvoie un
 // pointeur sur une structure hostent. Nous avons besoin de cette structure
 // plus loin. La composition de cette structure n'est pas importante pour
 // l'instant.
 hostInfo = gethostbyname("127.0.0.1");
 if (hostInfo == NULL) {
	std::cout << "here" << std::endl;
 exit(1);
 }
serverPort = 6667;
 // Création de socket. "AF_INET" correspond à l'utilisation du protocole IPv4
 // au niveau réseau. "SOCK_DGRAM" correspond à l'utilisation du protocole UDP
 // au niveau transport. La valeur 0 indique qu'un seul protocole sera utilisé
 // avec ce socket.
 socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
 if (socketDescriptor < 0) {
 cerr << "Impossible de créer le socket\n";
 exit(1);
 }
 serverAddress.sin_family = hostInfo->h_addrtype;
 memcpy((char *) &serverAddress.sin_addr.s_addr,
 hostInfo->h_addr_list[0], hostInfo->h_length);
 serverAddress.sin_port = htons(serverPort);
 connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

 // Envoi de la ligne au serveur
 if (sendto(socketDescriptor, "hello", 5, 0,
 (struct sockaddr *) &serverAddress,
 sizeof(serverAddress)) < 0) {
 cerr << "Émission du message impossible\n";
 close(socketDescriptor);
 exit(1);
 }
	std::cout << "here" << std::endl;
 // Attente de la réponse pendant une seconde.
 FD_ZERO(&readSet);
 FD_SET(socketDescriptor, &readSet);
 timeVal.tv_sec = 1;
 timeVal.tv_usec = 0;
//  if (select(socketDescriptor+1, &readSet, NULL, NULL, &timeVal)) {
 // Lecture de la ligne modifiée par le serveur.
//  memset(msg, 0x0, MSG_ARRAY_SIZE); // Mise à zéro du tampon
//  numRead = recv(socketDescriptor, msg, MAX_MSG, 0);
//  if (numRead < 0) {
//  cerr << "Aucune réponse du serveur ?\n";
//  close(socketDescriptor);
//  exit(1);
//  }
//  }
//  else {
//  cout << "** Le serveur n'a répondu dans la seconde.\n";
//  }
 // Invite de commande pour l'utilisateur et lecture des caractères jusqu'à la
 // limite MAX_MSG. Puis suppression du saut de ligne. Comme ci-dessus.
 while (1)
 {}
//  cout << "Saisie du message : ";
//  memset(msg, 0x0, MSG_ARRAY_SIZE); // Mise à zéro du tampon
//   cin.get(msg, MAX_MSG, '\n');
 // suppression des caractères supplémentaires et du saut de ligne
 cin.ignore(numeric_limits<streamsize>::max(),'\n');
 close(socketDescriptor);
 return 0;
}
