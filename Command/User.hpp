#ifndef USER_HPP
# define USER_HPP

# include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "../includes/server.hpp"

class	User
{
	private :
	int _socket;
	std::string	_UserHosts;
	std::string	_nickname;
	std::string _channel;
	//map avec bool 1 pour op du premier qui rejoin le channel
	//vecteur >  delete  juste delete le chann ou on est
	//join check si ca existe si ca existe delete et met le a la fin sinon insrt

	std::string _cmd;

	public :
		bool oper;
		std::string realname;
	int					_mode;
	bool						_connected;
	time_t						_lastPing;

	// public :
		// std::string  username;
		// std::string realname;

		/* Constructor */
		User(std::string host, int socket);
		User(User const & cpy);
		User(User  * cpy);
		User &operator=(User const & rhs);
		void				setUserHost(std::string host);
		std::string		const getUserChannel() const;
		void reply(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");
		/* Destructor */
		/* Destructor */
		~User(void);

		std::string const & 	getUserHost() const;
		std::string	const		getUserNick() const;
		int						getUserMode() const ;
		void	print_channel_user();
		// std::string	const 		getUserChannel() const;
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
