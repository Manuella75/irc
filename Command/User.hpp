#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

class	User
{
	private :
	int 						_socket;
	std::string					_nickname;
	std::string					_UserHosts;
	std::string 				_channel;
	std::string 				_cmd;
	int					_mode;
	bool						_connected;
	time_t						_lastPing;

	public :
		std::string  username;
		std::string realname;

		/* Constructor */
		User(std::string host, int socket);
		User(User const & cpy);
		User(User  * cpy);
		User &operator=(User const & rhs);
		/* Destructor */
		~User(void);

		std::string const & 	getUserHost() const;
		std::string	const		getUserNick() const;
		int						getUserMode() const ;
		std::string	const 		getUserChannel() const;
		int						getUserSocket() const;

		void					setUserMode(int mode);
		void					setUserNick(std::string Nick);
		void					setUserChannel(std::string chann);
		void					setCmd(std::string command);

		void					disconnect();
		size_t					getLastPing() const;
		bool					getConnected() const;
		void 					resetPing();
};

#endif
