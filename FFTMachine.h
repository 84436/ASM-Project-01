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