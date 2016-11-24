#include "..\cont++\contpp\matrix.h"
#include <iostream>

using namespace contpp;

using std::cin;
using std::cout;

int main()
{
	vector<int, 4> m{ 10, 20, 30, 40 };
	for (int i = 0; i < 4; ++i)
	{
		cout << m(0, i) << "\n";
	}
}