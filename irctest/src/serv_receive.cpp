/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_receive.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:48:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:36:55 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

/* This function will parse the client's buffer into its commands list, and execute each of them */
static void	buf_to_cmd(Server *server, Client *client)
{
	if (server == NULL || client == NULL)
		return ;

	char	*buffer = strdup(client->getBuffer().c_str());
	std::list<std::string>	buf_list(split(buffer, "\r\n"));
	std::map<std::string, void (*)(Server*, Message&)>	cmdlist = server->getCmdList();

	free(buffer);
	client->setBuffer("");

	for (std::list<std::string>::const_iterator it = buf_list.begin(); it != buf_list.end(); ++it)
	{
		Message new_msg(client, *it);
		std::cout << "Message from client #" << client->getFd() << " (" << client->getNickname() << ") << [" << *it << "]" << std::endl;
		if (new_msg.parse_msg() && cmdlist.find(new_msg.getCommand()) != cmdlist.end())
		{
			if (client->getAuthorize() || (new_msg.getCommand() == "PASS"))
				cmdlist[new_msg.getCommand()](server, new_msg);
		}
	}
}

void	serv_receive(sockfd clientfd, Server *server)
{
	char					buffer[BUFFER_SIZE + 1];
	ssize_t					len;

	memset(buffer, 0, BUFFER_SIZE + 1);
	len = recv(clientfd, buffer, BUFFER_SIZE, MSG_DONTWAIT);
	std::string	buf_str(buffer);

	if (server == NULL)
		return ;

	server->getUser(clientfd)->resetTime();

	if (len < 0)
	{
		std::cout << "Error recv(): " << strerror(errno) << std::endl;
		server->getUser(clientfd)->setBuffer("");
	}
	else if (len == 0)
		server->getUser(clientfd)->disconnect();
	else if (len > 0 && (buf_str.rfind("\r\n") != buf_str.size() - 2))
	{
		std::cout << "Message from client #" << clientfd << " (" << server->getUser(clientfd)->getNickname() << ") incomplete! Adding it to the buffer..." << std::endl;
		server->getUser(clientfd)->setBuffer(server->getUser(clientfd)->getBuffer() + buffer);
	}
	else
	{
		server->getUser(clientfd)->setBuffer(server->getUser(clientfd)->getBuffer() + buffer);
		buf_to_cmd(server, server->getUser(clientfd));
	}
}
