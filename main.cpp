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

enum VALID_OPS
{
	INVALID = -1,
	TO_BASE2, TO_BASE10, TO_BASE16,
	NOT, ROL, ROR,
	AND, OR, XOR, LSL, ASR,
	ADD, SUBTRACT, MULTIPLY, DIVIDE
};

const int8_t findOp(string o)
{
	const vector<string> valid_ops = {
		"2", "10", "16",
		"~", "rol", "ror",
		"&", "|", "^", "<<", ">>"
		"+", "-", "*", "/"
	};

	auto found = find(valid_ops.begin(), valid_ops.end(), o);

	if (found == valid_ops.end())
		return VALID_OPS::INVALID;
	else
		return (int8_t)(found - valid_ops.begin());
}

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
		// Đọc và tách command
		string command;
		getline(fi, command);
		vector<string> args = tokenizer(command);
		
		if (args.size() == 3)
		{
			switch (stoi(args[1]))
			{
				case VALID_OPS::TO_BASE2:
					break;

				case VALID_OPS::TO_BASE10:
					break;

				case VALID_OPS::TO_BASE16:
					break;

				case VALID_OPS::NOT:
					break;

				case VALID_OPS::ROL:
					break;

				case VALID_OPS::ROR:
					break;

				default:
					break;
			}
		}

		else if (args.size() == 4)
		{
			switch (stoi(args[2]))
			{
				case VALID_OPS::AND:
					break;
				
				case VALID_OPS::OR:
					break;

				case VALID_OPS::XOR:
					break;

				case VALID_OPS::LSL:
					break;

				case VALID_OPS::ASR:
					break;

				case VALID_OPS::ADD:
					break;

				case VALID_OPS::SUBTRACT:
					break;

				case VALID_OPS::MULTIPLY:
					break;

				case VALID_OPS::DIVIDE:
					break;

				default:
					break;
			}
		}

		else
			cout << "Bad command: " << command << endl;
	}
	return 0;
}
