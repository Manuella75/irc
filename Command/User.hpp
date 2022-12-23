#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>
#include <map>

class	User
{
	private :
<<<<<<< HEAD
	std::string	_nickname;
=======

	std::string	_UserNick;
	std::string _cmd;
>>>>>>> master
	// std::string	_UserName;
	// std::string	_UserPassword;
	std::string	_UserHosts;
	int _mode;
	int _socket;
	std::string _channel;

	public :
<<<<<<< HEAD
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
=======

	/* Constructor */
	User(std::string cmd);
	User(User const & cpy);
	User &operator=(User const & rhs);
	std::string const & getUserHost() const;
	
	// User(std::string nick, std::string name, std::string password ,std::string host);
	/* Destructor */
	~User(void);

	/* Member functions */
>>>>>>> master
};

#endif
