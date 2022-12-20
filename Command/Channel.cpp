#include "Channel.hpp"

Channel::Channel(std::string  name, User U) : _name(name)
{
	User  *Us =  new  User(U);
	_Users.insert(std::pair<int , User *>(U.socket, Us));

}

Channel::~Channel()
{}

std::string const & Channel::getName() const
{
	return _name;
}

std::string const & Channel::getTopic() const
{
	return _topic;
}

int Channel::getMode() const
{
	return _mode;
}


std::map<int, User *> & Channel::getUsers()
{
	return _Users;
}
