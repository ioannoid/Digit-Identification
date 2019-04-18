#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

class matrix {
    
public:
    matrix(std::initializer_list<std::initializer_list<double>> in);

    

private:
    std::vector<std::vector<double>> data;
};