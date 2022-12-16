#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>

class	User
{
	private :

	std::string	_UserNick;
	// std::string	_UserName;
	// std::string	_UserPassword;
	std::string	_UserHosts;
	std::string  usernamer;
	int  mode;
	std::string realname;
	public :

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
