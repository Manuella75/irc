#include "Channel.hpp"

Channel::Channel(std::string  name, User U) : _name(name)
{
	User  *Us =  new  User(U);
	U.setUserMode(1);
	U.setUserChannel(name);
	_Users.insert(std::pair<int , User *>(U.getUserSocket(), Us));

}

Channel:: Channel(Channel const & cpy)
{
	*this = cpy;
}
Channel::Channel(Channel * cpy)
{
	*this =  *cpy;
}

Channel &Channel::operator=(Channel const & rhs)
{
	_name = rhs.getName();
	_topic =  rhs.getTopic();
	_Users =  rhs.getUsers();
	return *this;
}

Channel::~Channel()
{}

//User *Channel::getAMember(std::string member) const
//{
//	std::map<int, User*>::const_iterator	it;
//	
//	for (it = User.begin(); it != User.end(); ++it)
//	{
//		if (it->second && it->second->getUserNick() == member)
//			return it->second;
//	}
//	return NULL;
//}

std::string const & Channel::getName() const
{
	return _name;
}

std::string const & Channel::getTopic() const
{
	return _topic;
}

std::map<int, User *> & Channel::getUsers()
{
	return _Users;
}

std::map<int, User *> const & Channel::getUsers() const
{
	return _Users;
}
