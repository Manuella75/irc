/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettien <mettien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:53:23 by mettien           #+#    #+#             */
/*   Updated: 2022/11/18 20:16:34 by mettien          ###   ########.fr       */
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
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno> // a enlever
#include <map>
#include <vector>
#include <poll.h>
#include "../Command/Command.hpp"
#include "../Command/User.hpp"

// class Command;
// class User;


class Server
{

private:
    
    // Attributes //
    int                 _port;
    std::string         _passwd;
    int                 _listenerSock;
    int                 _sock;
    int                 _lastFd; // a changer par map des Users
    std::map<int,pollfd> _pfds;

    // Class //
    std::map<int, User*> Users; 
    // Create a socket //
    int createSocket();
    
    // Create polling sock //
    int polling();
    
    // Set up fd //
    void set_Event(int sock, int event); // add a fd to the map

    // Wait for a connection //
    int waitClient();
    
    // Connection with clients
    int connection();
    
public:

    // Construct/Destruct //
    Server(std::string port, std::string passwd);
    ~Server();
    
    // Send message to client //
    void        sendmsg(int clientSock, std::string msg);

    // Main loop //
    void        run();

    // Get functions //
    int         getPort() const;
    std::string getPasswd() const;

    // Check functions //
    bool valid_args(std::string input_port, std::string input_passwd);
    bool hasPasswd() const;

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