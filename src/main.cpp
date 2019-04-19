#include <iostream>
#include "matrix.hpp"
#include "network.hpp"

using namespace std;

int main() {
    
	matrix m({ { 1,2,3 }, { 1,2,3 } });

	network nn({ 2, 4, 2 });
	matrix prediction = nn.predict(matrix({ {2,2} }));

	cout << prediction << endl;

	

	system("PAUSE");

    return 0;
}