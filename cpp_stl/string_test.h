// string::find
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstdint>
typedef std::basic_string<uint8_t> ustring;

void find_test()
{
	std::string str_src("There are two needles in this haystack with needles.");
	//string��ʾchar�������ݵ�����,������ͬchar *,char* ����'\0'���ս�
	char tstr[3] = { '\0', 'z', 'z' };
	str_src.append(tstr, 3);
	std::string str_find("needle");

	// different member versions of find in the same order as above:
	std::size_t found = str_src.find(str_find);
	if (found != std::string::npos)
		std::cout << "first 'needle' found at: " << found << '\n';

	found = str_src.find("needles are small", found + 1, 6);
	if (found != std::string::npos)
		std::cout << "second 'needle' found at: " << found << '\n';

	found = str_src.find("haystack");
	if (found != std::string::npos)
		std::cout << "'haystack' also found at: " << found << '\n';

	found = str_src.find('.');
	if (found != std::string::npos)
		std::cout << "Period found at: " << found << '\n';

	found = str_src.find("zz");
	if (found != std::string::npos)
		std::cout << "zz found at:" << found << '\n';

	// let's replace the first needle:
	str_src.replace(str_src.find(str_find), str_find.length(), "preposition");
	std::cout << str_src << '\n';
	std::cout << str_src.c_str() << '\n';//ע��۲�����һ�е�������

}



void size_test()
{
	//string������/�ߴ�/����
	std::string buf;
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;
	buf.reserve(1024 * 10);//ע��,������������������1024*10	
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;
	buf.reserve(1024 * 10);
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;

	buf.resize(1024 * 10);//ʹ��resize��,����/��С/���ȶ������˱仯,���������ı仯�����������в���
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;
}

int main()
{
	find_test();
	size_test();
	
	return 0;
}
