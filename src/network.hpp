#pragma once

#include <iostream>
#include <vector>

#include "matrix.hpp"

class network {
public:
	network(std::vector<int> map);

	matrix predict(matrix in);

	matrix sigmoid(matrix in);
	matrix d_sigmoid(matrix in);

private:
	std::vector<matrix> w;
	std::vector<matrix> b;
};