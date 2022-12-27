#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>

class	User
{
	private :

	int			_fd;
	std::string	_UserNick;
	std::string _cmd;
	// std::string	_UserName;
	// std::string	_UserPassword;
	std::string	_UserHost;

	public :

	/* Constructor */
	User();
	User(User const & cpy);
	User &operator=(User const & rhs);
	std::string const & getUserHost() const;
	
	// User(std::string nick, std::string name, std::string password ,std::string host);
	/* Destructor */
	~User(void);

	/* Member functions */
	void setCmd(std::string command);
	void setBuf(std::string buffer);
};

#endif
