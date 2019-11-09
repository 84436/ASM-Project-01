#include "QInt.h"

void QInt::randomize()
{
	random_device r;
	for (uint8_t i = 0; i < QLEN; i++)
		data[i] = r() % 2;
}

string QInt::toB2()
{
	string s;
	for (uint8_t i = 0; i < QLEN; i++) {
		s.push_back((data[i] ? '1' : '0'));
		if ((i + 1) % 4 == 0)
			s.push_back(' ');
	}
	return s;
}

string QInt::toB16()
{
	string s;
	for (uint8_t i = 0; i < QLEN; i += 4)
	{
		uint8_t t = 0;
		for (uint8_t j : {0, 1, 2, 3})
			t += data.test(i + j) << (3 - j);
		s.push_back(HEX[t]);
		if ((i - 12) % 16 == 0)
			s.push_back(' ');
	}
	return s;
}
