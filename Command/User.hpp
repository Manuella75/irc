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
	std::string	_nickname;
	std::string	_UserHosts;
	int _socket;
	// std::string _channel;
	std::map<std::string, bool> _channel;
	//vecteur >  delete  juste delete le chann ou on est
	//join check si ca existe si ca existe delete et met le a la fin sinon insrt

	std::string _cmd;

	public :
		bool oper;
		std::string realname;
		/* Constructor */
		User(std::string host, int socket);
		User(User const & cpy);
		User(User  * cpy);
		User &operator=(User const & rhs);
		std::string const & getUserHost() const;
		std::string		const	getUserNick() const;
		void				setUserNick(std::string Nick);
		void				setUserHost(std::string host);
		void				setUserChannel(std::string chann, bool bo);
		void	setCmd(std::string command);
		std::map<std::string, bool>			const getUserChannel() const;
		std::string			const getUserlastChannel() const;
		int					getUserSocket() const;
		void	deleteUserlastChannel();
		/* Destructor */
		~User(void);
};

#endif
