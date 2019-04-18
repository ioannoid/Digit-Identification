#include "matrix.hpp"

matrix::matrix(std::vector<std::vector<double>> v) : data(v) {}

matrix matrix::operator+ (matrix& addend) {
	matrix og = *this;
	int ogrows = og.getData().size();
	int ogcols = og.getData()[0].size();
	int addendrows = addend.getData().size();
	int addendcols = addend.getData()[0].size();
	if (ogrows == addendrows && ogcols == addendcols) {

	}
	else {
		cout << "Two matrixes of different size were attempted to be added.";
		exit(0);
		
	}

	return matrix({});
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