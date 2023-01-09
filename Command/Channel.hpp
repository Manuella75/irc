#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "User.hpp"


class User;
class Server;

class Channel
{
	private:
		std::vector<int>	_Banni;
		std::string 					_name; // channel name
		std::string 					_topic; // chanel topic
		std::map<int, User *> 			Members; // channel users
		User							*_creator; // the creator
		std::string						_mode;
		size_t							_maxUsers;

	public :
	 	Channel(std::string const  name, User *creator);
		Channel(Channel const &cpy);
		Channel(Channel * cpy);
		~Channel();
		Channel & operator=(Channel const & rhs);
		std::vector<int> const  & getBanni() const;
		void addBanni(int i);
		void	setTopic(std::string topic);

		User*								getCreator() const;
		User*								getOneMember(std::string member) const;
		std::map<int, User*> &				getAllMembers();
		std::string	const &					getName() const;
		std::string const & 				getTopic() const;
		std::map<int, User *> const& 		getUsers() const;
		std::map<int, User *>  & 			getUsers();
		std::string							getMode() const;

		void								kickMember(User *member);
		void								addMember(User *member);
		void								addMode(char mode);
		void								removeMode(char mode);
		std::string							display();

};
#endif
