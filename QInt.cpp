#include "QInt.h"
#include <sstream>

uint8_t** QInt::Pow2Table = nullptr;
bool QInt::Pow2Table_Generate_ran = false;
bool isOdd(string s);
string divByTwo(string num);
void QInt::Pow2Table_Generate()
{
	if (Pow2Table_Generate_ran)
		return;

	Pow2Table = new uint8_t * [QLEN]();
	for (uint8_t i = 0; i < QLEN; i++)
		Pow2Table[i] = new uint8_t[DLEN]();

	Pow2Table[0][0] = 1;
	for (uint8_t b = 1; b < QLEN; b++)
	{
		for (uint8_t d = 0; d < DLEN; d++)
		{
			Pow2Table[b][d] += 2 * Pow2Table[b - 1][d];
			if (Pow2Table[b][d] >= 10 && d < DLEN - 1)
			{
				Pow2Table[b][d + 1] += Pow2Table[b][d] / 10;
				Pow2Table[b][d] %= 10;
			}
		}
	}

	Pow2Table_Generate_ran = true;
}

QInt::QInt(uint8_t base, string data) : QInt()
{
	switch (base)
	{
		case 2:
			this->data = bitset<QLEN>(data);
			break;

		/*case 10:
			break;*/

		/*case 16:
			break;*/

		default: break;
	}
}

QInt::QInt(const QInt& x) : QInt()
{
	this->data = x.data;
}

void QInt::operator=(const QInt& x)
{
	this->data = x.data;
}

void QInt::randomize()
{
	random_device rd;
	for (uint8_t i = 0; i < QLEN; i++)
		data[i] = rd() % 2;
}

int QInt::bit_size() const
{
	int sign;
	sign = this->data[QLEN - 1];
	int ans = QLEN - 1;
	while (ans >= 0 && this->data[ans] == bool(sign))
		ans--;
	return ans + 1;
}

QInt QInt::operator+(const QInt& x)
{
	QInt r;
	bool c = 0; // carry
	for (int i = 0; i < QLEN; ++i)
	{
		if (!c)
		{
			if (this->data[i] && x.data[i]) { r.data[i] = 0; c = 1; }
			else { r.data[i] = this->data[i] | x.data[i]; }
		}
		else
		{
			if (!this->data[i] && !x.data[i]) { r.data[i] = 1; c = 0; }
			else { r.data[i] = this->data[i] & x.data[i]; }
		}
	}
	return r;
}

//TODO : Can check nhe lai

QInt QInt::operator*(const QInt& x)
{

	QInt ans("0");
	QInt _tmp(x);
	int count = 0;
	bool isNeg = (x.data[1] == 1);
	string multicand = _tmp.toB10();
	if (multicand[0] == '-')
		multicand = multicand.substr(1);
	while (multicand != "0")
	{
			if (isOdd(multicand))
				ans = ans + (*this << count);
			count++;
			multicand = divByTwo(multicand);
		}
	if (isNeg)
		ans = (~ans + QInt("1"));
	return ans;
}

QInt QInt::operator&(const QInt& x)
{
	QInt r = *this;
	for (uint8_t i = 0; i < QLEN; i++)
	{
		r.data[i] = this->data[i] & x.data[i];
	}
	return r;
}

QInt QInt::operator|(const QInt& x)
{
	QInt r = *this;
	for (uint8_t i = 0; i < QLEN; i++)
	{
		r.data[i] = this->data[i] | x.data[i];
	}
	return r;
}

QInt QInt::operator^(const QInt& x)
{
	QInt r = *this;
	for (uint8_t i = 0; i < QLEN; i++)
	{
		r.data[i] = this->data[i] ^ x.data[i];
	}
	return r;
}

QInt::QInt(const bitset<QLEN> p_value)
{
	this->data = p_value;
}

bool isOdd(string s)
{
	if ((s[s.size() - 1] - '0') % 2 == 1)
		return true;
	return false;
}
string divByTwo(string num)
{
	string ans;
	if (num == "1" || num == "0")
		return "0";
	int idx = 0;
	int temp = num[idx] - '0';
	while (temp < 2)
		temp = temp * 10 + (num[++idx] - '0');
	while (num.size() > idx)
	{
		// Store result in answer i.e. temp / divisor 
		ans += (temp / 2) + '0';

		// Take next digit of number 
		temp = (temp % 2) * 10 + num[++idx] - '0';
	}
	// If divisor is greater than number 
	if (ans.size() == 0)
		return "0";

	// else return ans 
	return ans;
}
QInt::QInt(string num, int base)
{
	bool isNeg = false;
	if (num[0] == '-')
	{
		isNeg = true;
		num = num.substr(1);
	}
	vector<bool> recase;
	while (num != "0")
	{
		recase.push_back(isOdd(num));
		num = divByTwo(num);
	}
	int k = 0;
	for (auto i : recase)
	{
		if (k >= QLEN)
			break;
		this->data[k++] = i;
	}
	if (isNeg)
	{
		bitset<QLEN> one(1);
		*this = (~*(this) + QInt(one));
	}
}

