#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <random>
using namespace std;

constexpr auto QLEN = 128;
constexpr char HEX[] = "0123456789ABCDEF";

class QInt
{
	private:
		bitset<QLEN> data;

	public:
		QInt() {}
		//QInt(uint8_t base, string data);  // từ số sẵn có
		QInt(const QInt& x);                // copy từ QInt sẵn có
		void operator=(const QInt& x);	    // copy từ QInt sẵn có

		void randomize();                   // test

		QInt operator+  (const QInt& x);
		//QInt operator-  (const QInt& x);
		//QInt operator*  (const QInt& x);
		//QInt operator/  (const QInt& x);
		QInt operator&  (const QInt& x);
		QInt operator|  (const QInt& x);
		QInt operator^  (const QInt& x);
		//QInt operator<< (const QInt& x);
		//QInt operator>> (const QInt& x);
		QInt operator~  ();
		//QInt rol        ();
		//QInt ror        ();

		string toB2();
		//string toB10();
		string toB16();
};
