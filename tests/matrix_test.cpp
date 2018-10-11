#include <iostream>
#include "Matrix.hpp"

template<typename T>
void print(const math::Matrix<T>&);

void test_construction();
//void test_addition();

int main(int argc, char** argv) {

	test_construction();	

	std::cout << std::endl;
	return 0;
}


template<typename T>
void print(const math::Matrix<T>& m) {
	for (int i = 0; i < m.rows(); ++i) {
		for (int j = 0; j < m.cols(); ++j)
			std::cout << " " << m.at(i,j);
		std::cout << "\n";
	}
}

void test_construction() {
	std::cout << "testing construction...\n";
	
	std::cout << "creating 4x6 init to 1\n";	
	math::Matrix<int>* a = new math::Matrix<int> (4, 6, 1);
	print(*a);

	std::cout << "\ncreating 5x5 init to -25\n";
	math::Matrix<int>* b = new math::Matrix<int> (5, -25);
	print(*b);

	std::cout << "\ncreating 3x2 init to {{1,2},{3,4},{5,6}}\n";
	std::vector<std::vector<int> > dat = { {1,2}, {3,4}, {5,6} };
	math::Matrix<int>* c = new math::Matrix<int> (3, 2, dat);
	print(*c);

	delete a;
	delete b;
	delete c;
	std::cout << "construction success\n";
}

