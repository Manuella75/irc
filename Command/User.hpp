#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>
#include <map>

class	User
{
	private :

	std::string	Nickname;
	// std::string	_UserName;
	// std::string	_UserPassword;
	std::string	_UserHosts;
	public :

	int socket;
	std::map<int, User *> Users;
	std::string  username;
	int  mode;
	std::string realname;
	/* Constructor */
	User(std::string host);
	User(User const & cpy);
	User &operator=(User const & rhs);
	std::string const & getUserHost() const;
	std::string  getUserNick();

	// User(std::string nick, std::string name, std::string password ,std::string host);
	/* Destructor */
	~User(void);

	/* Member functions */
};

#endif
