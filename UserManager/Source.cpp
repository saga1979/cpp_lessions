#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "user_info.h"
using namespace std;


static const char* DATA_FILE = "./zf.data";

int main(int argc, char* argv[])
{
	if (argc != 3) {
		cout << "use:" << endl;
		cout << "[exec] [user name] [new pwd]" << endl;
		return -1;
	}

	//read user info from disk file
	list<user_info*> ilist;
	ifstream ifs;
	ifs.open(DATA_FILE, std::ifstream::in);
	char buf[256];

	while (ifs.getline(buf, 256)) {
		user_info* puser = new user_info;
		*puser = buf;
		ilist.push_back(puser);
	}

	//if file is empty, then initialize it
	if (ilist.size() == 0) {

		for (char i = '0'; i< '9'; i++) {
			user_info* puser = new user_info;
			(*puser)[user_info::NAME].push_back(i);
			ilist.push_back(puser);
		}
	}

	//find user to modify
	list<user_info*>::iterator it = ilist.begin();

	for (; it != ilist.end(); it++) {
		if (*(*it) == argv[1]) {
			break;
		}
	}

	if (it != ilist.end()) {
		(*(*it))[user_info::PWD] = argv[2];
	}
	else {
		cout << argv[1] << "not found!" << endl;
		return -1;
	}

	//write data to disk file
	ofstream ofs;
	ofs.open(DATA_FILE, std::ofstream::out | std::ofstream::trunc /*| std::ofstream::app*/);

	for (it = ilist.begin(); it != ilist.end(); it++) {
		ofs << *(*it);
		delete *it;
	}

	ofs.close();

	return 0;
}
