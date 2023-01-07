#include "User.hpp"

/* Constructor */

// User::User(std::string nick, std::string name, std::string password, std::string host) : _UserNick(nick), _UserName(name), _UserPassword(password),  _UserHost(host)
// {
	// return ;
// }

User::User (std::string host, int socket) : _socket(socket), _UserHosts(host), _lastPing(time(0))
{
	//_mode = "i";
	_connected = true;
	oper = 0;
	_nickname = "";
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
	return *this;
}

void	User::disconnect(void)
{
	this->_connected = false;
}

void User::setCmd(std::string command)
{
	this->_cmd = command;
}

size_t	User::getLastPing(void) const
{
	return (time(0) - this->_lastPing);
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


void  User::setUserNick(std::string nick)
{
	_nickname = nick;
}
void  User::setUserHost(std::string host)
{
	_UserHosts = host;
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

void	User::setUserChannel(std::string channel)
{
	_channel = channel;
}


bool	User::getConnected() const
{
	return _connected;
}

void 	User::resetPing()
{
	_lastPing = time(0);
}


User::~User(void)
{
	return ;
}
