#include <iostream>
#include <vector>

#include "matrix.hpp"

using namespace std;

int main() {
    
	matrix m({ {1,2,3}, {1,2,3}, {1,2,3} });


    vector<vector<double>> n =  m.getData();

    for(auto v : n) {
        for(auto i : v)
        {
            cout << i << endl;
        }
    }

    return 0;
}