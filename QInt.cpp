#include "QInt.h"
#include <sstream>

uint8_t** QInt::Pow2Table = nullptr;
bool QInt::Pow2Table_Generate_ran = false;
//Singleton Table de convert base2 -> base10
void QInt::Pow2Table_Generate()
{
	if (Pow2Table_Generate_ran)
		return;

	Pow2Table = new uint8_t * [QLEN]();
	for (uint8_t i = 0; i < QLEN; i++)
		Pow2Table[i] = new uint8_t[DLEN]();
	//Singleton startpoint

	Pow2Table[0][0] = 1;
	for (uint8_t b = 1; b < QLEN; b++)
	{
		for (uint8_t d = 0; d < DLEN; d++)
		{
			Pow2Table[b][d] += 2 * Pow2Table[b - 1][d];
			if (Pow2Table[b][d] >= 10 && d < DLEN - 1)
			{
				//Cong don phan tu trong table
				Pow2Table[b][d + 1] += Pow2Table[b][d] / 10;
				Pow2Table[b][d] %= 10;
			}
		}
	}

	Pow2Table_Generate_ran = true;
}

//////////////////////////////////////////////////

//Tra ve true neu string bieu dien mot so nguyen le
bool isOdd(string s)
{
	if ((s[s.size() - 1] - '0') % 2 == 1)
		return true;
	return false;
}

