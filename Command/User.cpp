#include "User.hpp"

/* Constructor */

// User::User(std::string nick, std::string name, std::string password, std::string host) : _UserNick(nick), _UserName(name), _UserPassword(password),  _UserHost(host)
// {
	// return ;
// }

User::User (std::string host) : _UserHost(host)
{}

User::User(User const & cpy){
	*this = cpy;
}

User & User::operator=(User const & rhs)
{
	this->_UserHost = rhs.getUserHost();
	return *this;
}

std::string const & User::getUserHost() const
{
	return _UserHost;
}
/* Destructor */

User::~User(void)
{
	return ;
}
