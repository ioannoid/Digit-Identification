#include <iostream>
#include <vector>

#include "matrix.hpp"

using namespace std;

int main() {
    
	matrix m({{1,1,1}, {2,2,2}, {3,3,3}});
    matrix n({{4,4,4}, {5,5,5}, {6,6,6}});

    cout << m + n << endl;

    return 0;
}