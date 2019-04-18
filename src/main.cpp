#include <iostream>
#include <vector>

#include "matrix.hpp"

using namespace std;

int main() {
    
	matrix m({{1,2,3}, {1,2,3}, {1,2,3}});
    matrix n({{3,2,1}, {3,2,1}, {3,2,1}});

    cout << m - n << endl;

    return 0;
}