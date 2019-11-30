#define _CRT_SECURE_NO_WARNINGS

#include "QInt.h"

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
		"&", "|", "^", "<<", ">>",
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
	// freopen(argv[2], "w", stdout);

	// Phòng trường hợp...
	if (!fi.is_open() || !fo.is_open())
	{
		cout << "Failed to open file." << endl;
		return -1;
	}

	// Đếm số dòng trong file
	int32_t line_total = 0;
	while (!fi.eof())
	{
		string command;
		getline(fi, command);
		if (!command.empty() && command.find_first_not_of(' ') != string::npos)
			line_total++;
	}

	fi.close();

	fi.open(argv[1], fstream::in);

	int32_t line_current = 0;
	while (!fi.eof())
	{
		// Đọc và tách command
		string command;
		getline(fi, command);
		if (command.empty() || command.find_first_not_of(' ') == string::npos)
			continue;

		vector<string> tokens = tokenizer(command);
		
		// Xét số thành phần trong một command, tìm toán tử tương ứng,
		// tính và ghi kết quả ra file

		line_current++;
		cout << "Line " << line_current << "/" << line_total << ": ";

		if (tokens.size() == 3)
		{
			cout << tokens[1];
			switch (findOp(tokens[1]))
			{
				case VALID_OPS::TO_BASE2:
					fo << QInt(stoi(tokens[0]), tokens[2]).toString(2) << endl;
					break;

				case VALID_OPS::TO_BASE10:
					fo << QInt(stoi(tokens[0]), tokens[2]).toString(10) << endl;
					break;

				case VALID_OPS::TO_BASE16:
					fo << QInt(stoi(tokens[0]), tokens[2]).toString(16) << endl;
					break;

				case VALID_OPS::NOT:
					fo << QInt(stoi(tokens[0]), tokens[2]).operator~().toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::ROL:
					fo << QInt(stoi(tokens[0]), tokens[2]).rol().toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::ROR:
					fo << QInt(stoi(tokens[0]), tokens[2]).ror().toString(stoi(tokens[0])) << endl;
					break;

				default:
					fo << endl;
					break;
			}
		}

		else if (tokens.size() == 4)
		{
			cout << tokens[2];
			switch (findOp(tokens[2]))
			{
				case VALID_OPS::AND:
					fo << (QInt(stoi(tokens[0]), tokens[1]) & QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;
				
				case VALID_OPS::OR:
					fo << (QInt(stoi(tokens[0]), tokens[1]) | QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::XOR:
					fo << (QInt(stoi(tokens[0]), tokens[1]) ^ QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::LSL:
					fo << (QInt(stoi(tokens[0]), tokens[1]) << stoi(tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::ASR:
					fo << (QInt(stoi(tokens[0]), tokens[1]) >> stoi(tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::ADD:
					fo << (QInt(stoi(tokens[0]), tokens[1]) + QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::SUBTRACT:
					fo << (QInt(stoi(tokens[0]), tokens[1]) - QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::MULTIPLY:
					fo << (QInt(stoi(tokens[0]), tokens[1]) * QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				case VALID_OPS::DIVIDE:
					fo << (QInt(stoi(tokens[0]), tokens[1]) / QInt(stoi(tokens[0]), tokens[3])).toString(stoi(tokens[0])) << endl;
					break;

				default:
					break;
			}
		}

		else
			cout << "Bad command: " << command;

		cout << endl;
	}

	cout << "File written." << endl;

	return 0;
}
