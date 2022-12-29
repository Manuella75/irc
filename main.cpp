/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettien <mettien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:53:04 by mettien           #+#    #+#             */
/*   Updated: 2022/12/29 22:25:15 by mettien          ###   ########.fr       */
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
	-check pb fuser
	-ping pong
	-timeout
	-mode
	-envoie du welcome juste apres nick et user
	-user nickname max 9
	-max users
	-maxbacklog

	Server Operator:
	-/OPER <userid> <password> (authentification pr etre IRCOPERATOR)
	-/KILL <nick> [message] (virer qq du serveur,deconnexion)
	-/ISBANNED <channel> <nickname> (savoir si un user est ban)

	ChanOperator:
	-/TOPIC #cool Bienvenue sur #COOL =) (change topic du chan)
	-/KICK <channel> <nick> [message] (virer qq du chan)
	-/INVITE <channelname> <nickname> (invite qq sur chan,si mode +i)

	MODE
		*Channel*
		- +m(moderated), seuls users +v peuvent parler
		- +i(invite) , users doit etre inviter
		- +l, limite le nb de users ds un chan
		- +
 */
