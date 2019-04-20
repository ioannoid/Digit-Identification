#include <iostream>
#include "matrix.hpp"
#include "network.hpp"

using namespace std;

int main() {
	network nn({ 2, 3,4, 2 });

	cout << nn.predict(matrix{{1},{2}});
	cout << nn.predict(matrix{{2},{1}});
	cout << nn.predict(matrix{{3},{4}}) << std::endl;

	srand(time(NULL));

	vector<matrix> n1;
	n1.push_back(matrix{{1},{2}});
	n1.push_back(matrix{{2},{1}});
	n1.push_back(matrix{{3},{4}});

	vector<matrix> n2;

	n2.push_back(matrix{{0},{1}});
	n2.push_back(matrix{{1},{1}});
	n2.push_back(matrix{{1},{0}});

	for(int i = 0; i < 10000; i++) {
		int n = rand() % 3;
		nn.propagate(n1[n], n2[n]);
	} 

	cout << nn.predict(matrix{{1},{2}});
	cout << nn.predict(matrix{{2},{1}});
	cout << nn.predict(matrix{{3},{4}});
	
	system("PAUSE");

    return 0;
}