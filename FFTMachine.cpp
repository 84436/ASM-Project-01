#include "FFTMachine.h"

Complex::Complex(void) {
	r = 0;
	i = 0;
}

Complex::Complex(double const& real) {
	r = real;
	i = 0;
}

Complex::Complex(double const& real, double const& imag) {
	r = real;
	i = imag;
}

Complex::Complex(Complex const& v) {
	r = v.r;
	i = v.i;
}
Complex::operator int() const
{
	return this->r;
}
Complex Complex::operator- (Complex const& a) const {
	Complex result(double(r - a.r), double(i - a.i));
	return result;
}

Complex Complex::operator+ (Complex const& a) const {
	Complex result(double(r + a.r), double(i + a.i));
	return result;
}
Complex Complex::operator* (Complex const& a) const {
	Complex result(double(r * a.r - i * a.i), double(i * a.r + r * a.i));
	return result;
}
Complex Complex::operator/ (int n) const {
	Complex result(r / n, i / n);
	return result;
}
Complex& Complex::operator= (const Complex& a) {
	if (this == &a) return *this;  
	r = a.r;
	i= a.i;
}
