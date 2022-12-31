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
		std::string 					_name; // channel name
		std::string 					_topic; // chanel topic
		std::map<int, User *> 			_Users; // channel users
		User							*_creator; // the creator

	public :
	 	Channel(std::string const  name, User *creator);
		Channel(Channel const &cpy);
		Channel(Channel * cpy);
		~Channel();
		Channel & operator=(Channel const & rhs);


		User*							getCreator() const;
		User*							getAMember(std::string member) const;
		std::string const & 			getName() const;
		std::string const & 			getTopic() const;
		std::map<int, User *> const& 	getUsers() const;
		std::map<int, User *>  & 		getUsers();

		void							kickMember(User *member);
		void							addMember(User *member);

};	
#endif
