#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "User.hpp"

class Channel
{
	private:
		std::string _name; // channel name
		std::string _topic; // chanel topic
		std::map<int, User *> _Users; // channel users
		std::vector<int>	_Banni;
	public :
	 	Channel(std::string const  name, User U);
		Channel(Channel const &cpy);
		Channel(Channel * cpy);
		~Channel();
		Channel & operator=(Channel const & rhs);
		std::string const & getName() const;
		std::string const & getTopic() const;
		std::map<int, User *> const  & getUsers() const;
		std::vector<int> const  & getBanni() const;
		void	setTopic(std::string topic);
		std::map<int, User *>  & getUsers();

};
#endif
