/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:32:08 by fboumell          #+#    #+#             */
/*   Updated: 2022/11/10 14:21:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/*  Command: MODE
    Parameters: <nickname>
                *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )

    The user MODE's are typically changes which affect either how the
    client is seen by others or what 'extra' messages the client is sent.
    A user MODE command MUST only be accepted if both the sender of the
    message and the nickname given as a parameter are both the same.  If
    no other parameter is given, then the server will return the current
    settings for the nick.

    i - marks a users as invisible;
    w - user receives wallops;
    o - operator flag;

    Numeric Replies:
        ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
        ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
*/

void mode(Server *serv, Message &msg)
{
	if (serv == NULL)
		return ;

    std::string str;

    if (msg.getParams().size() == 0)
    {
        str = ERR_NEEDMOREPARAMS;
        str += " " + msg.getSender()->getNickname() + " ";
        str += ":Error need more params.";
    }
	else if (msg.getParams()[0].find_first_of("#&+!") == 0)
		return ;
    else if (msg.getParams()[0] != msg.getSender()->getNickname())
    {
        str = ERR_USERSDONTMATCH;
        str += " " + msg.getSender()->getNickname() + " ";
        str += ":Cannot change mode for other users";
    }
	else if (msg.getParams().size() == 1)
	{
		str = RPL_UMODEIS;
        str += " " + msg.getSender()->getNickname() + " ";
        str += "+" + serv->getUser(msg.getSender()->getNickname())->getMode();
	}
    else
    {
        std::string mode = msg.getParams()[1];
        for (size_t i = 0; i < mode.size(); i++)
        {
            if (mode[i] == '+')
            {
                for (int j = i + 1; isalpha(mode[j]); j++)
                {
                    if (mode[j] == 'i' || mode[j] == 'w')
                        msg.getSender()->addMode(mode[j]);
                    else if (mode[j] != 'O' && mode[j] != 'o')
                    {
                        str = ERR_UMODEUNKNOWNFLAG;
                        str += " " + msg.getSender()->getNickname() + " ";
                        str += ":Unknown MODE flag";
                        msg.getSender()->send_to(str);
                    }
                }
            }
            if (mode[i] == '-')
            {
                for (int j = i + 1; isalpha(mode[j]); j++)
                {
                    if (mode[j] == 'i' || mode[j] == 'w' || mode[j] == 'o')
                        msg.getSender()->rmMode(mode[j]);
                    else if (mode[j] != 'O')
                    {
                        str = ERR_UMODEUNKNOWNFLAG;
                        str += " " + msg.getSender()->getNickname() + " ";
                        str += ":Unknown MODE flag";
                        msg.getSender()->send_to(str);
                    }
                }
            }
        }
        str = RPL_UMODEIS;
        str += " " + msg.getSender()->getNickname() + " ";
        str += "+" + serv->getUser(msg.getSender()->getNickname())->getMode();
        msg.getSender()->send_to(str);
        return ;
    }
    msg.getSender()->send_to(str);
}
