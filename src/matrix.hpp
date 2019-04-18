#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>
#include <ostream>

class matrix {
    
public:
    matrix(std::vector<std::vector<double>> v);

    matrix operator+ (matrix& addend);

    int row();
    int col();

    std::vector<std::vector<double>> getData();

    friend std::ostream& operator<<(std::ostream &out, const matrix &m);

private:
    std::vector<std::vector<double>> data;
};

inline std::ostream& operator<<(std::ostream &out, const matrix &m) {
    for (auto v : m.data)
}