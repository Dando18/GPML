/** @file Matrix.hpp
	Contains Matrix class definition and implementation.
	@author Daniel Nichols
	@date October 2018
*/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <utility>		// pair, make_pair
#include <stdexcept>	// invalid_argument
#include <vector>		// vector
#include "typedefs.h"	// uint


namespace math {


/** @brief Matrix generic class
	
	@author Daniel Nichols
	@date October 2018
*/
template<typename N>
class Matrix {
	public:
		// constructors
		/** Square matrix constructor. Creates a size*size matrix
			with every value set to fill.
			@param size - size of the rows and cols of the matrix
			@param fill - default value for every entry
		*/
		Matrix(uint size, const N& fill);

		/** Matrix constructor. Creates a rows*cols matrix
			with every value set to fill.
			@param rows - number of rows
			@param cols - number of cols
			@param fill - default value for every entry
		*/
		Matrix(uint rows, uint cols, const N& fill);
		
		/**	Creates and fills matrix with data from `N** data` array. Will seg-fault if
			`data` is not `size * size`.
			@param size - size of square matrix
			@param data - 2d array of data to fill matrix
		*/
		Matrix(uint size, N** data);

		/** Creates and fills matrix with data from `vector<vector<N> > data`. Will seg-fault
			or ignore excess data if `data` is not `size * size`.
			@param size - size of square matrix
			@param data - 2d vector of data to fill matrix
		*/
		Matrix(uint size, const std::vector<std::vector<N> >& data);

		/**	Creates and fills matrix with data from `N** data` array. Will seg-fault if
			`data` is not `rows * cols`.
			@param rows - number of rows in resulting matrix
			@param cols - number of columns in resulting matrix
			@param data - 2d array of data to fill matrix
		*/
		Matrix(uint rows, uint cols, N** data);

		/** Creates and fills matrix with data from `vector<vector<N> > data`. Will seg-fault
			or ignore excess data if `data` is not `rows * cols`.
			@param rows - number of rows in resulting matrix
			@param cols - number of cols in resulting matrix
			@param data - 2d vector of data to fill matrix
		*/
		Matrix(uint rows, uint cols, const std::vector<std::vector<N> >& data);

		/** Copy constructor. Copies matrix m into new matrix.
			@param m - matrix to be copied
		*/
		Matrix(const Matrix& m);


		// member functions
		/** Get element at r, c of the matrix 0-indexed.
			@param r - row of return element
			@param c - column of return element
			@throw invalid_argument thrown if r<0 or r>=rows() or c<0 or c>=cols()
		*/
		N at(uint r, uint c) const;

		/** Set element at r, c of the matrix 0-indexed.
			@param r - row of element set
			@param c - column of element set
			@param val - value to set element at r,c
			@throw invalid_argument thrown if r<0 or r>=rows() or c<0 or c>=cols()
		*/
		void set(uint r, uint c, N val);
	
		/** Get the shape or (rows, cols). This is equivalent to `std::make_pair(rows(), cols());`
			@return an STL pair containing the row count and column count 
		*/	
		std::pair<uint, uint> shape() const { return std::make_pair(_rows, _cols); }

		/** Get the number of rows in the matrix.
			@return the number of rows in the matrix
		*/
		uint rows() const { return _rows; }
		
		/**	Get the number of columns in the matrix.
			@return the number of columns in the matrix
		*/
		uint cols() const { return _cols; }

		/** Get the size of the matrix (`size() == rows() * cols()`)
			@return the size of the matrix
		*/
		uint size() const { return _size; }

        
        /** transposes this matrix
        */
        void T();


		// overloaded operators

		/** Copies `m` into `this`. Performs an element-wise copy.
			Ignores self-copy.
			@param m - matrix to copy into `this`
			@return pointer to `this` after copy
		*/
		Matrix& operator=(const Matrix& m);

		/**	Adds matrix `m` to `this` element-wise
			@param m - matrix to add to `this`. rows and cols must be equivalent.
			@return a pointer to `this` after addition
			@throw invalid_argument thrown if `rows()!=m.rows()` or `cols()!=m.cols()`
		*/
		Matrix& operator+=(const Matrix& m);

		/**	Subtracts matrix `m` from `this` element-wise
			@param m - matrix to subtract from `this`. rows and cols must be equivalent.
			@return a pointer to `this` after subtraction
			@throw invalid_argument thrown if `rows()!=m.rows()` or `cols()!=m.cols()`
		*/
		Matrix& operator-=(const Matrix& m);

		/**	Adds Multiplies `this` by scaler `scal`
			@param scal - scaler to multiply `this` by
			@return a pointer to `m` after multiplication
		*/
		Matrix& operator*=(const N& scal);

		/**	Performs matrix multiplication between `this` and `m`. This operation will
			throw an exception if `cols!=m.rows()`. It will also reshape `this` to that
			`rows()` does not change and `cols()` becomes `m.cols()`.
			@param m - matrix to multiply by `this`. 
			@return a pointer to `this` after multiplication.
			@throw invalid_argument if `cols()!=m.rows()` matrix multiplication is undefined
		*/
		Matrix& operator*=(const Matrix& m);

