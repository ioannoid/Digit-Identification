#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "matrix.hpp"
#include "network.hpp"

using namespace std;

char* loadFile(const char* filename);
int filesize(const char* filename);

vector<vector<double>> processImages(const char* filename);
vector<double> processLabels(const char* filename);

matrix fmtMatrix(double num);
matrix mapMatrix(matrix m, double inmin, double inmax, double outmin, double outmax);

const int img_dimension = 28;
const char* imgfile = "train-images";
const char* labelfile = "train-labels";

int main() {

	srand (time(NULL));

	vector<vector<double>> images = processImages(imgfile);
	vector<double> labels = processLabels(labelfile);

	char choice;
	cout << "Would you like to train(t) or test(s): ";
	cin >> choice;
	cout << endl;

	if(choice == 't' || choice == 'T') {
		int iter;
		cout << "How many iterations of training would you like to run: ";
		cin >> iter;
		cout << endl;

		double lr;
		cout << "What would you like the learning rate to be: ";
		cin >> lr;
		cout << endl;

		network ii("imap.nn", lr);

		for (int i = 0; i < iter; i++) {
			int rindex = rand() % images.size();
			ii.propagate(mapMatrix(matrix(images[rindex]), 0, 255, -1, 1), fmtMatrix(labels[rindex]));
			if(i % 100 == 0) cout << i << endl;
		}

		ii.save("imap.nn");
	}
	else if(choice == 's' || choice == 'S') {

		network ii("imap.nn", 0.3);

		int iter;
		cout << "How many images would you like to test: ";
		cin >> iter;
		cout << endl;

		double right = 0;
		double total = 0;

		for (int i = 0; i < iter; i++) {
			int rindex = rand() % images.size();
			matrix prediction = ii.predict(mapMatrix(matrix(images[rindex]), 0, 255, -1, 1));
			int guess;
			double max = 0;
			for(int r = 0; r < prediction.row(); r++) {
				if (prediction[r][0] > max) {
					max = prediction[r][0];
					guess = r;
				} 
			}

			for(int j = 0; j < images[rindex].size(); j++) {
				if(images[rindex][j] > 0) cout << (char) 219 << (char) 219 << (char) 219;
				else cout << ' ' << ' ' << ' ';

				if(j % 28 == 0) cout << endl;
			}

			cout << "Guess: " << guess << endl << endl;
			if (guess == labels[rindex]) right++;
			total++;
			
		}

		cout << right / total << endl;
	}

	system("PAUSE");
    return 0;
}

char* loadFile(const char* filename) {
	char* imagebytes;
	int isize;

	ifstream imagedata;
	imagedata.open(filename, ios::binary);
	if (!imagedata) {
		throw std::out_of_range("Error: File not found.");
	}

	isize = filesize(filename);
	imagebytes = new char[isize];

	int it = 0;
	bool dblcheck = true;
	while (imagedata >> imagebytes && dblcheck) {
		it++;
		if (it > isize) dblcheck = false;
	}
	imagedata.close();
	return imagebytes;
}

vector<vector<double>> processImages(const char* filename) {
	//Load data from file into 1d array
	char* imgbytes = loadFile(filename);

	vector<vector<double>> images;
	vector<double> image;
	int isize = filesize(filename);
	
	int length = 0;
	double pixel = 0;

	//Process data from imgbytes array into 2d vector
	//Each element in first dimension represents an image, while each element in second dimension
	//represents a list of its pixeldata
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

vector<double> processLabels(const char* filename) {
	//Load data from file into 1d array
	char* lblbytes = loadFile(filename);

	vector<double> labels;
	int lsize = filesize(filename);

	double cur = 0;

	//Process data from lblbytes into appropriately formatted 1d vector
	for (int i = 8; i < lsize; i++) {
		cur = (double) (uint8_t) lblbytes[i];
		labels.push_back(cur);
	}

	return labels;
}

int filesize(const char* filename) {
	ifstream file;
	file.open(filename, ios::ate | ios::binary);

	if (!file) {
		throw std::out_of_range("Error: File not found.");
	}

	size_t size = file.tellg();

	//Convert size_t to int
	int finalsize = 0;
	for (size_t i = 0; i < size; i++) {
		finalsize += 1;
	}

	return finalsize;
}

matrix fmtMatrix(double num) {
	matrix fmt(10, 1);
	fmt[num][0] = 1;
	return fmt;
}

matrix mapMatrix(matrix m, double inmin, double inmax, double outmin, double outmax) {
	return (m - inmin) * (outmax - outmin) / (inmax - inmin) + outmin;
}
