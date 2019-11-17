#include "QInt.h"

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
