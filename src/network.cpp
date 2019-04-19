#include "network.hpp"

network::network(std::vector<int> map) {
	w.resize(map.size() - 1);
	b.resize(map.size() - 1);

	for (int i = 1; i < map.size(); i++) {
		w[i - 1] = matrix::randn(map[i-1], map[i]);
		b[i - 1] = matrix::randn(1, map[i]);
	}

	//for (auto m : w) std::cout << m;
	//for (auto m : b) std::cout << m;
}

matrix network::predict(matrix in) {
	for (int i = 0; i < w.size(); i++) {
		std::cout << in << w[i] << b[i] << std::endl;
		in = in.dot(w[i]) + b[i];
	}

	return in;
}

matrix network::sigmoid(matrix in) {
	return 1 / (1 + (2.718281 ^ -in));
}

matrix network::d_sigmoid(matrix in) {
	return sigmoid(in)*(1 - sigmoid(in));
}
