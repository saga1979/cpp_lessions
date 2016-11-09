#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__
class user_manager
{
	user_manager();
	~user_manager();
public:
	static user_manager& instance();
};


#endif

