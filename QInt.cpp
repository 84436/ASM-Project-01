#include "QInt.h"
#include <sstream>

QInt::QInt(const QInt& x)
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


//TODO: DANG TRONG QUA TRINH TEST : CAN BASE10 NEN MOI UP LEN
QInt QInt::operator*(const QInt& x)
{
	/*int muler_len = this->bit_size();
	int muland_len = x.bit_size();
	int N = 1;
	for (int i = 1; i < (muler_len + muland_len); i *= 2) {
		N *= 2;
	}*/
	string numStr1 = "9";
	string numStr2 = "190";
	int lenStr1, lenStr2, sumN;
	lenStr1 = numStr1.size();
	lenStr2 = numStr2.size();
	sumN = lenStr1 + lenStr2;
	int N = 1;
	for (int i = 1; i < sumN; i *= 2) {
		N *= 2;
	}
	Complex* multiplier = new Complex[N];
	Complex* multiplicand = new Complex[N];
	Complex* ans = new Complex[N];

	for (int i = lenStr1 -1; i >= 0; i--) {
		//multiplier[muler_len - i - 1] = Complex((double)(this->data[i]));
		multiplier[lenStr1 - i - 1] = Complex((double)(numStr1[i] - '0'));
	}
	for (int i = lenStr2 - 1;i >= 0;i--){
		//multiplicand[muland_len  - i - 1] = Complex((double)(x.data[i]));
		multiplicand[lenStr2  - i - 1] = Complex((double)(numStr2[i] - '0'));
	}

	fft(multiplier, multiplier, N);
	fft(multiplicand, multiplicand, N);

	for (int i = 0; i < N; i++) {
		ans[i] = (multiplier[i] * multiplicand[i]);
	}
	ifft(ans, ans, N);
	vector<int> rst;
	int curr, roundup = 0;
	for (int i = 0; i < sumN; i++) {
		curr = (int)ans[i] + roundup;
		rst.push_back(curr % 10);
		roundup = curr / 10;
	}

	vector<int>::reverse_iterator rit = rst.rbegin();
	while ((*rit) == 0) {
		rst.pop_back();
		rit = rst.rbegin();
	}

	stringstream rststream;
	for (; rit != rst.rend(); rit++) {
		rststream << *rit;//+'0';
	}
	string res;
	rststream >> res;
	cout << "$# " << res << endl;
	/*bitset<QLEN> result;
	for (int i = 0; i < QLEN - 1; i++)
		result[i] = rst[QLEN - i - 1];*/
	delete[] ans;
	delete[] multiplier;
	delete[] multiplicand;
	return QInt();
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
	if (v_shift > QLEN || v_shift <= 0)
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
		if ((i + 1) < QLEN && (i + 1) % 4 == 0)
			r.insert(r.begin(), ' ');
	}
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
		if ((i + 4) < QLEN && (i + 4) % 16 == 0)
			r.insert(r.begin(), ' ');
	}
	return r;
}