//Chia string bieu dien so nguyen cho 2
string divByTwo(string num)
{
	string ans;
	//Kiem tra so am/so duong nguoc dau cac kieu
	if (num == "1" || num == "0")
		return "0";
	int idx = 0;
	int temp = num[idx] - '0';
	while (temp < 2)
		temp = temp * 10 + (num[++idx] - '0');
	while (num.size() > idx)
	{
		//Chia cho 2 va cong cho 0
		ans += (temp / 2) + '0';

		//Tach so du tu temp ra
		temp = (temp % 2) * 10 + num[++idx] - '0';
	}
	// Neu so chia lon hon so bi chia
	if (ans.size() == 0)
		return "0";

	//Khong thi tra ve ket qua
	return ans;
}
QInt::QInt(uint8_t base, string data) : QInt()
{
	//O day chung toi khong lam the
	if (data.empty())
	{
		cout << "Bad string." << endl;
		return;
	}

	// base2
	if (base == 2)
	{
		if (data.size() > 128)
		{
			cout << "Bad binary string length." << endl;
			return;
		}

		this->data = bitset<QLEN>(data);
	}

	// base10, <3 Ton
	else if (base == 10)
	{
		bool isNeg = false;
		if (data[0] == '-')
		{
			isNeg = true;
			data = data.substr(1);
		}
		vector<bool> recase;
		while (data != "0")
		{
			recase.push_back(isOdd(data));
			data = divByTwo(data);
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

	// base16
	else if (base == 16)
	{
		if (data.size() > 32)
		{
			cout << "Bad hexadecimal string length." << endl;
			return;
		}

		while (data.size() < 32)
		{
			data.insert(data.begin(), '0');
		}

		// data.size() --> uint64_t
		for (int64_t c = data.size() - 1; c >= 0; --c)
		{
			// Index trong HEX = số ở dạng b10
			uint8_t dec = 0;
			for (uint8_t i = 0; i < 16; i++)
				if (data[c] == HEX[i]) { dec = i; break; }

			for (uint8_t b : {0, 1, 2, 3})
			{
				this->data[QLEN - 4 * (c + 1) + b] = (bool)(dec % 2);
				dec /= 2;
			}
		}
	}

	// invalid
	else
	{
		cout << "Bad base." << endl;
	}
}

//Convert bitset thanh QInt
QInt::QInt(const bitset<QLEN> p_value)
{
	this->data = p_value;
}

//Copy Constuctor
QInt::QInt(const QInt& x) : QInt()
{
	this->data = x.data;
}

//Random cho QInt - ho tro test cac kieu
void QInt::randomize()
{
	random_device rd;
	for (uint8_t i = 0; i < QLEN; i++)
		data[i] = rd() % 2;
}

//Operator = cho QInt
void QInt::operator=(const QInt& x)
{
	this->data = x.data;
}

//////////////////////////////////////////////////
//CAC OPERATOR TINH TOAN

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

QInt QInt::operator-(const QInt& x)
{
	//Tru la cong voi bu hai cua x
	return (*this) + (~x + QInt(2, "1"));
}

QInt QInt::operator*(const QInt& x)
{

	//Xu li so cung dau, khac dau
	QInt multer = q_abs(*this), multand = q_abs(x), ans = QInt(2, "0");
	//cout << "$ " << multer.toB10() << " " << multand.toB10();
	if (compare(multer, multand) < 0)
	{
		QInt __tmp(x);
		return  __tmp * (*this);
	}
	int sign = (this->data[QLEN - 1] == 0) ^ (x.data[QLEN - 1] == 1) ? 1 : -1;
	//Chuan  bi data
	int count = 0;
	QInt zero(2, "0");


	while (compare(multand, zero) != 0)
	{
		//cout << "$ " << multand.toB10() << endl;
		//Neu bit la 1 thi shift bit qua de cong, khong thi thoi
		if (multand.data[0] == 1)
			ans = ans + (multer << count);
		count++;
		multand = multand / QInt(10, "2");
	}

	//Neu khac dau thi dao dau, khong khac dau thi thoi
	if (sign == -1)
		ans = (~ans + QInt(2, "1"));
	return ans;
}

QInt QInt::operator/(const QInt& x)
{
	QInt dvd = q_abs(*this), dvs = q_abs(x), ans = QInt(2, "0");
	int sign = (this->data[QLEN - 1] == 0) ^ (x.data[QLEN - 1] == 1) ? 1 : -1;
	/*cout << "$ " << sign;
	cout << "$ " << dvd.toB10() << " " << dvs.toB10() << " " << endl;*/
	while (compare(dvd, dvs) >= 0)
	{
		QInt temp = dvs;
		QInt m = QInt(2, "1");
		QInt temp_temp = temp << 1;
		while (compare(temp_temp, dvd) <= 0)
		{
			temp = temp << 1;
			m = m << 1;
			temp_temp = temp << 1;
		}
		dvd = dvd - temp;
		ans = ans + m;
	}
	if (sign == -1)
		ans = ~ans + QInt(2, "1");
	/*cout << "$ " << ans.toB10() << endl;*/
	return ans;
}

//Ham tri tuyet doi cac kieu
QInt q_abs(QInt x)
{
	if (x.data[QLEN - 1] == 1)
		return (~x + QInt(2, "1"));
	return x;
}

//Ham compare cho 2 QInt, ho tro cho cac operator so sanh
inline int compare(QInt& lhs, QInt& rhs)
{
	if (lhs == rhs)
		return 0;
	else
	{
		QInt ans = lhs - rhs;
		return ans.data[QLEN - 1] == 1 ? -1 : 1;
	}
}

//Operator ==
inline bool operator==(const QInt& lhs, const QInt& rhs)
{
	for (int i = 0; i < QLEN; i++)
	{
		if (lhs.data[i] != rhs.data[i])
			return false;
	}
	return true;
}

//Ham cmp, ho tro so sanh bang
int cmp(QInt a, QInt b)
{
	if ((a ^ b) == QInt(2, "0"))
		return 0;
	return false;
}

//////////////////////////////////////////////////

QInt QInt::operator&(const QInt& x)
{
	return QInt(data & x.data);
}

QInt QInt::operator|(const QInt& x)
{
	return QInt(data | x.data);
}

QInt QInt::operator^(const QInt& x)
{
	return QInt(data ^ x.data);
}

QInt QInt::operator~() const
{
	return QInt(~(this->data));
}

QInt QInt::operator<<(const int8_t& x)
{
	return QInt(this->data << x);
}

//Shift luan li nen no phai khac voi phan con lai
QInt QInt::operator>>(const int8_t& x)
{
	
	if (x > QLEN || x < 0)
		abort();

	//Tao mot cai vong
	bitset<QLEN> re_value;
	//Init cai vong theo bit cuoi cua so can shift, luan li nam o day
	if (this->data[QLEN - 1]) re_value.flip();
	int i = 0;
	int k = x;

	//Cat cai vong ra theo so x can shift
	while (k < QLEN)
	{
		re_value[i++] = this->data[k++];
	}
	return QInt(re_value);
}

QInt QInt::rol() const
{
	// Safe mode
	QInt r(this->data << 1);
	r.data[0] = this->data[QLEN - 1];
	return r;
}

QInt QInt::ror() const
{
	// Safe mode
	QInt r(this->data >> 1);
	r.data[QLEN - 1] = this->data[0];
	return r;
}

//////////////////////////////////////////////////

//string QInt::toB2()
//{
//	string r;
//
//	for (uint8_t i = 0; i < QLEN; i++)
//		r.insert(r.begin(), (data[i] ? '1' : '0'));
//
//	// Trim string
//	if (r[0] == '0')
//	{
//		size_t del_mark = r.find_first_not_of('0');
//		r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
//	}
//
//	return r;
//}
//
//string QInt::toB10()
//{
//	string r;
//
//	uint8_t* b10 = new uint8_t[DLEN]();
//
//	// Tạo bản sao
//	QInt temp;
//	if (data[QLEN - 1])
//	{
//		bitset<QLEN> one;
//		one.flip(0);
//		temp = ~(*this) + QInt(one);
//	}
//	else
//	{
//		temp = *this;
//	}
//
//	// Cộng và ghi ra string
//	for (uint8_t b = 0; b < QLEN; b++)
//	{
//		if (temp.data[b])
//		{
//			for (uint8_t d = 0; d < DLEN; d++)
//			{
//				b10[d] += Pow2Table[b][d];
//				if (b10[d] >= 10 && d < DLEN - 1)
//				{
//					b10[d + 1] += b10[d] / 10;
//					b10[d] %= 10;
//				}
//			}
//		}
//	}
//	for (uint8_t d = 0; d < DLEN; d++)
//		r.append(to_string(b10[DLEN - 1 - d]));
//
//	// Trim string
//	if (r[0] == '0')
//	{
//		size_t del_mark = r.find_first_not_of('0');
//		r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
//	}
//
//	// Thêm dấu âm nếu có .-.
//	if (data[QLEN - 1])
//		r.insert(r.begin(), '-');
//
//	return r;
//}
//
//string QInt::toB16()
//{
//	string r;
//
//	for (uint8_t i = 0; i < QLEN; i += 4)
//	{
//		uint8_t t = 0;
//		for (uint8_t j : {0, 1, 2, 3})
//			t += data.test((size_t)i + j) << j;
//		r.insert(r.begin(), HEX[t]);
//	}
//
//	// Trim string
//	if (r[0] == '0')
//	{
//		size_t del_mark = r.find_first_not_of('0');
//		r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
//	}
//
//	return r;
//}

string QInt::toString(uint8_t base)
{
	string r;

	if (base == 2)
	{
		for (uint8_t i = 0; i < QLEN; i++)
			r.insert(r.begin(), (data[i] ? '1' : '0'));

		// Trim string
		if (r[0] == '0')
		{
			size_t del_mark = r.find_first_not_of('0');
			r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
		}
	}

	else if (base == 10)
	{
		uint8_t* b10 = new uint8_t[DLEN]();

		// Tạo bản sao
		QInt temp;
		if (data[QLEN - 1])
		{
			temp = ~(*this) + QInt(2, "1");
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

		delete[] b10;
	}

	else if (base == 16)
	{
		for (uint8_t i = 0; i < QLEN; i += 4)
		{
			uint8_t t = 0;
			for (uint8_t j : {0, 1, 2, 3})
				t += data.test((size_t)i + j) << j;
			r.insert(r.begin(), HEX[t]);
		}

		// Trim string
		if (r[0] == '0')
		{
			size_t del_mark = r.find_first_not_of('0');
			r.erase(0, (del_mark > r.size()) ? r.size() - 1 : del_mark);
		}
	}

	return r;
}
