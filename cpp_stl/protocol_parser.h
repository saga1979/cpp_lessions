#pragma once

#include <map>
#include <utility>
#include <list>
#include <string>
using namespace std;

const uint32_t LEN_FIELD_LEN = sizeof(uint32_t);
//!ע��,"���ݶ�"�ĳ���,�ɰ�����"���ݶ�"����һ������غ�������
/**
1. �ֶ����ݱ�ʾ->"fieldname":value
   ���ݱ�ʾǰ��4���ֽ�Ϊ���ֶε����ݳ���(��������ʾ���ȵ�4�ֽ�)
2. �ڿ��԰�������ֶ�
   ��ͷ4�ֽ�Ϊ�ýڵ����ݳ���
   ����4�ֽ�Ϊ�ýڰ������ֶ�����
   �����(1.)���������ֶ�
3. ��Ϣ���԰��������
   ��ͷ4�ֽ�Ϊ����Ϣ�����ݳ���
   ����4�ֽ�Ϊ����Ϣ�����Ľڵ�����
   �����(2.)�������Ľ�
*/


//������ǰ���ʾ4���ֽڵ����ݳ���,ֻ��������:"field_name":value
static int data_to_pair(pair<string, string>& obj, const string& data)
{
	size_t field_name_end_pos = data.find("\":");

	obj.first.insert(0, data.substr(1, field_name_end_pos - 1));
	obj.second.insert(0, data.substr(field_name_end_pos + 2, data.length() - field_name_end_pos - 2));

	return 0;
}
//��������ʾ���ݳ��ȵĿ�ͷ4�ֽ�
static int data_to_map(map<string, string>& obj, const string& data)
{
	//�ĸ��ֽڱ�ʾ�ֶ�����
	uint32_t field_num = *(uint32_t*)data.substr(0, LEN_FIELD_LEN).data();
	size_t field_pos = LEN_FIELD_LEN;
	for (int i = 0; i < field_num; i++)
	{
		//ÿ���ֶεĿ�ͷ�ĸ��ֽڱ�ʾ���ֶε����ݳ���(�ֶγ���=���ݳ���+LEN_FIELD_LEN)
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
//ת����ʱ��,����������ǰ��������ݳ���
static int map_to_data(const map<string, string>& obj, string& data)
{
	for (map<string, string>::const_iterator mit = obj.begin(); mit != obj.end(); mit++)
	{
		uint32_t original_len = data.length();
		data += "\"";
		data += mit->first;
		data += "\":";
		data += mit->second;
		//��ͷ���뱾�����ݳ���(4���ֽ�)
		uint32_t field_data_len = data.length() - original_len;
		data.insert(original_len, (const char*)&field_data_len, LEN_FIELD_LEN);
	}
	//��ͷ������������ݶε�����
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
		//�ٲ�������ݶε����ݳ���
		uint32_t section_data_len = section_data.length();
		section_data.insert(0, (const char*)&section_data_len, LEN_FIELD_LEN);

		data += section_data;
	}
	//��ͷ��������������ݶ�����
	data.insert(0, (const char*)&section_num, LEN_FIELD_LEN);
	//��ͷ�������ݶ��ܳ���
	uint32_t total_data_len = data.length();
	data.insert(0, (const char*)&total_data_len, LEN_FIELD_LEN);

	return 0;
}

static int data_to_list_map(list<map<string, string> > & obj, const string& data)
{
	//��ͷ�ĸ��ֽڱ�ʾ�������ݳ���
	uint32_t data_len = *(uint32_t*)data.substr(0, LEN_FIELD_LEN).data();
	//�����ĸ��ֽڱ�ʾ�ֶ�����
	uint32_t section_num = *(uint32_t*)data.substr(LEN_FIELD_LEN, LEN_FIELD_LEN).data();

	size_t field_pos = LEN_FIELD_LEN + LEN_FIELD_LEN;
	for (int i = 0; i < section_num; i++)
	{
		//ÿ���ֶεĿ�ͷ�ĸ��ֽڱ�ʾ���ֶε����ݳ���(�ֶγ���=���ݳ���+LEN_FIELD_LEN)
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
