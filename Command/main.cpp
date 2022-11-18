#include "Command.hpp"
#include "User.hpp"

int	main(void)
{
	User U("ldinguir", "Linda Dinguir", "password", "127.0.0.1");

	Command A(U, "lol");
	Command B(U, "/join lolilol");
	Command C(U, "/JOin");
	return (0);
}
