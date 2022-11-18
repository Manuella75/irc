/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettien <mettien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:53:04 by mettien           #+#    #+#             */
/*   Updated: 2022/11/17 17:35:12 by mettien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/server.hpp"

int	main (int argc, char **argv) 
{
	if (argc != 3)
	{
		std::cerr << "Must be: \"./ircserv <port> <password>\"" << std::endl;
		exit (EXIT_FAILURE);
	}
	try
    {
		Server server(argv[1],argv[2]);
		std::cout << "Port :" << server.getPort() << std::endl;
		std::cout << "Passwd :" << server.getPasswd() << std::endl;
		//std::cout << "hasPasswd :" << server.hasPasswd() << std::endl;
		server.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
		exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}

/* TO DO:

	-Nonblocking communication
	-read all the buffer from client
	-handle ip v6 ?
	-handle les dependancies
	-hamdle error msg	
 */
