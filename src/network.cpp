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
	std::vector<matrix> a(w.size(), matrix());

	for(int i = 0; i < w.size(); i++) {
		z[i] = predict.dot(w[i]) + b[i];
		a[i] = sigmoid(z[i]);
		predict = a[i];
	}

	return a[a.size()-1];
}

matrix network::cost(matrix in, matrix out) {
	return 0.5*((in - out)^2);
}

matrix network::d_cost(matrix in, matrix out) {
	return in - out;
}

matrix network::sigmoid(matrix in) {
	return 1 / (1 + (2.718281 ^ -in));
}

matrix network::d_sigmoid(matrix in) {
	return sigmoid(in)*(1 - sigmoid(in));
}
