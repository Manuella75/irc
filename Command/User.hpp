#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>
#include <map>

class	User
{
	private :
	std::string	_nickname;
	// std::string	_UserName;
	// std::string	_UserPassword;
	std::string	_UserHosts;
	int _mode;
	int _socket;
	std::string _channel;

	public :
		std::string  username;
		std::string realname;
		/* Constructor */
		User(std::string host, int socket);
		User(User const & cpy);
		User &operator=(User const & rhs);
		std::string const & getUserHost() const;
		std::string			getUserNick();
		int					getUserMode();
		void				setUserMode(int mode);
		void				setUserChannel(std::string chann);
		std::string			getUserChannel();
		int					getUserSocket();
		/* Destructor */
		~User(void);
};

#endif
