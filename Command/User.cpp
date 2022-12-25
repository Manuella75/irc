#include "User.hpp"

/* Constructor */

// User::User(std::string nick, std::string name, std::string password, std::string host) : _UserNick(nick), _UserName(name), _UserPassword(password),  _UserHost(host)
// {
	// return ;
// }

User::User (std::string host, int socket) : _UserHosts(host), _socket(socket)
{
	_mode = 2;
	_nickname = "yo ";
	_channel = "";
}

User::User(User const & cpy){
	*this = cpy;
}

User::User(User * cpy){
	*this = *cpy;
}

User & User::operator=(User const & rhs)
{
	this->_UserHosts = rhs.getUserHost();
	this->_nickname = rhs.getUserNick();
	this->_socket = rhs.getUserSocket();
	this->_mode = rhs.getUserMode();
	this->_channel = rhs.getUserChannel();
	return *this;
}

void User::setCmd(std::string command)
{
	this->_cmd = command;
}


std::string const & User::getUserHost() const
{
	return _UserHosts;
}

std::string const  User::getUserNick() const
{
	return _nickname;
}

int  User::getUserSocket() const
{
	return _socket;
}

int  User::getUserMode() const
{
	return _mode;
}

void  User::setUserMode(int mode)
{
	_mode = mode;
}

std::string const  User::getUserChannel() const
{
	return _channel;
}

void  User::setUserNick(std::string nick)
{
	_nickname = nick;
}

void  User::setUserChannel(std::string chann)
{
	_channel = chann;
}

User::~User(void)
{
	return ;
}
