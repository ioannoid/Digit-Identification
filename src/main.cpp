#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "matrix.hpp"
#include "network.hpp"

using namespace std;

char* loadFile(const char* filename);
size_t filesize(const char* filename);

vector<vector<double>> processImages(char* imgbytes, size_t isize);
vector<double> processLabels(char* lblbytes, size_t lsize);

matrix fmtMatrix(double num);
matrix mapMatrix(matrix m, double inmin, double inmax, double outmin, double outmax);

const int img_dimension = 28;
const char* imgfile = "train-images";
const char* labelfile = "train-labels";

int main() {

	srand (time(NULL));

	char* imagebytes = loadFile(imgfile);
	char* labelbytes = loadFile(labelfile);
	
	size_t isize = filesize(imgfile);
	size_t lsize = filesize(labelfile);
	
<<<<<<< HEAD
	vector<vector<uint8_t>> images = processImages(imagebytes, isize);
	vector<uint8_t> labels = processLabels(labelbytes, lsize);

	
=======
	vector<vector<double>> images = processImages(imagebytes, isize);
	vector<double> labels = processLabels(labelbytes, lsize);

	network ii("iimap.nn", 0.3);

	for (int i = 0; i < 1000; i++) {
		int rindex = rand() % images.size();
		ii.propagate(mapMatrix(matrix(images[rindex]), 0, 255, -1, 1), fmtMatrix(labels[rindex]));
		if(i % 100 == 0) cout << i << endl;
	}

	// for (int i = 0; i < 100; i++) {
	// 	int rindex = rand() % images.size();
	// 	matrix prediction = ii.predict(matrix(images[rindex]));
	// 	int guess;
	// 	double max = 0;
	// 	for(int r = 0; r < prediction.row(); r++) {
	// 		cout << prediction[r][0] << " : " << max << endl;
	// 		if (prediction[r][0] > max) {
	// 			max = prediction[r][0];
	// 			guess = r;
	// 		} 
	// 	}
	// 	cout << prediction << guess << " : " << labels[rindex] << endl << endl;
		
	// }

	cout << ii.predict(matrix(images[0])) << endl << fmtMatrix(labels[0]) << endl;
	cout << ii.predict(matrix(images[1])) << endl << fmtMatrix(labels[1]) << endl;

	//cout << endl << ii.predict(matrix(images[0])/255);
	ii.save("iimap.nn");
>>>>>>> 171f121ad526e48ed077387bc9370b5476e53887

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

vector<vector<double>> processImages(char* imgbytes, size_t isize) {
	vector<vector<double>> images;
	vector<double> image;
	
	int length = 0;
	double pixel = 0;

	for (int i = 16; i < isize; i++) {
		pixel = (double) (uint8_t) imgbytes[i];
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

vector<double> processLabels(char* lblbytes, size_t lsize) {
	vector<double> labels;

	double cur = 0;

	for (int i = 8; i < lsize; i++) {
		cur = (double) (uint8_t) lblbytes[i];
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

matrix fmtMatrix(double num) {
	matrix fmt(10, 1);
	fmt[num][0] = 1;
	return fmt;
}

matrix mapMatrix(matrix m, double inmin, double inmax, double outmin, double outmax) {
	return (m - inmin) * (outmax - outmin) / (inmax - inmin) + outmin;
}
