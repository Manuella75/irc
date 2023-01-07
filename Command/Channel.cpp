#include "Channel.hpp"

Channel::Channel(std::string  name, User *creator) : _name(name), _creator(creator)
{
	// User  *Us =  new  User(creator);
	_channelOp =  creator->getUserSocket();
	std::cout << "CHan op = "<< this->getChannelOp() << std::endl;
	std::cout << "CHan op = "<< this->getName() << std::endl;
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
	_channelOp =  rhs._channelOp;
	return *this;
}

Channel::~Channel(){}



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

int		Channel::getChannelOp()
{
	return _channelOp;
}


std::string const & Channel::getTopic() const
{
	return _topic;
}
int		Channel::verif_user(int socket)
{
	std::map<int, User *>::iterator it = _Users.begin();
	for (; it != _Users.end(); it++)
	{
		if (it->first == socket)
			return 1;
	}
	return 0;
}
