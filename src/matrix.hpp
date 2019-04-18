#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>
#include <ostream>

class matrix {
    
public:
    matrix(std::vector<std::vector<double>> v);
    matrix(int r, int c);

    std::vector<double>& operator[](int r);

    matrix operator+(matrix& addend);
    matrix operator-(matrix& subtrahend);

	matrix dot(matrix& mat);
	matrix T();

    int row();
    int col();

    std::vector<std::vector<double>> getData();

    friend std::ostream& operator<<(std::ostream &out, const matrix &m);

private:
    std::vector<std::vector<double>> data;
};

inline std::ostream& operator<<(std::ostream &out, const matrix &m) {
    for (auto v : m.data) {
        for (auto d : v) out << d << " ";
        out << std::endl;
    }

    return out;
}