		/**	Divides `this` by scalar `scal` element-wise.
			Does not check for `scal==0` as division for class `N`
			might have non-standard definition.
			@param scal - scalar to divide `this` by
			@return a pointer to `m` after division
		*/
		Matrix& operator/=(const N& scal);
	
	
		// destructor	
		/** Destructor. Deletes the matrix internally */
		~Matrix();
		
	private:
		uint _size;		/**<size of matrix*/
		uint _cols;		/**<number of columns in matrix*/
		uint _rows;		/**<number of rows in matrix*/
		N** _matrix;	/**<internal array to store matrix data*/
};



// free standing operator declarations
/**	Adds lhs and rhs matrices element-wise. Copies lhs and add rhs to it.
	@param lhs - left hand side matrix of addition
	@param rhs - right hand side matrix of addition
	@return a new matrix with elements from element-wise addition of `lhs` and `rhs`
	@throw invalid_argument if `lhs` and `rhs` do not have same shape
*/
template<typename N>
Matrix<N> operator+(Matrix<N> lhs,const Matrix<N>& rhs);

/**	Subtracts lhs and rhs matrices element-wise. Copies lhs and subtract rhs from it.
	@param lhs - left hand side matrix of subtraction
	@param rhs - right hand side matrix of subtraction
	@return a new matrix with elements from element-wise subtraction of `lhs` and `rhs`
	@throw invalid_argument if `lhs` and `rhs` do not have same shape
*/
template<typename N>
Matrix<N> operator-(Matrix<N> lhs, const Matrix<N>& rhs);

/**	Multiplies lhs and scalar rhs. Copies lhs and multiplies by scalar rhs
	@param lhs - left hand side matrix 
	@param rhs - right hand side scalar
	@return a new matrix with elements multiplication of `lhs` and `rhs`
*/
template<typename N>
Matrix<N> operator*(Matrix<N> lhs, const N& rhs);

/**	Multiplies scalar lhs and matrix rhs. Copies rhs and multiplies by scalar lhs
	@param lhs - left hand side scalar 
	@param rhs - right hand side matrix
	@return a new matrix with elements multiplication of `lhs` and `rhs`
*/
template<typename N>
Matrix<N> operator*(const N& lhs, Matrix<N> rhs);

/**	Divides lhs matrix by scalar rhs. Copies lhs and divides by scalar rhs.
	Does not check if rhs is zero due to unknown type of `N`.
	@param lhs - left hand side matrix 
	@param rhs - right hand side scalar
	@return a new matrix with elements division of `lhs` and `rhs`
*/
template<typename N>
Matrix<N> operator/(Matrix<N> lhs, const N& rhs);

/**	Performs matrix multiplication of `rhs` and `lhs`
	@param lhs - left hand side matrix
	@param rhs - right hand side matrix
	@return a new matrix resulting from matrix multiplication. Result will have shape `lhs.rows()`, `rhs.cols()`.
	@throw invalid_argument if `lhs.cols() != rhs.rows()`
*/
template<typename N>
Matrix<N> operator*(Matrix<N> lhs, const Matrix<N>& rhs);


// define standard Matrix classes for easier use
/** integer matrix */
typedef Matrix<int> iMatrix;
/** float precision matrix */
typedef Matrix<float> fMatrix;
/** double precision matrix */
typedef Matrix<double> dMatrix;



// implementation


template<typename N>
Matrix<N>::Matrix(uint size, const N& fill) : Matrix(size, size, fill) {}


/*
	initilize with dimensions rows*cols and elements fill
*/
template<typename N>
Matrix<N>::Matrix(uint rows, uint cols, const N& fill) : _size(rows*cols), _cols(cols), _rows(rows) {
	// allocate rows
	_matrix = new N*[_rows];

	// allocate col in each row
	for (uint r = 0; r < _rows; ++r) {
		_matrix[r] = new N[_cols];

		// set each value to fill
		for (uint c = 0; c < _cols; ++c)
			_matrix[r][c] = fill;
	}
}

template<typename N>
Matrix<N>::Matrix(uint size, N** data) : Matrix(size, size, data) {}

template<typename N>
Matrix<N>::Matrix(uint rows, uint cols, N** data) : _size(rows*cols), _cols(cols), _rows(rows) {
	// allocate rows
	_matrix = new N*[_rows];

	for (uint r = 0; r < _rows; ++r) {
		// allocate columns
		_matrix[r] = new N[_cols];

		for (uint c = 0; c < _cols; ++c)
			_matrix[r][c] = data[r][c];
	}	
}

template<typename N>
Matrix<N>::Matrix(uint size, const std::vector<std::vector<N> >& data) : Matrix(size, size, data) {}

template<typename N>
Matrix<N>::Matrix(uint rows, uint cols, const std::vector<std::vector<N> >& data) : _size(rows*cols), _cols(cols), _rows(rows) {
	// allocate rows
	_matrix = new N*[_rows];

	for (uint r = 0; r < _rows; ++r) {
		// allocate columns	
		_matrix[r] = new N[_cols];

		for (uint c = 0; c < _cols; ++c)
			_matrix[r][c] = data[r][c];
	}
}


// copy constructor
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
N Matrix<N>::at(uint r, uint c) const {
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
void Matrix<N>::T() {
    if (_rows == 0 || _cols == 0) return;

    Matrix t (_cols, _rows, 0);
    for (uint r = 0; r < _rows; r++)
        for (uint c = 0; c < _cols; c++)
            t._matrix[c][r] = _matrix[r][c];
    *this = t;
}


////////////////////
// 			operator overload implementations
////////////////////

template<typename N>
Matrix<N>& Matrix<N>::operator=(const Matrix& m) {
	if (this != &m) {	// ignore self-assignment
		if (_rows != m._rows || _cols != m._cols) {		// cannot reuse memory
	
			// delete current memory
			for (int r = 0; r < _rows; ++r) delete[] _matrix[r];
			delete[] _matrix;

			// create new memory and reinit property vars
			_size = 0;
			_rows = 0;
			_cols = 0;			

			_matrix = new N*[m._rows];
			for (int r = 0; r < m._rows; ++r) _matrix[r] = new N[m._cols];
			
			_size = m._size;
			_rows = m._rows;
			_cols = m._cols;	
		} 
		for (int r = 0; r < _rows; ++r)
			for (int c = 0; c < _cols; ++c)
				_matrix[r][c] = m._matrix[r][c];
	}
	return *this;
}

template<typename N>
Matrix<N>& Matrix<N>::operator+=(const Matrix& m) {
	// error if they don't have same shape
	if (m._rows != _rows || m._cols != _cols) 
		throw std::invalid_argument("arrays must have same size");

	// add each element
	for (int r = 0; r < _rows; ++r)
		for (int c = 0; c < _cols; ++c)
			_matrix[r][c] += m._matrix[r][c];

	return *this;
}

template<typename N>
Matrix<N> operator+(Matrix<N> lhs, const Matrix<N>& rhs) {
	// lhs is copy of argument, so we can use +=
	lhs += rhs;
	return lhs;
}


template<typename N>
Matrix<N>& Matrix<N>::operator-=(const Matrix& m) {
	// error if they don't have same shape
	if (m._rows != _rows || m._cols != _cols)
		throw std::invalid_argument("arrays must have same size");
	
	// subtract every element from *this
	for (int r = 0; r < _rows; ++r) 
		for (int c = 0; c < _cols; ++c)
			_matrix[r][c] -= m._matrix[r][c];

	return *this;
}

template<typename N>
Matrix<N> operator-(Matrix<N> lhs, const Matrix<N>& rhs) {
	// lhs is a copy, so use -=
	lhs -= rhs;
	return lhs;
}


template<typename N>
Matrix<N>& Matrix<N>::operator*=(const N& scal) {
	// multiply each element by scalar
	for (int r = 0; r < _rows; ++r)
		for (int c = 0; c < _cols; ++c)
			_matrix[r][c] *= scal;
	return *this;	
}

template<typename N>
Matrix<N> operator*(Matrix<N> lhs, const N& scal) {
	// lhs is a copy
	lhs *= scal;
	return lhs;
}

// define mult. for left->right since its commutative
template<typename N>
Matrix<N> operator*(const N& scal, Matrix<N> rhs) {
	return rhs * scal;
}


template<typename N>
Matrix<N>& Matrix<N>::operator*=(const Matrix& m) {
	if (_cols != m._rows)
		throw std::invalid_argument("Matrix Multiplication is undefined if m.rows() must equal cols().");

	Matrix<N> result (_rows, m._cols);
	
	N sum;
	for (int r = 0; r < _rows; ++r) {
		for (int c = 0; c < m._cols; ++c) {
			sum = N();
			for (int i = 0; i < _cols; ++i)
				sum += _matrix[r][i] * m._matrix[i][c];

			result._matrix[r][c] = sum;
		}
	}
	(*this) = result;
	return *this;			
}


template<typename N>
Matrix<N> operator*(Matrix<N> lhs, const Matrix<N>& rhs) {
	lhs *= rhs;
	return rhs;
}


template<typename N>
Matrix<N>& Matrix<N>::operator/=(const N& scal) {
	// divide each element by scal
	for (int r = 0; r < _rows; ++r) 
		for (int c = 0; c < _cols; ++c)
			_matrix[r][c] /= scal;

	return *this;
}

template<typename N>
Matrix<N> operator/(Matrix<N> lhs, const N& rhs) {
	lhs /= rhs;
	return lhs;
}


template<typename N>
Matrix<N>::~Matrix() {
	for (uint r = 0; r < _rows; ++r) {
		delete[] _matrix[r];
	}
	delete[] _matrix;
}

}	// math

#endif
