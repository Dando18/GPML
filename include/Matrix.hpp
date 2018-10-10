#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <utility>		// std::pair
#include <stdexcept>	// std::invalid_argument
#include "typedefs.h"	// uint

namespace math {


template<typename N>
class Matrix {
	public:
		Matrix(uint size, N fill);
		Matrix(uint rows, uint cols, N fill);
		Matrix(const Matrix&);

		N at(uint r, uint c);
		void set(uint r, uint c, N val);

		N* row(uint r);		// returns a copy
		N* col(uint c);		// returns a copy

		std::pair<uint, uint> shape() { return std::make_pair(_rows, _cols); }
		uint rows() { return _rows; }
		uint cols() { return _cols; }
		uint size() { return _size; }



		// overloaded operators
		Matrix& operator+=(const Matrix&);
		Matrix& operator-=(const Matrix&);
		Matrix& operator*=(const N&);
		Matrix& operator*=(const Matrix&);
		Matrix& operator/=(const Matrix&);
		
		~Matrix();
		
	private:
		uint _size;
		uint _cols;
		uint _rows;
		N** _matrix;
};

// free standing operator declarations
template<typename N>
Matrix<N> operator+(Matrix<N> ,const Matrix<N>&);
template<typename N>
Matrix<N> operator-(Matrix<N>, const Matrix<N>&);
template<typename N>
Matrix<N> operator*(Matrix<N>, const N&);
template<typename N>
Matrix<N> operator/(Matrix<N>, const N&);
template<typename N>
Matrix<N> operator*(Matrix<N>, const Matrix<N>&);


// define standard Matrix classes for easier use
typedef Matrix<int> iMatrix;
typedef Matrix<float> fMatrix;
typedef Matrix<double> dMatrix;


// implementation

/*
	initializes the matrix with dimensions size*size and 
	sets each element to fill.
	size - size of square matrixa
	fill - default arg
*/
template<typename N>
Matrix<N>::Matrix(uint size, N fill) : _size(size*size), _cols(size), _rows(size) {
	// allocate rows
	_matrix = new N*[_rows];

	// allocate col in each row
	for (uint r = 0; r < _rows; ++r) {
		_matrix[r] = new N[_cols];

		// set each value to fill
		for (uint c = 0; c < _cols; ++c) {
			_matrix[r][c] = fill;
		}
	}
}


/*
	initilize with dimensions rows*cols and elements fill
*/
template<typename N>
Matrix<N>::Matrix(uint rows, uint cols, N fill) : _size(rows*cols), _cols(cols), _rows(rows) {
	// allocate rows
	_matrix = new N*[_rows];

	// allocate col in each row
	for (uint r = 0; r < _rows; ++r) {
		_matrix[r] = new N[_cols];

		// set each value to fill
		for (uint c = 0; c < _cols; ++c) {
			_matrix[r][c] = fill;
		}
	}
}

template<typename N>
Matrix<N>::Matrix(const Matrix& m) : _size(m.size()), _cols(m.cols()), _rows(m.rows()) {
	// allocate rows
	_matrix = new N*[_rows];

	// allocate col in each row
	for (uint r = 0; r < _rows; ++r) {
		_matrix[r] = new N[_cols];
		
		// set each value from m
		for (uint c = 0; c < _cols; ++c) {
			_matrix[r][c] = m.at(r,c);
		}
	}
}

/*
	returns element at r,c
	return can be NULL
	throws invalid_argument if r or c are not within [0, rows()-1] or [0, cols()-1]
*/
template<typename N>
N Matrix<N>::at(uint r, uint c) {
	if (r < 0 || r >= _rows) 
		throw std::invalid_argument("row out of range");
	if (c < 0 || c >= _cols)
		throw std::invalid_argument("column out of range");

	return _matrix[r][c];
}


/*
	Sets element at r,c to val
	note: r,c is zero index
	note: val can be NULL
	throws invalid_argument if r or c are not within [0, rows()-1] or [0, cols()-1]
*/
template<typename N>
void Matrix<N>::set(uint r, uint c, N val) {
	if (r < 0 || r >= _rows)
		throw std::invalid_argument("row out of range");
	if (c < 0 || c >= _cols)
		throw std::invalid_argument("column out of range");

	_matrix[r][c] = val;
}


template<typename N>
Matrix<N>& Matrix<N>::operator+=(const Matrix& m) {
	if (m._rows != _rows && m._cols != _cols) 
		throw std::invalid_argument("arrays must have same size");

	for (int r = 0; r < _rows; ++r)
		for (int c = 0; c < _cols; ++c)
			_matrix[r][c] += m._matrix[r][c];

	return *this;
}

template<typename N>
Matrix<N> operator+(Matrix<N> lhs, const Matrix<N>& rhs) {
	lhs += rhs;
	return lhs;
}





template<typename N>
Matrix<N>::~Matrix() {
	for (uint r = 0; r < _rows; ++r) {
		delete[] _matrix[r];
	}
	delete[] _matrix;
}

}

#endif
