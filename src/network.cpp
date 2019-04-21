#include "network.hpp"

network::network(std::vector<int> map) {
	w.resize(map.size() - 1);
	b.resize(map.size() - 1);

	for (int i = 1; i < map.size(); i++) {
		w[i - 1] = matrix::randn(map[i-1], map[i]);
		b[i - 1] = matrix::randn(map[i], 1);
	}
}

network::network(std::string fpath) {
	std::ifstream nnmap;
	nnmap.open(fpath);

    std::string type;
	std::string data;

    while (std::getline(nnmap, type)) {
		if (type[0] == 'w') {
			int row = stoi(type.substr(1, type.find('|') - 1));
			int length = stoi(type.substr(type.find('|') + 1));

			std::vector<std::vector<double>> vmatrix;
			std::vector<double> r;

			while (length != 0 && std::getline(nnmap, data)) {
				r.push_back(stod(data));
				row--;

				if (row == 0) {
					vmatrix.push_back(r);
					r.clear();
					row = stoi(type.substr(1, type.find('|')));
				}

				length--;
			}

			w.push_back(matrix(vmatrix));
		}
		else if (type[0] == 'b') {
			int length = stoi(type.substr(1));

			std::vector<std::vector<double>> vmatrix;

			while (length != 0 && std::getline(nnmap, data)) {
				vmatrix.push_back(std::vector<double>{stod(data)});
				length--;
			}

			b.push_back(matrix(vmatrix));
		}
    }

	nnmap.close();
}

matrix network::predict(matrix in) {
	for (int i = 0; i < w.size(); i++) {
		in = sigmoid(w[i].T().dot(in) + b[i]);
	}

	return in;
}

matrix network::propagate(matrix in, matrix out) {
	matrix predict = in;

	std::vector<matrix> z(w.size(), matrix());
	std::vector<matrix> a(w.size()+1, matrix());
	a[0] = in;

	for (int i = 0; i < w.size(); i++) {
		z[i] = w[i].T().dot(predict) + b[i];
		a[i+1] = sigmoid(z[i]);
		predict = a[i+1];
	}

	matrix fcost = cost(a[a.size()-1], out);

	std::vector<matrix> costw(w.size(), matrix());
	std::vector<matrix> costb(w.size(), matrix());

	//Final layer propagation
	matrix dcost_daf = d_cost(a[a.size()-1], out);
	matrix da_dzf = d_sigmoid(z[z.size()-1]);
	matrix dz_dwf = a[a.size()-2];
	matrix dcost_dwf = dz_dwf.dot((dcost_daf * da_dzf).T());

	double dz_dbf = 1;
	matrix dcost_dbf = dcost_daf * da_dzf * dz_dbf;

	costw[costw.size()-1] = dcost_dwf;
	costb[costb.size()-1] = dcost_dbf;
	
	matrix dcost_dap = dcost_daf;
	matrix da_dzp = da_dzf;

	//Other layers
	for (int i = w.size()-2; i >= 0; i--)
	{
		matrix dcost_da = w[i+1].dot(dcost_dap * da_dzp);
		matrix da_dz = d_sigmoid(z[i]);
		matrix dz_dw = a[i];
		matrix dcost_dw = dz_dw.dot((dcost_da * da_dz).T());

		double dz_db = 1;
		matrix dcost_db = dcost_da * da_dz * dz_db;

		costw[i] = dcost_dw;
		costb[i] = dcost_db;

		dcost_dap = dcost_da;
		da_dzp = da_dz;
	}

	for (int i = 0; i < w.size(); i++) {
		w[i] = w[i] - costw[i];
		b[i] = b[i] - costb[i];
	}

	return fcost;
}

matrix network::cost(matrix in, matrix out) {
	return ((in - out)^2);
}

matrix network::d_cost(matrix in, matrix out) {
	return 2.0 * (in - out);
}

matrix network::sigmoid(matrix in) {
	return 1 / (1 + (2.718281 ^ -in));
}

matrix network::d_sigmoid(matrix in) {
	return sigmoid(in) * (1 - sigmoid(in));
}

std::vector<matrix> network::getWeights() {
	return w;
}

std::vector<matrix> network::getBiases() {
	return b;
}

void network::save(std::string fname) {
	std::ofstream nnmap;
	nnmap.open(fname);

	for (int m = 0; m < w.size(); m++) {
		nnmap << "w" << w[m].col() << "|" << w[m].row() * w[m].col() << "\n";

		for (int r = 0; r < w[m].row(); r++) {
			for (int c = 0; c < w[m].col(); c++) {
				nnmap << w[m][r][c] << "\n";
			}
		}
	}

	for (int m = 0; m < b.size(); m++) {
		nnmap << "b" << b[m].row() << "\n";

		for (int r = 0; r < b[m].row(); r++) {
			nnmap << b[m][r][0] << "\n";
		}
	}
	nnmap.close();
}