QInt QInt::operator~()
{
	QInt r = *this;
	for (uint8_t i = 0; i < QLEN; i++)
	{
		r.data[i] = !(r.data[i]);
	}
	return r;
}

QInt QInt::operator>> (const int& v_shift)
{
	if (v_shift > QLEN || v_shift <= 0)
		abort();
	bitset<QLEN> re_value(this->data[QLEN - 1]);
	int i = 0;
	int k = v_shift;
	while (k < QLEN)
	{
		re_value[i++] = this->data[k++];
	}
	return QInt(re_value);
}

QInt QInt::operator<<(const int& v_shift)
{
	if (v_shift > QLEN || v_shift < 0)
		abort();
	bitset<QLEN> re_value(0);
	int i = QLEN;
	int k = QLEN - v_shift % QLEN - 1;
	while (k >= 0)
	{
		re_value[--i] = this->data[k--];
	}
	return QInt(re_value);
}

//TODO : Làm chưa xong
QInt QInt::rol(const int& n)
{
	if (n >= QLEN || n < 0)
		abort();
	bitset<QLEN> ans;
	int k = 2*QLEN - n%QLEN - 1;
	int i = QLEN - 1;
	while (i >= 0)
	{
		ans[i--] = this->data[(k) % QLEN];
		k--;
	}
	return QInt(ans);
}

QInt QInt::ror(const int& n)
{
	if (n >= QLEN || n < 0)
		abort();
	bitset<QLEN> ans;
	int k = n%QLEN;
	int i = 0;
	while (i < QLEN)
	{
		ans[i++] = this->data[(k) % QLEN];
		k++;
	}
	return QInt(ans);
}

string QInt::toB2()
{
	string r;

	for (uint8_t i = 0; i < QLEN; i++)
	{
		r.insert(r.begin(), (data[i] ? '1' : '0'));
		/*if ((i + 1) < QLEN && (i + 1) % 4 == 0)
			r.insert(r.begin(), ' ');*/
	}

	// Trim string
	if (r[0] == '0')
	{
		size_t del_mark = r.find_first_not_of('0');
		r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
	}

	return r;
}

string QInt::toB10()
{
	string r;

	uint8_t* b10 = new uint8_t[DLEN]();

	// Tạo bản sao
	QInt temp;
	if (data[QLEN - 1])
	{
		bitset<QLEN> one;
		one.flip(0);
		temp = ~(*this) + QInt(one);
	}
	else
	{
		temp = *this;
	}

	// Cộng và ghi ra string
	for (uint8_t b = 0; b < QLEN; b++)
	{
		if (temp.data[b])
		{
			for (uint8_t d = 0; d < DLEN; d++)
			{
				b10[d] += Pow2Table[b][d];
				if (b10[d] >= 10 && d < DLEN - 1)
				{
					b10[d + 1] += b10[d] / 10;
					b10[d] %= 10;
				}
			}
		}
	}
	for (uint8_t d = 0; d < DLEN; d++)
		r.append(to_string(b10[DLEN - 1 - d]));

	// Trim string
	if (r[0] == '0')
	{
		size_t del_mark = r.find_first_not_of('0');
		r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
	}

	// Thêm dấu âm nếu có .-.
	if (data[QLEN - 1])
		r.insert(r.begin(), '-');

	return r;
}
bool is_holding(vector<uint64_t> q)
{
	for (auto i : q)
	{
		if (i != 0)
			return true;
	}
	return false;
}

string QInt::toB16()
{
	string r;

	for (uint8_t i = 0; i < QLEN; i += 4)
	{
		uint8_t t = 0;
		for (uint8_t j : {0, 1, 2, 3})
			t += data.test(i + j) << j;
		r.insert(r.begin(), HEX[t]);
		/*if ((i + 4) < QLEN && (i + 4) % 16 == 0)
			r.insert(r.begin(), ' ');*/
	}

	// Trim string
	if (r[0] == '0')
	{
		size_t del_mark = r.find_first_not_of('0');
		r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
	}

	return r;
}
