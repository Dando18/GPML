#include <cstdio>
#include "Matrix.hpp"

int main(int argc, char** argv) {
	
	math::Matrix<int>* m = new math::Matrix<int>(4, 6, 0);

	for (int i = 0; i < m->rows(); ++i) {
		for (int j = 0; j < m->cols(); ++j) {
			printf(" %d", m->at(i,j));
		}
		printf("\n");
	}

	delete m;
	return 0;
}
