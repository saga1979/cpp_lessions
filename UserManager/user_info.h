#ifndef __USER_INFO_H__
#define __USER_INFO_H__

#include <iostream>
#include <string>
using std::ostream;
using std::string;
using std::out_of_range;

class user_info
{
	friend ostream& operator << (ostream&, const user_info&);
	string data[3];
public:
	enum {
		NAME = 0,
		PWD,
		DES,
		END,
	};
	user_info();
	user_info& operator = (const string& ); 
	bool operator == (const user_info& right);
	bool operator == (const string& name);
	string& operator[] (int pos);
	const string& operator[] (int pos) const;

};

#endif

