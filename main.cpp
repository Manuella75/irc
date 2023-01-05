/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <redarnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:53:04 by mettien           #+#    #+#             */
/*   Updated: 2023/01/06 00:33:04 by redarnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./includes/server.hpp"

bool is_running = true;

static void sig_handler(int ok)
{
	(void)ok;
	is_running = false;
}

int	main (int argc, char **argv)
{
	signal(SIGINT, sig_handler);

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
	-hamdle error msg
	-check pb fuser
	-ping pong
	-timeout
	-mode
	-envoie du welcome juste apres nick et user
	-user nickname max 9
	-max users
	-maxbacklog
	-user invisible a l'arrivee
	-message du nick si deja utiliser
	 -message mode du chan a larrivee
	 channel delete si ops part sans user connected

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
		- +v(voiced) donne voix a un user, si mode +m
		- +i(invite) , users doit etre inviter
		- +l, limite le nb de users ds un chan

		*User*

		-
 */

//check erase user + channel + signal delete tout
