#include "matrix.hpp"

matrix::matrix(std::initializer_list<std::initializer_list<double>> in) {
    data.resize(in.size());
    for(auto &v : data) v.resize(in.begin.size());
    
    for(int i = 0; i < data.size())
}

int matrix::row() {
    return data.size();
}

int matrix::col() {
    return data[0].size();
}