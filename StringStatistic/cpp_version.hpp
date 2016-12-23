#ifndef __CPP_VERSION_HPP__
#define __CPP_VERSION_HPP__
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <ctime>
using namespace std;

static const char* DATA_FILE = "./zf.data";

struct InputInfo
{
	string data;
	string time;
	//将结构体内容合并为,保存到文件,也可以打印(未考虑人性化打印格式)
	string to_string()
	{
		return data + "|" + time + "\n";
	}
	//从符合格式要求的字符串分离出内容
	InputInfo& from_string(const string& str)
	{
		data = str.substr(0, str.find("|"));
		time = str.substr(data.length() + 1, str.length() - data.length() - 1);
		return *this;
	}

};

static multimap<string, InputInfo*> s_inputs;
//处理用户输入数据
static void process_storeloop()
{
	while (1)
	{
		string data;
		cout << "input:";
		::getline(cin, data);
		if (data.empty())
		{
			break;
		}
		//生成新的输入信息
		InputInfo* pinfo = new InputInfo;
		pinfo->data = data;
		//格式化时间(2016-12-12 12:12:12)
		char buffer[256] = { 0 };
		time_t time = ::time(0);
		struct tm* timeinfo = localtime(&time);
		strftime(buffer, 255, "%F %X", timeinfo);
		pinfo->time = buffer;
		//加入到map
		s_inputs.insert(pair<string, InputInfo*>(data, pinfo));		
	}
}
//处理查找数据
static void process_searchloop()
{
	while (1)
	{
		string data;
		cout << "input:";
		::getline(cin, data);
		if (data.empty())
		{
			break;
		}
		pair<multimap<string, InputInfo*>::iterator, multimap<string, InputInfo*>::iterator>
			ret = s_inputs.equal_range(data);
		int count = 0;
		for (multimap<string, InputInfo*>::iterator it = ret.first; it != ret.second; it++, count++)
		{
			cout << it->second->to_string() << endl;
		}
		if (count == 0)
		{
			cout << "[" << data << "] not found:" << endl;
			continue;
		}
		cout << "[" << data << "] count:" << count << endl;
	}
}
//从文件加载数据
static void load_data()
{
	ifstream ifs;
	ifs.open(DATA_FILE, std::ifstream::in);
	char buf[256] = { 0 };

	while (ifs.getline(buf, 256)) 
	{
		InputInfo* pinfo = new InputInfo;
		pinfo->from_string(buf);
		s_inputs.insert(pair<string, InputInfo*>(pinfo->data, pinfo));
	}
}
//保存数据到磁盘文件
static void store_data()
{
	ofstream ofs;
	ofs.open(DATA_FILE, std::ofstream::out | std::ofstream::trunc /*| std::ofstream::app*/);

	for (multimap<string, InputInfo*>::iterator it = s_inputs.begin(); it != s_inputs.end(); it++) 
	{
		string data = it->second->to_string();
		ofs.write(data.c_str(), data.length());
		delete it->second;
	}

	ofs.close();
}

int main(int argc, char** argv)
{
	string data;
	load_data();
	while (1)
	{//打印功能菜单
		cout << "select functions:\n" 
			<< "1)store something\n" 
			<< "2)search something\n"
			<<"any other to exit....." << endl;
		::getline(cin, data);

		if (data == "1")
		{
			process_storeloop();
		}
		else if (data == "2")
		{
			process_searchloop();
		}
		else
		{
			break;
		}
		data.clear();
	}	
	store_data();
	cout << "bye.........\n" << endl;
	return 0;
}

#endif
