#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

class matrix {
    
public:
    matrix(std::vector<std::vector<double>> v);

    int row();
    int col();

    std::vector<std::vector<double>> getData();

private:
    std::vector<std::vector<double>> data;
};