#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
	matrix::matrix t = matrix({{1,2,3},{1,2,3},{1,2,3}});
	cout << t.data[0][0];

    return 0;
}