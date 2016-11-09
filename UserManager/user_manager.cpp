#include "user_manager.h"



user_manager::user_manager()
{
}


user_manager::~user_manager()
{
}

user_manager & user_manager::instance()
{
	static user_manager s;

	return s;
}
