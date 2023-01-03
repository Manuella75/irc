/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettien <mettien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:53:23 by mettien           #+#    #+#             */
/*   Updated: 2023/01/03 00:17:21 by mettien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include <sys/socket.h>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <map>
#include <vector>
#include <poll.h>
#include "../Command/Command.hpp"
#include <utility>
#include <iostream>
#include "../Command/User.hpp"
#include "../Command/Channel.hpp"
#include "../Command/Command.hpp"

#define BUFFERSIZE 512

class Channel;
class Command;

class Server
{

private:

    // Attributes //
    int                 _port;
    std::string         _passwd;
    int                 _listenerSock;
    int                 _sock;
    std::vector<pollfd> _pfds;

    // Class //
    std::map<int , User *> Users;
	std::map<std::string, Channel *> Chan;
    // Create a socket //
    int createSocket();

    // Set up fd //
    void add_fd(int sock, int event, int isServer); // add a fd to the map

    // Wait for a connection //
    int waitConnection();

    // Connection with clients
    int newClient();

    // Receive data from Client //
    int rcvFromClient(int fd);
    
    void sendPing();

    void	deconnectUsers();
public:

    // Construct/Destruct //
    Server(std::string port, std::string passwd);
    ~Server();

    // Main loop //
    void        run();

    // Get functions //
    int         getPort() const;
    std::string getPasswd() const;
    User *      getUser(int fd) const;

    // Check functions //
    bool    valid_args(std::string input_port, std::string input_passwd);
    bool    hasPasswd() const;
	void	setUserInfo(std::string buff, int fd);

    // Exceptions//
    class NotValidArgsException : public std::exception
    {
        public:
            const char* what() const throw();
    };

    class SocketFailedException : public std::exception
    {
        public:
            const char* what() const throw();
    };

    class ClientConnectionFailedException : public std::exception
    {
        public:
            const char* what() const throw();
    };

};

#endif
