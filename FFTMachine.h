#pragma once
#include "Qint.h"
#include <cmath>
#define M_PI 3.141592653589793238462643383279502884L
class Complex
{
private:
	double i;
	double r;
public:
	Complex operator- (Complex const& a) const;
	Complex operator+ (Complex const& a) const;
	Complex operator* (Complex const& a) const;
	Complex& operator= (const Complex& a);
	Complex operator/ (int n) const;
	Complex(void);
	Complex(double const& real);
	Complex(double const& real, double const& imag);
	Complex(Complex const& v);
	operator int() const;
};
static void ifft(Complex* dist, Complex* src, int N);
static void fft(Complex* dist, Complex* src, int N);
static void fft(Complex* dist, Complex* src, int N) {
	int n = 0;
	for (int i = 1; i < N; i *= 2) {
		n++;
	}
	for (int i = 0; i <= N - 1; i++) {
		int a = i;
		int b = 0;
		for (int j = 0; j < n; j++) {
			b = (b << 1) + (a & 1);
			a >>= 1;
		}
		if (b > i) {
			dist[b] = src[b] + src[i];
			dist[i] = dist[b] - src[i];
			dist[b] = dist[b] - dist[i];
		}
	}
	for (int s = 1, m = 1; s <= n; s++) {
		m *= 2;
		Complex temp, u, omega, omigaM = Complex(cos(-2 * M_PI / m), sin(-2 * M_PI / m));
		for (int k = 0; k < N; k = k + m) {
			omega = Complex(1);
			for (int j = 0; j <= m / 2 - 1; j++) {
				temp = omega * dist[k + j + m / 2];
				u = dist[k + j];
				dist[k + j] = u + temp;
				dist[k + j + m / 2] = u - temp;
				omega = omega * omigaM;
			}
		}
	}
}

static void ifft(Complex* dist, Complex* src, int N) {
	int n = 0;
	for (int i = 1; i < N; i *= 2) {
		n++;
	}
	for (int i = 0; i <= N - 1; i++) {
		int a = i;
		int b = 0;
		for (int j = 0; j < n; j++) {
			b = (b << 1) + (a & 1);
			a >>= 1;
		}
		if (b > i) {
			dist[b] = src[b] + src[i];
			dist[i] = dist[b] - src[i];
			dist[b] = dist[b] - dist[i];
		}
	}
	for (int s = 1, m = 1; s <= n; s++) {
		m *= 2;
		Complex temp, u, omiga, omigaM = Complex(cos(2 * M_PI / m), sin(2 * M_PI / m));
		for (int k = 0; k < N; k = k + m) {
			omiga = Complex(1);
			for (int j = 0; j <= m / 2 - 1; j++) {
				temp = omiga * dist[k + j + m / 2];
				u = dist[k + j];
				dist[k + j] = u + temp;
				dist[k + j + m / 2] = u - temp;
				omiga = omiga * omigaM;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		dist[i] = dist[i] / N; //CHANGE
	}
}



/*bool isSameSign = true;
	string numStr1 = this->toB10();
	QInt _tmp(x); string numStr2 = _tmp.toB10();
	if (numStr1[0] == '-' || numStr2[0] == '-')
	{
		if (numStr1[0] == '-')      numStr1 = numStr1.substr(1);
		if (numStr2[0] == '-')      numStr2 = numStr2.substr(1);
		isSameSign = (numStr1[0] == '-') && (numStr2[0] == '-');
	}
	int lenStr1, lenStr2;
	lenStr1 = numStr1.size();
	lenStr2 = numStr2.size();
	int sumN = lenStr1 + lenStr2;
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
	for (int i = 0; i < N; i++) {
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
	delete[] ans;
	delete[] multiplier;
	delete[] multiplicand;
	if (!isSameSign)
	{
		res = "-" + res;
	}
	return QInt(res);*/