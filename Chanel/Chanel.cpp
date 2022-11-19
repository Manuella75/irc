#include "Channel.hpp"

/* Constructor */

Channel::Channel(std::string name) : _Name(name)
{
	if (name[0] == '&')
	{
	// chan standard 
	}
	else if (name[0] == '#')
	{
	// chan standard 
	}
	else if (name[0] == '+')
	{
	// chan standard 
	}
	else if (name[0] == '!')
	{
	// chan sur 
	}
	else
	{
		// erreur channel doit commencer par & # + !                                    
	}
	return ;
}

/* Destructor */

Channel::~Channel(void)
{
	return ;
}
