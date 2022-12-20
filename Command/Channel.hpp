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
		char  _mode; // channel mode
	public :
	 	Channel(std::string const  name, User U);
		~Channel();
		std::string const & getName() const;
		std::string const & getTopic() const;
		std::map<int, User *>  & getUsers();
		int  getMode() const;

};
#endif
