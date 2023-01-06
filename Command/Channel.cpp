#include "Channel.hpp"

Channel::Channel(std::string  name, User *creator) : _name(name), _creator(creator)
{
	creator->setUserMode(1);
	creator->setUserChannel(name, 1);
	Members.insert(std::pair<int , User *>(creator->getUserSocket(), creator));
	_topic = "";
	_modModer = false;
	_modInvit = false;	
	_modLimit = false;
	_maxUsers = 0;
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
	Members =  rhs.getUsers();
	return *this;
}

Channel::~Channel(){}



void  Channel::setTopic(std::string topic)
{
	_topic = topic;
}

std::map<int, User *> & Channel::getUsers()
{
	return Members;
}

std::map<int, User *> const & Channel::getUsers() const
{
	return Members;
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

	for (it = Members.begin(); it != Members.end(); ++it)
	{
		if (it->second && it->second->getUserNick() == member)
			return it->second;
	}
	return NULL;
}

std::map<int, User*>&	Channel::getAllMembers(void)
{
 	return (this->Members);
}

void	Channel::kickMember(User *member)
{
	if (member != NULL && Members.find(member->getUserSocket()) != Members.end())
		Members.erase(member->getUserSocket());
}

void	Channel::addMember(User *member)
{
	if (_modLimit == true && (Members.size() >= _maxUsers))
	{
		member->reply(471, _name);
		return ;
	}
	Members.insert(std::make_pair(member->getUserSocket(), member));
}

std::string const & Channel::getName() const
{
	return _name;
}

std::string const & Channel::getTopic() const
{
	return _topic;
}
