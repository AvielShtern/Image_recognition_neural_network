// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
	int rows, cols;
} MatrixDims;

/**
* @class Matrix
* @brief the class of all matrix's in this program
*/
class Matrix
{
private:
	int _rows;
	int _cols;
	float *_mat{};

	static void _errorCase(const int &typeError);

public:

	/**
 	* constructor of matrix, create new matrix size row*col, allocate float array and initializes
 	* values with 0
 	* @param row num of row (int)
 	* @param col num of col (int)
 	*/
	Matrix(const int &row, const int &col);

    /**
    * default constructor of matrix, create new matrix size 1*1, allocate float array and
    * initializes
    * values with 0
    */
	Matrix();

    /**
    * copy constructor of matrix
    * @param rsh matrix in right hand side
    */
	Matrix(const Matrix &rsh);

	/**
	 * dtor
	 */
	~Matrix();

	/**
	 * @return returns the amount of rows as int
	 */
	int getRows() const;

	/**
	 * @return returns the amount of cols as int
	 */
	int getCols() const;

	/**
     * Transforms a matrix into a coloumn vector .Supports function calling concatenation
	 * @return the original Matrix
	 */
	Matrix &vectorize();

	/**
	 * Prints matrix elements, no return value.
     * Prints space after each element (incl. last element in the row)
     * prints newline after each row (incl. last row)
	 */
	void plainPrint() const;

	/**
	 * Assignment
	 * @param rsh The matrix to which we want to be equal
	 * @return the original Matrix
	 */
	Matrix &operator=(const Matrix &rsh);

	/**
	 * Matrix multiplication
	 * @param rsh
	 * @return new Matrix (the result of multiplication)
	 */
	Matrix operator*(const Matrix &rsh) const;

	/**
	 * Scalar multiplication on the right
	 * @param scalar
	 * @return new Matrix (the result of multiplication)
	 */
	Matrix operator*(const float &scalar) const;

	/**
	 * Scalar multiplication on the left
	 * @param scalar
	 * @param rsh The matrix we want to multiply in the scalar
	 * @return new Matrix (the result of multiplication)
	 */
	friend Matrix operator*(const float &scalar, const Matrix &rsh);

	/**
	 * Matrix addition
	 * @param rsh The matrix we want to add
	 * @return new Matrix (the result of addition)
	 */
	Matrix operator+(const Matrix &rsh) const;

	/**
	 * Matrix addition accumulation
	 * @param rsh The matrix we want to add
	 * @return the original Matrix after the addition
	 */
	Matrix &operator+=(const Matrix &rsh);

	/**
	 * Brackets indexing
	 * M(i,j) == M[i·rowSize+j]
	 * @param i index
	 * @return M[i] that can change (!)
	 */
	float &operator[](const int &i);

	/**
	 * Parenthesis indexing
	 * @param i,j indices
	 * @return return the i,j element in the matrix that can change (!)
	 */
	float &operator()(const int &i, const int &j);

	/**
	 * Brackets indexing
	 * M(i,j) == M[i·rowSize+j]
	 * @param i index
	 * @return M[i]
	 */
	float operator[](const int &i) const;

    /**
     * Parenthesis indexing
     * @param i,j indices
     * @return return the i,j element in the matrix
     */
	float operator()(const int &i, const int &j) const;

	/**
	 * Pretty export of matrix
	 * @param out the output stream
	 * @param matrix the matrix we want to output
	 * @return the output stream (supports concatenation)
	 */
	friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);

	/**
	 * Fills matrix elements. has to read input stream fully,
     * otherwise, that’s an error
	 * @param iStream the input stream
	 * @param matrix the matrix we want to fill
	 * @return the input stream (supports concatenation)
	 */
	friend std::istream &operator>>(std::istream &iStream, Matrix &matrix);

};

#endif //MATRIX_H
