#include <iostream>
#include <vector>

#include "matrix.hpp"

using namespace std;

int main() {
    
	matrix m({{1,1,1}, {2,2,2}, {3,3,3}});
    matrix n({{4,4,4}, {5,5,5}, {6,6,6}});

    cout << m + n << endl;

	matrix t({{1,2,3},{4,5,6},{7,8,9}});
	matrix s({{9,8,7},{6,5,4},{3,2,1}});

	cout << t.dot(s.T()) << endl;

	matrix x = matrix::randn(3, 3);

	cout << x;

	system("PAUSE");

    return 0;
}