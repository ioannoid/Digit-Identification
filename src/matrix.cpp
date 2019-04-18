#include "matrix.hpp"

matrix::matrix(std::vector<std::vector<double>> v) : data(v) {}

int matrix::row() {
    return data.size();
}

int matrix::col() {
    return data[0].size();
}

std::vector<std::vector<double>> matrix::getData() {
    return data;
}