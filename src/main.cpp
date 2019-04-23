#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "matrix.hpp"
#include "network.hpp"

using namespace std;

char* loadFile(const char* filename);
size_t filesize(const char* filename);
vector<vector<uint8_t>> processImages(char* imgbytes, size_t isize);
vector<uint8_t> processLabels(char* lblbytes, size_t lsize);

const int img_dimension = 28;
const char* imgfile = "train-images";
const char* labelfile = "train-labels";

int main() {
	char* imagebytes = loadFile(imgfile);
	char* labelbytes = loadFile(labelfile);
	
	size_t isize = filesize(imgfile);
	size_t lsize = filesize(labelfile);
	
	vector<vector<uint8_t>> images = processImages(imagebytes, isize);
	vector<uint8_t> labels = processLabels(labelbytes, lsize);

	int img;

	cin >> img;
	vector<uint8_t> image = images[img];

	fstream file;
	file.open("header", ios::in|ios::binary|ios::ate);
    
    size_t hsize = 0;
    char* header;

    file.seekg(0, ios::end);
	hsize = file.tellg(); 
	file.seekg(0, ios::beg); 

    header = new char[hsize];

    file.read( header, hsize );
    file.close();

    file.open("file.bmp", ios::binary | ios::out);
    file.write(header, hsize);

	int row = 0;
	vector<uint8_t> pixels;

	for(int i = image.size()-1; i >= 0; i--) {
        pixels.push_back(image[i]);
        pixels.push_back(image[i]);
        pixels.push_back(image[i]);
        row++;
        if(row==28) {

            std::reverse(pixels.begin(), pixels.end());

            for (int j = 0; j < pixels.size(); j++) file.write((char*) &pixels[j], sizeof(char));
            pixels.clear();
            row = 0;
        }
    }

	file.close();
	
	//Print out digit images with matching labels
	// int r = 0;
	// for (int i = 0; i < 5; i++) {
	// 	for (int j = 0; j < images[i].size(); j++) {
	// 		if (unsigned(images[i][j]) > 0) {
	// 			cout << 1 << "";
	// 		}
	// 		else {
	// 			cout << 0 << "";
	// 		}
	// 		r++;
	// 		if (r == 28) {
	// 			r = 0;
	// 			cout << endl;
	// 		}
	// 	}
	// 	cout << unsigned(labels[i]) << endl << endl;
	// }

	system("PAUSE"); 

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

vector<vector<uint8_t>> processImages(char* imgbytes, size_t isize) {
	vector<vector<uint8_t>> images;
	vector<uint8_t> image;
	
	int length = 0;
	uint8_t pixel = 0;

	for (int i = 16; i < isize; i++) {
		memcpy(&pixel, imgbytes + i, 1);
		image.push_back(pixel);
		length++;
		if (length == img_dimension * img_dimension) {
			images.push_back(image);
			image.clear();
			length = 0;
		}
	}
	return images;
}

vector<uint8_t> processLabels(char* lblbytes, size_t lsize) {
	vector<uint8_t> labels;

	for (int i = 8; i < lsize; i++) {
		uint8_t cur = 0;
		memcpy(&cur, lblbytes + i, 1);
		labels.push_back(cur);
	}

	return labels;
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