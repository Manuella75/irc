#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <cctype>
#include "User.hpp"

/* Channel (RFC 2812)
Channels names are strings (beginning with a '&', '#', '+' or '!' character) 
of length up to fifty (50) characters.  
Apart from the requirement that the first character is either '&', '#', '+' or '!',
the only restriction on a channel name is that it SHALL NOT contain 
any spaces (' '), a control G (^G or ASCII 7), a comma (',').  
Space is used as parameter separator and command is used as a list item
separator by the protocol). 
A colon (':') can also be used as a delimiter for the channel mask.
Channel names are case insensitive.
Each prefix characterizes a different channel type. The definition
of the channel types is not relevant to the client-server protocol
and thus it is beyond the scope of this document.  

cf Internet Relay Chat: Channel Management : https://www.rfc-editor.org/rfc/rfc2811
*/

class	Channel
{
	private :
	std::string		_Name;
	User			_ChanOwner;
	std::vector<User>	_Users;

	public :

	/* Constructor */
	Channel(std::string name);
	/* Destructor */
	~Channel(void);
};

#endif
