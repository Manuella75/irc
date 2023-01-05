#include "Channel.hpp"

Channel::Channel(std::string  name, User *creator) : _name(name), _creator(creator)
{
	//User  *Us =  new  User(U);
	creator->setUserMode(1);
	creator->setUserChannel(name);
	_Users.insert(std::pair<int , User *>(creator->getUserSocket(), creator));
	_topic = "";
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

Channel::~Channel(){}

std::string const & Channel::getName() const
{
	return _name;
}

std::string const & Channel::getTopic() const
{
	return _topic;
}

void  Channel::setTopic(std::string topic)
{
	_topic = topic;
}

std::map<int, User *> & Channel::getUsers()
{
	return _Users;
}

std::map<int, User *> const & Channel::getUsers() const
{
	return _Users;
}

std::vector<int> const & Channel::getBanni() const
{
	return _Banni;
}

void  Channel::addBanni(int i)
{
	_Banni.push_back(i);
}
Channel::~Channel()
{}

User *Channel::getOneMember(std::string member) const
{
	std::map<int, User*>::const_iterator	it;

	for (it = _Users.begin(); it != _Users.end(); ++it)
	{
		if (it->second && it->second->getUserNick() == member)
			return it->second;
	}
	return NULL;
}

std::map<int, User*>&	Channel::getAllMembers(void)
{
 	return (this->_Users);
}

void	Channel::kickMember(User *member)
{
	if (member != NULL && _Users.find(member->getUserSocket()) != _Users.end())
		_Users.erase(member->getUserSocket());
}

void	Channel::addMember(User *member)
{
	if (member != NULL)
		_Users.insert(std::make_pair(member->getUserSocket(), member));
}

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
