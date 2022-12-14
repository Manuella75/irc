/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:11:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/10 14:07:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_HPP
# define LIBS_HPP

/* libraries */
# include <cstdlib>
# include <string>
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <memory.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netdb.h>
# include <poll.h>
# include <unistd.h>
# include <fcntl.h>
# include <cstring>
# include <vector>
# include <sstream>
# include <fstream>
# include <algorithm>
# include <signal.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/stat.h>
# include <time.h>

/* colors */
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[0;36m"
# define RED "\033[4;31m"
# define RESET "\033[0m"

/* defines */
# define BUFFER_SIZE	512
# define BOTNAME		"DistinguichCatBot"

/* typedefs */
typedef int	sockfd;
class Server;
class Message;
typedef void (*ft_cmd)(Server*, Message&);

/* global */
extern bool server_running;

/* class headers */
# include "class/Message.hpp"
# include "class/Client.hpp"
# include "class/Channel.hpp"
# include "class/Server.hpp"
# include "class/Configuration.hpp"

/* headers */
# include "proto.hpp"
# include "err_def.hpp"
# include "rpl_def.hpp"

#endif
