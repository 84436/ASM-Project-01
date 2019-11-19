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

// Tokenizer trong đây chỉ cần biết ' ' là đủ ._.
vector<string> tokenizer(string s)
{
	vector<string> tokens;
	size_t offset = 0;
	while (offset < s.size())
	{
		size_t spacechar = (
			s.find_first_of(' ', offset) != string::npos
			? s.find_first_of(' ', offset)
			: s.size()
		);
		tokens.push_back(
			s.substr(offset, spacechar - offset)
		);
		offset = ++spacechar;
	}
	return tokens;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Incorrect number of arguments." << endl;
		return -1;
	}

	fstream fi(argv[1], fstream::in);
	fstream fo(argv[2], fstream::out | fstream::trunc);

	// Phòng trường hợp...
	if (!fi.is_open() || !fo.is_open())
	{
		cout << "Failed to open file." << endl;
		return -1;
	}

	while (!fi.eof())
	{
		string command;
		getline(fi, command);
		vector<string> args = tokenizer(command);
	}

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

	QInt a("4647");
	QInt b("4302371896916613314517792614108589");
	cout << "Bin: " << a.toB2() << endl;
	cout << "Dec: " << a.toB10() << endl;
	
	cout << "Bin: " << b.toB2() << endl;
	cout << "Dec: " << b.toB10() << endl;
	QInt ans = a * b;
	cout << "Bin: " << ans.toB2() << endl;
	cout << "Dec: " << ans.toB10() << endl;
	return 0;
}
