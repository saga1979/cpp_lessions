#pragma once

#include <map>
#include <utility>
#include <list>
#include <string>
using namespace std;

const uint32_t LEN_FIELD_LEN = sizeof(uint32_t);
//!注意,"数据段"的长度,由包含该"数据段"的上一级的相关函数插入
/**
1. 字段数据表示->"fieldname":value
   数据表示前面4个字节为该字段的数据长度(不包括表示长度的4字节)
2. 节可以包含多个字段
   开头4字节为该节的数据长度
   后面4字节为该节包含的字段数量
   后面跟(1.)中描述的字段
3. 信息可以包含多个节
   开头4字节为该信息的数据长度
   后面4字节为该信息包含的节的数量
   后面跟(2.)中描述的节
*/


//不包含前面表示4个字节的数据长度,只包含数据:"field_name":value
static int data_to_pair(pair<string, string>& obj, const string& data)
{
	size_t field_name_end_pos = data.find("\":");

	obj.first.insert(0, data.substr(1, field_name_end_pos - 1));
	obj.second.insert(0, data.substr(field_name_end_pos + 2, data.length() - field_name_end_pos - 2));

	return 0;
}
//不包含表示数据长度的开头4字节
static int data_to_map(map<string, string>& obj, const string& data)
{
	//四个字节表示字段数量
	uint32_t field_num = *(uint32_t*)data.substr(0, LEN_FIELD_LEN).data();
	size_t field_pos = LEN_FIELD_LEN;
	for (int i = 0; i < field_num; i++)
	{
		//每个字段的开头四个字节表示本字段的数据长度(字段长度=数据长度+LEN_FIELD_LEN)
		const string& field_data = data.substr(field_pos + LEN_FIELD_LEN,
			*(uint32_t*)(data.data() + field_pos));
		pair<string, string> p;
		data_to_pair(p, field_data);
		obj.insert(p);
		field_pos += LEN_FIELD_LEN;
		field_pos += field_data.length();
	}
	return 0;
}
//转换的时候,不会在数据前面插入数据长度
static int map_to_data(const map<string, string>& obj, string& data)
{
	for (map<string, string>::const_iterator mit = obj.begin(); mit != obj.end(); mit++)
	{
		uint32_t original_len = data.length();
		data += "\"";
		data += mit->first;
		data += "\":";
		data += mit->second;
		//开头插入本段数据长度(4个字节)
		uint32_t field_data_len = data.length() - original_len;
		data.insert(original_len, (const char*)&field_data_len, LEN_FIELD_LEN);
	}
	//开头插入包含的数据段的数量
	uint32_t section_num = obj.size();
	data.insert(0, (const char*)&section_num, LEN_FIELD_LEN);
	return 0;
}

static int list_map_to_data(const list< map<string, string> > & obj, string& data)
{
	uint32_t section_num = obj.size();


	if (0 == section_num)
	{
		data.insert(0, string((const char*)&section_num, sizeof(uint32_t)));
		return 0;
	}

	for (list< map<string, string> >::const_iterator it = obj.begin(); it != obj.end(); it++)
	{
		string section_data;
		map_to_data((*it), section_data);
		//再插入该数据段的数据长度
		uint32_t section_data_len = section_data.length();
		section_data.insert(0, (const char*)&section_data_len, LEN_FIELD_LEN);

		data += section_data;
	}
	//开头插入包含的子数据段数量
	data.insert(0, (const char*)&section_num, LEN_FIELD_LEN);
	//开头插入数据段总长度
	uint32_t total_data_len = data.length();
	data.insert(0, (const char*)&total_data_len, LEN_FIELD_LEN);

	return 0;
}

static int data_to_list_map(list<map<string, string> > & obj, const string& data)
{
	//开头四个字节表示本段数据长度
	uint32_t data_len = *(uint32_t*)data.substr(0, LEN_FIELD_LEN).data();
	//后面四个字节表示字段数量
	uint32_t section_num = *(uint32_t*)data.substr(LEN_FIELD_LEN, LEN_FIELD_LEN).data();

	size_t field_pos = LEN_FIELD_LEN + LEN_FIELD_LEN;
	for (int i = 0; i < section_num; i++)
	{
		//每个字段的开头四个字节表示本字段的数据长度(字段长度=数据长度+LEN_FIELD_LEN)
		const string& section_data = data.substr(field_pos + LEN_FIELD_LEN,
			*(uint32_t*)(data.data() + field_pos));
		map<string, string>  p;

		data_to_map(p, section_data);

		obj.push_back(p);

		field_pos += LEN_FIELD_LEN;
		field_pos += section_data.length();
	}
	return 0;
}


void data_test()
{
	list <map<string, string> > users;

	for (int i = 0; i < 10; i++)
	{
		map<string, string> user;
		string name("zf");
		name += std::to_string(i);

		user.insert(pair<string, string>("name", name));
		user.insert(pair<string, string>("salary", std::to_string(100 + i)));
		user.insert(pair<string, string>("img", "xxxxx"));

		users.push_back(user);
	}
	string data;
	list_map_to_data(users, data);

	list <map<string, string> > objs;

	data_to_list_map(objs, data);
}

int main(int argc, char** argv)
{
	data_test();
	return 0;
}
