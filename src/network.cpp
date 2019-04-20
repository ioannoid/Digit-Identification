#include "network.hpp"

network::network(std::vector<int> map) {
	w.resize(map.size() - 1);
	b.resize(map.size() - 1);

	for (int i = 1; i < map.size(); i++) {
		w[i - 1] = matrix::randn(map[i-1], map[i]);
		b[i - 1] = matrix::randn(map[i], 1);
	}
}

matrix network::predict(matrix in) {
	for (int i = 0; i < w.size(); i++) {
		in = sigmoid(w[i].T().dot(in) + b[i]);
	}

	return in;
}
matrix network::propagate(matrix in, matrix out) {

	/*matrix z1 = w[0].T().dot(in) + b[0];
	matrix a1 = sigmoid(z1);

	matrix z2 = w[1].T().dot(a1) + b[1];
	matrix a2 = sigmoid(z2);

	matrix dcost_da2 = d_cost(a2, out);
	matrix da2_dz2 = d_sigmoid(z2);
	matrix dz2_dw2 = a1;
	double dz2_db2 = 1;

	matrix dcost_dw2 = dz2_dw2.dot((dcost_da2*da2_dz2).T());
	matrix dcost_db2 = dcost_da2 * da2_dz2 * dz2_db2;


	std::cout << w[1] << std::endl << da2_dz2 << std::endl << dcost_da2;
	matrix dcost_da1 = w[1].dot(da2_dz2 * dcost_da2);
	matrix da1_dz1 = d_sigmoid(z1);
	matrix dz1_dw1 = in;
	double dz1_db1 = 1;

	matrix dcost_dw1 = dz1_dw1.dot((dcost_da1*da1_dz1).T());
	matrix dcost_db1 = dcost_da1 * da1_dz1 * dz1_db1;*/

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
	matrix dcost(in.row(), in.col());
	for(int r = 0; r < in.row(); r++) {
		for(int c = 0; c < in.col(); c++) {
			dcost[r][c] = 2.0 * (in[r][c] - out[r][c]);
		}
	}

	return dcost;
}

matrix network::sigmoid(matrix in) {
	matrix sig(in.row(), in.col());
	for(int r = 0; r < in.row(); r++) {
		for(int c = 0; c < in.col(); c++) {
			sig[r][c] = 1.0 / (1.0 + exp(-in[r][c]));
		}
	}
	return sig;
}

matrix network::d_sigmoid(matrix in) {
	matrix sig(in.row(), in.col());
	for(int r = 0; r < in.row(); r++) {
		for(int c = 0; c < in.col(); c++) {
			sig[r][c] = (exp(-in[r][c])) / pow((1.0 + exp(-in[r][c])),2.0);
		}
	}
	return sig;
}
