﻿#include "QInt.h"
#include "FFTMachine.h"
#include <sstream>
#include "main.h"
/*
	Đề bài:
	Định nghĩa lớp QInt, operator= và các ops khác để thao tác trên kiểu này.

	Input:
		base1 base2 num
		base [~ ROL ROR] num
		base num1 [+ - * / & | ^ << >>] num2
		Với:
			base : [2 | 10 | 16]
			num  : số biểu diễn dưới base đã cho
			base1 == base2 thì no-op ("không làm gì")
			<< : LSL
			>> : ASR
	
	Output:
		"không pad 0x0 / 0b0"
 */

/*
	main chứa intepretor:
	argv[1] = input filepath, argv[2] = output filepath
	cho exit(-1) nếu argc != 3 cho an toàn?
*/
int main(int argc, char** argv)
{
	/*bitset<QLEN> _test = {1};
	int k = 0;
	for (int i = 1; i < QLEN; i++)
	{
		k += i;
		if (k % i == 0 || k % 3 != 0)
			_test[i] = 1;
	}
	QInt a(_test);
	cout << "Bin: " << a.toB10() << endl;
	QInt ans = a.ror(5);
	cout << "Bin: " << ans.toB2() << endl;*/
	bitset<QLEN> _test1(190);
	bitset<QLEN> _test2(190);
	QInt a(_test1);
	QInt b(_test2);
	cout << "Bin: " << a.toB2() << endl;
	cout << "Bin: " << b.toB2() << endl;
	QInt ans = a * b;
	cout << "Bin: " << ans.toB2() << endl;
	return 0;
}
