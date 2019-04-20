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