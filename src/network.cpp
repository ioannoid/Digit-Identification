#include "network.hpp"

network::network(std::vector<int> map) {
	w.resize(map.size() - 1);
	b.resize(map.size() - 1);

	for (int i = 1; i < map.size(); i++) {
		w[i - 1] = matrix::randn(map[i-1], map[i]);
		b[i - 1] = matrix::randn(1, map[i]);
	}
}

matrix network::predict(matrix in) {
	for (int i = 0; i < w.size(); i++) {
		in = sigmoid(in.dot(w[i]) + b[i]);
	}

	return in;
}
matrix network::propagate(matrix in, matrix out) {

	matrix predict = in;

	std::vector<matrix> z(w.size(), matrix());
	std::vector<matrix> a(w.size()+1, matrix());
	a[0] = in;

	for (int i = 0; i < w.size(); i++) {
		z[i] = predict.dot(w[i]) + b[i];
		a[i+1] = sigmoid(z[i]);
		predict = a[i+1];
	}

	for(auto w : a) std::cout << w;

	matrix fcost = cost(a[a.size()-1], out);

	std::vector<matrix> costw(w.size(), matrix());
	std::vector<matrix> costb(w.size(), matrix());

	//Final layer propagation
	matrix dcost_daf = d_cost(a[a.size()-1], out);
	matrix da_dzf = d_sigmoid(z[z.size()-1]);
	matrix dz_dwf = a[a.size()-2];
	matrix dcost_dwf = (dcost_daf * da_dzf).T().dot(dz_dwf).T();

	double dz_dbf = 1;
	matrix dcost_dbf = dcost_daf * da_dzf * dz_dbf;

	costw[costw.size()-1] = dcost_dwf;
	costb[costb.size()-1] = dcost_dbf;

	matrix da_dzp = da_dzf;
	matrix dz_dwp = dz_dwf;

	//Other layers
	for (int i = w.size()-2; i >= 0; i--)
	{
		matrix dcost_da = w[i+1].dot(da_dzp.T()).T() * dz_dwp;
		matrix da_dz = d_sigmoid(z[i]);
		matrix dz_dw = a[i];
		matrix dcost_dw = (dcost_da * da_dz).T().dot(dz_dw).T();

		double dz_db = 1;
		matrix dcost_db = dcost_da * da_dz * dz_db;

		costw[i] = dcost_dw;
		costb[i] = dcost_db;

		da_dzp = da_dz;
		dz_dwp = dz_dw;
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
	return 2*(in - out);
}

matrix network::sigmoid(matrix in) {
	return 1 / (1 + (2.718281 ^ -in));
}

matrix network::d_sigmoid(matrix in) {
	return sigmoid(in)*(1 - sigmoid(in));
}
