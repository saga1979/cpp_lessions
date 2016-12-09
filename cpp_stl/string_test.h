// string::find
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstdint>
typedef std::basic_string<uint8_t> ustring;

void find_test()
{
	std::string str_src("There are two needles in this haystack with needles.");
	//string表示char类型数据的容器,并不等同char *,char* 遇到'\0'就终结
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
	std::cout << str_src.c_str() << '\n';//注意观察与上一行的输出差别

}



void size_test()
{
	//string的容量/尺寸/长度
	std::string buf;
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;
	buf.reserve(1024 * 10);//注意,后面的容量输出并不是1024*10	
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;
	buf.reserve(1024 * 10);
	std::cout << "buf capacity:" << buf.capacity() << std::endl;
	std::cout << "buf size:" << buf.size() << std::endl;
	std::cout << "buf len:" << buf.length() << std::endl;

	buf.resize(1024 * 10);//使用resize后,容量/大小/长度都发生了变化,但是容量的变化跟其他两者有差异
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
