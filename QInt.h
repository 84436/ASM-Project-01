#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <random>
#include <math.h>
#include <algorithm>
#include <stack>
#include "FFTMachine.h"
using namespace std;

constexpr auto QLEN = 128;
constexpr auto DLEN = 39;
constexpr char HEX[] = "0123456789ABCDEF";

class QInt
{
	private:
		bitset<QLEN> data;

		static uint8_t** Pow2Table;
		void Pow2Table_Generate();
		static bool Pow2Table_Generate_ran;
		
	public:
		QInt() { Pow2Table_Generate(); }
		QInt(uint8_t base, string data);	// từ số sẵn có
		QInt(const QInt& x);                // copy từ QInt sẵn có
		void operator=(const QInt& x);	    // copy từ QInt sẵn có
		QInt(const bitset<QLEN> p_value);
		QInt( string str, int base = 10);  //convert baseX -> QInt: Tạm thời là base10
		void randomize();                   // test
		int bit_size() const;
		QInt operator+  (const QInt& x);
		//QInt operator-  (const QInt& x);
		QInt operator*  (const QInt& x);
		//QInt operator/  (const QInt& x);
		QInt operator&  (const QInt& x);
		QInt operator|  (const QInt& x);
		QInt operator^  (const QInt& x);
		QInt operator<< (const int& x);
		QInt operator>> (const int& x);
		QInt operator~  ();
		QInt rol        (const int& n);
		QInt ror        (const int& n);

		
		string toB2();
		string toB10();
		string toB16();
};
