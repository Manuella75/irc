#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>

class Channel
{
	private:
		std::string name; // channel name
		std::string topic; // chanel topic
		std::map<int, User *> Users; // channel users
		std::string mode; // channel mode
		std::map<int, std::string> user_mode; // user mode
		std::string key; // channel key in channels map
		std::string max_users; // max users
		std::vector<User *> invited; // vector of invited users
	public :
		std::string const & getName(); const
};
