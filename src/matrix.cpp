#include "matrix.hpp"

matrix::matrix(std::vector<std::vector<double>> v) : data(v) {}

matrix::matrix matrix::operator+ (matrix::matrix& addend) {
	matrix og = *this;

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