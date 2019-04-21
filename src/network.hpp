#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "matrix.hpp"

class network {
public:
	network(std::vector<int> map);
	network(std::string fpath);

	matrix predict(matrix in);
	matrix propagate(matrix in, matrix out);

	matrix cost(matrix in, matrix out);
	matrix d_cost(matrix in, matrix out);

	matrix sigmoid(matrix in);
	matrix d_sigmoid(matrix in);

	std::vector<matrix> getWeights();
	std::vector<matrix> getBiases();

	void save(std::string fname);

private:
	std::vector<matrix> w;
	std::vector<matrix> b;
};