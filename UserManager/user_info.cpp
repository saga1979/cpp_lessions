#include "user_info.h"


using namespace std;

ostream& operator << (ostream& os, const user_info& user)
{
	return os << user[user_info::NAME] << '\t' << user[user_info::PWD] << '\t' << user[user_info::DES] << '\t' << endl;
}

user_info::user_info()
{

	data[NAME] = "name";
	data[PWD] = "123456";
	data[DES] = "des.....";

}

user_info & user_info::operator=(const string &src)
{

	size_t last_index = 0;
	size_t cur_index = 0;
	int type = 0;

	while ((cur_index = src.find_first_of("\t", last_index)) != string::npos) {
		string str = src.substr(last_index, cur_index - last_index);
		last_index = cur_index + 1;
		(*this)[type] = str;
		type++;
	}

	return *this;

}

bool user_info::operator==(const user_info & right)
{
	return data[NAME] == right[NAME];
}

bool user_info::operator==(const string & name)
{
	return data[NAME] == name;
}

string & user_info::operator[](int pos)
{
	if (pos >= NAME && pos < END)
		return data[pos];

	throw new out_of_range("user has only three fields");
}

const string & user_info::operator[](int pos) const
{
	if (pos >= NAME && pos < END)
		return data[pos];

	throw new out_of_range("user has only three fields");
}
