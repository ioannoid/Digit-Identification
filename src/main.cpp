#include <iostream>
#include <vector>
#include <fstream>

#include "matrix.hpp"
#include "network.hpp"

using namespace std;

char* loadFile(const char* filename);
size_t filesize(const char* filename);

int main() {
	char* imagebytes = loadFile("train-images");
	char* labelbytes = loadFile("train-labels");

	int fs = filesize("train-images");
	for (int i = 0; i < 16; i++) {
		cout << (uint32_t)imagebytes[i] << " ";
	}

	/*network nn("nnmap.nn");

	vector<matrix> w = nn.getWeights();
	vector<matrix> b = nn.getBiases();

	for(auto m : w) cout << m << endl;
	for(auto m : b) cout << m << endl;

	cout << nn.predict(matrix{{1},{2}});
	cout << nn.predict(matrix{{2},{1}});
	cout << nn.predict(matrix{{3},{4}});*/

	/*network nn(std::vector<int>{ 2, 3,4, 2 });

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
		matrix out = nn.propagate(n1[n], n2[n]);

		if(i % 100 == 0) {
			//cout << out << endl;
		} 
	} 

	cout << nn.predict(matrix{{1},{2}});
	cout << nn.predict(matrix{{2},{1}});
	cout << nn.predict(matrix{{3},{4}});
	
	nn.save("nnmap1.nn");*/

    return 0;
}

char* loadFile(const char* filename) {
	char* imagebytes;
	size_t isize;

	ifstream imagedata;
	imagedata.open(filename, ios::binary);
	if (!imagedata) {
		throw std::out_of_range("Error: File not found.");
	}

	isize = filesize(filename);
	imagebytes = new char[isize];

	imagedata.read(imagebytes, isize);
	imagedata.close();
	return imagebytes;
}

size_t filesize(const char* filename) {
	ifstream file;
	file.open(filename, ios::ate | ios::binary);

	if (!file) {
		throw std::out_of_range("Error: File not found.");
	}

	size_t size = file.tellg();
	return size;
}