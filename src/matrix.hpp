#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <initializer_list>

class matrix {

public:
	matrix();
	matrix(int r, int c);
	matrix(std::vector<std::vector<double>> v);
	matrix(std::initializer_list<std::initializer_list<double>> il);

	std::vector<double>& operator[](int r);

	matrix operator+(matrix addend);
	matrix operator-(matrix subtrahend);
	matrix operator*(matrix factor);

	matrix operator+(double addend);
	matrix operator-(double subtrahend);
	matrix operator*(double factor);
	matrix operator^(double exponent);
	matrix operator-();

	friend matrix operator+(double addend, matrix maddend);
	friend matrix operator-(double minuend, matrix subtrahend);
	friend matrix operator*(double factor, matrix mfactor);
	friend matrix operator/(double dividend, matrix divisor);
	friend matrix operator^(double base, matrix exponent);

	matrix dot(matrix mat);
	matrix T();

	static matrix randn(int r, int c);

    int row();
    int col();

    friend std::ostream& operator<<(std::ostream &out, const matrix &m);

private:
    std::vector<std::vector<double>> data;
};

inline matrix operator+(double addend, matrix maddend) {
	matrix sum(maddend.row(), maddend.col());
	for (int r = 0; r < sum.row(); r++) {
		for (int c = 0; c < sum.col(); c++) {
			sum[r][c] = addend + maddend[r][c];
		}
	}

	return sum;
}

inline matrix operator-(double minuend, matrix subtrahend) {
	matrix diff(subtrahend.row(), subtrahend.col());
	for (int r = 0; r < diff.row(); r++) {
		for (int c = 0; c < diff.col(); c++) {
			diff[r][c] = minuend - subtrahend[r][c];
		}
	}

	return diff;
}

inline matrix operator*(double factor, matrix mfactor) {
	matrix product(mfactor.row(), mfactor.col());
	for (int r = 0; r < product.row(); r++) {
		for (int c = 0; c < product.col(); c++) {
			product[r][c] = factor * mfactor[r][c];
		}
	}

	return product;
}

inline matrix operator/(double dividend, matrix divisor) {
	matrix quotient(divisor.row(), divisor.col());
	for (int r = 0; r < quotient.row(); r++) {
		for (int c = 0; c < quotient.col(); c++) {
			quotient[r][c] = dividend / divisor	[r][c];
		}
	}

	return quotient;
}

inline matrix operator^(double base, matrix exponent) {
	matrix e(exponent.row(), exponent.col());
	for (int r = 0; r < e.row(); r++) {
		for (int c = 0; c < e.col(); c++) {
			e[r][c] = pow(base, exponent[r][c]);
		}
	}

	return e;
}

inline std::ostream& operator<<(std::ostream &out, const matrix &m) {
    for (auto v : m.data) {
        for (auto d : v) out << d << " ";
        out << std::endl;
    }

    return out;
}