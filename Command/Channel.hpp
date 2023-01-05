#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "User.hpp"

<<<<<<< HEAD
class User;
class Channel
{
	private:
		std::string _name; // channel name
		std::string _topic; // chanel topic
		std::map<int, User *> _Users; // channel users
		std::vector<int>	_Banni;
	public :
	 	Channel(std::string const  name, User U);
=======
class Channel
{
	private:
		std::string 					_name; // channel name
		std::string 					_topic; // chanel topic
		std::map<int, User *> 			_Users; // channel users
		User							*_creator; // the creator

	public :
	 	Channel(std::string const  name, User *creator);
>>>>>>> master
		Channel(Channel const &cpy);
		Channel(Channel * cpy);
		~Channel();
		Channel & operator=(Channel const & rhs);
<<<<<<< HEAD
		std::string const & getName() const;
		std::string const & getTopic() const;
		std::map<int, User *> const  & getUsers() const;
		std::vector<int> const  & getBanni() const;
		void addBanni(int i);
		void	setTopic(std::string topic);
		std::map<int, User *>  & getUsers();

};
=======


		User*								getCreator() const;
		User*								getOneMember(std::string member) const;
		std::map<int, User*> &				getAllMembers();
		std::string	const &					getName() const;
		std::string const & 				getTopic() const;
		std::map<int, User *> const& 		getUsers() const;
		std::map<int, User *>  & 			getUsers();

		void								kickMember(User *member);
		void								addMember(User *member);

};	
>>>>>>> master
#endif
