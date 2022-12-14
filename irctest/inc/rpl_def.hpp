/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_def.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:21:26 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/04 16:39:07 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_DEF_HPP
# define RPL_DEF_HPP

// [<prefix>] RPL/ERR <nickname> [<params>]

# define RPL_WELCOME    "001"		// "Welcome to the Internet Relay Network <nick>!<user>@<host>"
# define RPL_YOURHOST   "002"		// "Your host is <servername>, running version <ver>"
# define RPL_CREATED    "003"		// "This server was created <date>"
# define RPL_MYINFO     "004"		// "<servername> <version> <available user modes> <available channel modes>"
# define RPL_UMODEIS    "221"       // "<user mode string>"  || To answer a query about a client's own mode, RPL_UMODEIS is sent back.                                                                                       
# define RPL_TOPIC		"332"		// "<channel> :<topic>"
# define RPL_VERSION    "351"       // "<version>.<debuglevel> <server> :<comments>"
# define RPL_NAMREPLY   "353"       // "( "=" / "*" / "@" ) <channel> :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )   || "@" is used for secret channels, "*" for private channels, and "=" for others (public channels).
# define RPL_ENDOFNAMES "366"       // "<channel> :End of NAMES list"   ||  To reply to a NAMES message, a reply pair consisting
                                                                            /*of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
                                                                            server back to the client.  If there is no channel
                                                                            found as in the query, then only RPL_ENDOFNAMES is*/
# define RPL_INFO       "371"       // ":<string>"
# define RPL_MOTD       "372"       // ":- <text>"
# define RPL_ENDOFINFO  "374"       // ":End of INFO list"
# define RPL_MOTDSTART  "375"       // ":- <server> Message of the day - "
# define RPL_ENDOFMOTD  "376"       // ":End of MOTD command"
    
              

        

# define RPL_YOUREOPER	"381"		// ":You are now an IRC operator"

#endif
