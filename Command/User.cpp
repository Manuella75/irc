#include "User.hpp"

/* Constructor */

// User::User(std::string nick, std::string name, std::string password, std::string host) : _UserNick(nick), _UserName(name), _UserPassword(password),  _UserHost(host)
// {
	// return ;
// }

User::User (std::string host) : _UserHosts(host)
{
	mode = 0;
	Nickname = "";
}

User::User(User const & cpy){
	*this = cpy;
}

User & User::operator=(User const & rhs)
{
	this->_UserHosts = rhs.getUserHost();
	// this->_UserNick = rhs.getUserNick();
	return *this;
}

std::string const & User::getUserHost() const
{
	return _UserHosts;
}

std::string  User::getUserNick()
{
	return Nickname;
}
/* Destructor */

User::~User(void)
{
	return ;
}
