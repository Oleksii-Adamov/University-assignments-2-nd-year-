#pragma once
#include<complex>
struct Complex_num : std::complex<double>
{
	Complex_num() {

	}
	Complex_num(long long real, long long imag) {
		this->real(real);
		this->imag(imag);
	}
	friend bool operator<(const Complex_num& l, const Complex_num& r)
	{
		double l_sq_mod = l.real() * l.real() + l.imag() * l.imag();
		double r_sq_mod = r.real() * r.real() + r.imag() * r.imag();
		if (l_sq_mod == r_sq_mod) {
			return l.real() < r.real();
		}
		return l_sq_mod < r_sq_mod;
	}

	friend bool operator>(const Complex_num& l, const Complex_num& r)
	{
		double l_sq_mod = l.real() * l.real() + l.imag() * l.imag();
		double r_sq_mod = r.real() * r.real() + r.imag() * r.imag();
		if (l_sq_mod == r_sq_mod) {
			return l.real() > r.real();
		}
		return l_sq_mod > r_sq_mod;
	}
};

