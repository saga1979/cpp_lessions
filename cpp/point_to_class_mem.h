

#include <iostream>
using namespace std;

class Test
{
public:
	void print()
	{
		cout << "ss" << endl;
	}
};




int main()
{
	Test obj;
	void (Test::*pFun)() = &Test::print;

	(obj.*pFun)();

	return 0;
}