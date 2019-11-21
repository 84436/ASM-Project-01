#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <random>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

constexpr auto QLEN = 128;					// độ dài QInt = 128 bit ._.
constexpr auto DLEN = 39;					// ceil(log10(2^128))
constexpr char HEX[] = "0123456789ABCDEF";

class QInt
{
	private:
		bitset<QLEN> data;

		static uint8_t** Pow2Table;
		static bool Pow2Table_Generate_ran;
		void Pow2Table_Generate();			// tính 2^k, k=0..127
		
	public:
		QInt() { Pow2Table_Generate(); }
		// TODO: nhập 2 cái dưới lại
		QInt(uint8_t base, string data);	// từ string base2/base16
		QInt(string str, int base = 10);	// từ string base10
		QInt(const bitset<QLEN> p_value);	// từ bitset
		QInt(const QInt& x);                // copy
		void randomize();					// random; chỉ dùng để test
		void operator=(const QInt& x);	    // copy

		QInt operator+  (const QInt& x);
		QInt operator-  (const QInt& x);
		QInt operator*  (const QInt& x);
<<<<<<< HEAD
		QInt operator/  (const QInt& x);
=======
		//QInt operator/  (const QInt& x);

>>>>>>> origin
		QInt operator&  (const QInt& x);
		QInt operator|  (const QInt& x);
		QInt operator^  (const QInt& x);
		QInt operator~  () const;
<<<<<<< HEAD
		QInt rol        (const int& n);
		QInt ror        (const int& n);
=======
		QInt operator<< (const int8_t& x);
		QInt operator>> (const int8_t& x);
		QInt rol		() const;
		QInt ror		() const;
>>>>>>> origin
		

		friend QInt q_abs(QInt x);

		friend inline int compare( QInt& lhs,  QInt& rhs);
		friend inline bool operator==(const QInt& lhs, const QInt& rhs);

		string toB2();
		string toB10();
		string toB16();
};
