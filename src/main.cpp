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