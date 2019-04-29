#include "matrix.hpp"

matrix::matrix() {}

matrix::matrix(int r, int c) {
	data.resize(r);
	for (int i = 0; i < r; i++) data[i] = std::vector<double>(c, 0);
}

matrix::matrix(std::vector<double> v) {
	data.resize(v.size());
	for(int i = 0; i < v.size(); i++) data[i] = std::vector<double>{v[i]};
}

matrix::matrix(std::vector<std::vector<double>> v) : data(v) {}

matrix::matrix(std::initializer_list<std::initializer_list<double>> il) {
	data.resize(il.size());
	for(int i = 0; i < il.size(); i++) {
		data[i] = std::vector<double>(*(il.begin()+i));
	}
}

std::vector<double>& matrix::operator[](int r) {
    return data[r];
}

matrix matrix::operator+ (matrix addend) {
	if (row() == addend.row() && col() == addend.col()) {
        matrix sum(row(), col());
        for (int r = 0; r < row(); r++) {
            for (int c = 0; c < col(); c++) {
                sum[r][c] = data[r][c] + addend[r][c];
            }
        }

        return sum;
    }
    else {
		throw std::out_of_range("Error: Dimension mixmatch");
    }
}

matrix matrix::operator-(matrix subtrahend) {
    if (row() == subtrahend.row() && col() == subtrahend.col()) {
        matrix diff(row(), col());
        for (int r = 0; r < row(); r++) {
            for (int c = 0; c < col(); c++) {
                diff[r][c] = data[r][c] - subtrahend[r][c];
            }
        }

        return diff;
    }
    else {
		throw std::out_of_range("Error: Dimension mixmatch");
    }
}

matrix matrix::operator*(matrix factor) {
	if (row() == factor.row() && col() == factor.col()) {
		matrix product(row(), col());
		for (int r = 0; r < row(); r++) {
			for (int c = 0; c < col(); c++) {
				product[r][c] = data[r][c] * factor[r][c];
			}
		}

		return product;
	}
	else {
		throw std::out_of_range("Error: Dimension mixmatch");
	}
}

matrix matrix::operator+(double addend) {
	matrix sum = data;
	for (int r = 0; r < row(); r++) {
		for (int c = 0; c < col(); c++) {
			sum[r][c] += addend;
		}
	}

	return sum;
}

matrix matrix::operator-(double subtrahend) {
	matrix diff = data;
	for (int r = 0; r < row(); r++) {
		for (int c = 0; c < col(); c++) {
			diff[r][c] -= subtrahend;
		}
	}

	return diff;
}

matrix matrix::operator*(double factor) {
	matrix product = data;
	for (int r = 0; r < row(); r++) {
		for (int c = 0; c < col(); c++) {
			product[r][c] *= factor;
		}
	}

	return product;
}

matrix matrix::operator/(double divisor) {
	matrix quotient = data;
	for (int r = 0; r < row(); r++) {
		for (int c = 0; c < col(); c++) {
			quotient[r][c] /= divisor;
		}
	}

	return quotient;
}

matrix matrix::operator^(double exponent) {
	matrix e = data;
	for (int r = 0; r < row(); r++) {
		for (int c = 0; c < col(); c++) {
			e[r][c] = pow(e[r][c], exponent);
		}
	}

	return e;
}

matrix matrix::operator-() {
	matrix negation(row(), col());
	for (int r = 0; r < row(); r++) {
		for (int c = 0; c < col(); c++) {
			negation[r][c] = -data[r][c];
		}
	}

	return negation;
}

matrix matrix::dot(matrix mat) {
	if (col() == mat.row()) {
		matrix dot(row(), mat.col());
		for (int r = 0; r < row(); r++) {
			for (int c = 0; c < mat.col(); c++) {
				double sum = 0;
				for (int i = 0; i < col(); i++) sum += (data[r][i] * mat[i][c]);
				dot[r][c] = sum;
			}
		}

		return dot;
	}
	else {
		throw std::out_of_range("Error: Dimension mixmatch");
	}
}

matrix matrix::T() {
	matrix t(col(), row());
	for (int c = 0; c < col(); c++) {
		for (int r = 0; r < row(); r++) {
			t[c][r] = data[r][c];
		}
	}

	return t;
}

matrix matrix::randn(int r, int c)
{
	std::random_device rd;
    std::mt19937 e2(rd());

	e2.seed(time(NULL));

	matrix randnMat(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			std::normal_distribution<double> dist(0.0, 2.0);
			randnMat[i][j] = dist(e2);;
		}
	return randnMat;
}

int matrix::row() {
    return data.size();
}

int matrix::col() {
    return data[0].size();
}
