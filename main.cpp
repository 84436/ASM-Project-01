#include "QInt.h"

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
	int c = 142857;
	bitset<QLEN> _test(c);
	QInt a(_test);
	cout << "Bin: " << a.toB2() << endl;
	QInt ans = a.rol(5);
	cout << "Bin: " << ans.toB2() << endl;
	return 0;
}
