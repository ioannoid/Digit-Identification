#include <iostream>
#include "matrix.hpp"
#include "network.hpp"

using namespace std;

int main() {

	network nn({ 2, 2, 2 });

	cout << nn.predict(matrix({{2,2}}));

	for(int i = 0; i < 100; i++) nn.propagate(matrix({{2,2}}), matrix({{1,0}}));

	cout << nn.predict(matrix({{2,2}}));
	
	system("PAUSE");

    return 0;
}