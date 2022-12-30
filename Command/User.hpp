#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

class	User
{
	private :
	std::string	_nickname;
	std::string	_UserHosts;
	int _mode;
	int _socket;
	std::string _channel;
	std::string _cmd;

	public :
		std::string realname;
		/* Constructor */
		User(std::string host, int socket);
		User(User const & cpy);
		User(User  * cpy);
		User &operator=(User const & rhs);
		std::string const & getUserHost() const;
		std::string		const	getUserNick() const;
		int					getUserMode() const ;
		void				setUserMode(int mode);
		void				setUserNick(std::string Nick);
		void				setUserHost(std::string host);
		void				setUserChannel(std::string chann);
		void	setCmd(std::string command);
		std::string			const getUserChannel() const;
		int					getUserSocket() const;
		/* Destructor */
		~User(void);
};

#endif
