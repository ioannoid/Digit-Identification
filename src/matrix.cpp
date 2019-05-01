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
	int ogrows = og.getData().size();
	int ogcols = og.getData()[0].size();
	int addendrows = addend.getData().size();
	int addendcols = addend.getData()[0].size();
	if (ogrows == addendrows && ogcols == addendcols) {
		
	}
	else {
		std::cout << "Two matrixes of different size were attempted to be added.";
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
        std::cout << "Error: Dimension mixmatch" << std::endl;
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