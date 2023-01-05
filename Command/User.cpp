#include "User.hpp"

/* Constructor */

// User::User(std::string nick, std::string name, std::string password, std::string host) : _UserNick(nick), _UserName(name), _UserPassword(password),  _UserHost(host)
// {
	// return ;
// }

User::User (std::string host, int socket) : _UserHosts(host), _socket(socket)
{
	_nickname = "";
	oper = 0;
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


std::map<std::string, bool> const  User::getUserChannel() const
{
	return _channel;
}

std::string const  User::getUserlastChannel() const
{
	std::map<std::string, bool>::const_iterator it = _channel.end();
	it--;
	return it->first;
}

int   User::getUserlastChannelOpe() const
{
	std::map<std::string, bool>::const_iterator it = _channel.end();
	it--;
	return it->second;
}
void  User::setUserNick(std::string nick)
{
	_nickname = nick;
}
void  User::setUserHost(std::string host)
{
	_UserHosts = host;
}
void  User::setUserChannel(std::string chann, bool bo)
{
	// need to check si le channel existe
	std::map<std::string, bool>::iterator it = _channel.begin();
	for (; it != _channel.end(); it++)
	{
		if (it->first == chann)
			_channel.erase(it);
	}
	_channel.insert(std::pair<std::string, bool>(chann, bo));
	// _channel = chann;
}

void User::deleteUserlastChannel()
{
	std::map<std::string, bool>::iterator it = _channel.begin();
	for (;it != _channel.end(); it++)
	;
	it--;
	_channel.erase(it);
}

User::~User(void)
{
	return ;
}
