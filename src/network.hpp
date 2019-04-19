#pragma once

#include <iostream>
#include <vector>
#include <cstdarg>

#include "matrix.hpp"

class network {
public:
	network(std::vector<int> map);

	friend class trainer;

private:
	std::vector<matrix> w;
	std::vector<matrix> b;
};