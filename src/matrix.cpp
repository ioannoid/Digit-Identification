#include "matrix.hpp"

matrix::matrix(std::vector<std::vector<double>> v) : data(v) {}

matrix::matrix(int r, int c) {
    data.resize(r);
    for(int i = 0; i < r; i++) data[i] = std::vector<double>(c, 0);
}

std::vector<double>& matrix::operator[](int r) {
    return data[r];
}

matrix matrix::operator+ (matrix& addend) {
	matrix og = *this;
	if (row() == addend.row() && col() == addend.col()) {
		matrix n(row(),col());
		for (int y = 0; y < row(); y++) {
			for (int x = 0; x < col(); x++) {
				n[x][y] = og[x][y] + addend[x][y];
			}
		}
		return n;
	}
	else {
		throw std::out_of_range("Error: Dimension mixmatch.");
		exit(0);
	}

	return matrix({});
}

matrix matrix::operator-(matrix& subtrahend) {
    if (row() == subtrahend.row() && col() == subtrahend.col()) {
        matrix diff(row(), col());
        for (int r = 0; r < row(); r++) {
            for (int c = 0; c < col(); c++) {
                diff[r][c] = (*this)[r][c] - subtrahend[r][c];
            }
        }

        return diff;
    }
    else {
		throw std::out_of_range("Error: Dimension mixmatch");
        exit(0);
    }
}

matrix matrix::dot(matrix & mat) {
	if (col() == mat.row()) {
		matrix dot(row(), mat.col());
		for (int r = 0; r < row(); r++) {
			for (int c = 0; c < mat.col(); c++) {

			}
		}
	}
	else {
		throw std::out_of_range("Error: Dimension mixmatch");
		exit(0);
	}
}

int matrix::row() {
    return data.size();
}

int matrix::col() {
    return data[0].size();
}

std::vector<std::vector<double>> matrix::getData() {
    return data;
}