#include "User.hpp"

/* Constructor */

// User::User(std::string nick, std::string name, std::string password, std::string host) : _UserNick(nick), _UserName(name), _UserPassword(password),  _UserHost(host)
// {
	// return ;
// }

User::User (std::string host, int socket) : _UserHosts(host), _socket(socket)
{
	_mode = 2;
	_nickname = "";
	_channel = "";
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
	return _nickname;
}

int  User::getUserSocket()
{
	return _socket;
}

int  User::getUserMode()
{
	return _mode;
}

void  User::setUserMode(int mode)
{
	_mode = mode;
}

std::string  User::getUserChannel()
{
	return _channel;
}

void  User::setUserChannel(std::string chann)
{
	_channel = chann;
}

User::~User(void)
{
	return ;
}
