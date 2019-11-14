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

QInt QInt::operator~()
{
	QInt r = *this;
	for (uint8_t i = 0; i < QLEN; i++)
	{
		r.data[i] = !(r.data[i]);
	}
	return r;
}

//QInt QInt::rol()
//{
//	QInt x = *this;
//	bool MSB = x.data[0];
//	for (uint8_t i = 1; i < QLEN; i++)
//	{
//		x.data[i - 1] = x.data[i];
//	}
//	x.data[QLEN - 1] = MSB;
//	return x;
//}
//
//QInt QInt::ror()
//{
//	QInt x = *this;
//	bool LSB = x.data[QLEN - 1];
//	for (int8_t i = QLEN - 2; i >= 0; i--)
//	{
//		x.data[i + 1] = x.data[i];
//	}
//	x.data[0] = LSB;
//	return x;
//}

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
