// $Id: udp-server.cc 1473 2010-03-03 23:03:07Z latu $
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#define MAX_MSG 100
// 3 caractères pour les codes ASCII 'cr', 'lf' et '\0'
#define MSG_ARRAY_SIZE (MAX_MSG+3)
using namespace std;
int main()
{
 int listenSocket, i;
 unsigned short int listenPort, msgLength;
 socklen_t clientAddressLength;
 struct sockaddr_in clientAddress, serverAddress;
 char msg[MSG_ARRAY_SIZE];
 memset(msg, 0x0, MSG_ARRAY_SIZE); // Mise à zéro du tampon
 cout << "Entrez le numéro de port utilisé en écoute (entre 1500 et 65000) : ";
 cin >> listenPort;
 // Création de socket en écoute et attente des requêtes des clients
 listenSocket = socket(AF_INET, SOCK_DGRAM, 0);
 if (listenSocket < 0) {
 cerr << "Impossible de créer le socket en écoute\n";
 exit(1);
 }

 // On relie le socket au port en écoute.
 // On commence par initialiser les champs de la structure serverAddress puis
 // on appelle bind(). Les fonctions htonl() et htons() convertissent
 // respectivement les entiers longs et les entiers courts du rangement hôte
 // (sur x86 on trouve l'octet de poids faible en premier) vers le rangement
 // réseau (octet de poids fort en premier).
 serverAddress.sin_family = AF_INET;
 serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(listenPort);

 if (bind(listenSocket,
 (struct sockaddr *) &serverAddress,
 sizeof(serverAddress)) < 0) {
 cerr << "Impossible de lier le socket en écoute\n";
 exit(1);
 }
 // Attente des requêtes des clients.
 // C'est un appel non-bloquant ; c'est-à-dire qu'il enregistre ce programme
 // auprès du système comme devant attendre des connexions sur ce socket avec
 // cette tâche. Ensuite, l'exécution se poursuit.
 listen(listenSocket, 5);

 cout << "Attente de requête sur le port " << listenPort << "\n";
 while (1) {
 clientAddressLength = sizeof(clientAddress);
 // Mise à zéro du tampon de façon à connaître le délimiteur
 // de fin de chaîne.
 memset(msg, 0x0, MSG_ARRAY_SIZE);
 if (recvfrom(listenSocket, msg, MSG_ARRAY_SIZE, 0,
 (struct sockaddr *) &clientAddress,
 &clientAddressLength) < 0) {
 cerr << " Problème de réception du messsage\n";
 exit(1);
 }
 // Affichage de l'adresse IP du client.
 cout << " Depuis " << inet_ntoa(clientAddress.sin_addr);
 // Affichage du numéro de port du client.
 cout << ":" << ntohs(clientAddress.sin_port) << "\n";
 // Affichage de la ligne reçue
 cout << " Message reçu :\n";
//  msgLength = strlen(msg);
 // Conversion de cette ligne en majuscules.
//  for (i = 0; i < msgLength; i++)
//  msg[i] = toupper(msg[i]);
 // Renvoi de la ligne convertie au client.
//  if (sendto(listenSocket, msg, msgLength + 1, 0,
//  (struct sockaddr *) &clientAddress,
//  sizeof(clientAddress)) < 0)
//  cerr << "Émission du message modifié impossible\n";
 }
}
