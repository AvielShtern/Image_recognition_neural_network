#include "Matrix.h"

using std::cout;
using std::endl;
using std::cerr;

/**
 * initial value of matrix is 0
 */
#define INITIAL_VALUE 0

/**
 * valid num of rows in ctor is from 0
 */
#define VALID_NUM_ROWS 0

/**
 * valid num of cols in ctor is from 0
 */
#define VALID_NUM_COLS 0

/**
 * in defauld ctor num of rows is 1
 */
#define DEFAULT_NUM_ROWS 1

/**
 * in defauld ctor num of cols is 1
 */
#define DEFAULT_NUM_COLS 1

/**
 * in vectorised num of rows is 1
 */
#define VEC_NUM_ROWS 1

/**
 * idx less from 0 is invalid
 */
#define VALID_IDX 0

/**
 * when we print the matrix we use it
 */
#define DOUBLE_ASTERISK  "**"

/**
 * when we print the matrix we use it
 */
#define DOUBLE_SPACE  "  "

/**
 * say that was error in ctor
 */
#define TYPE_ERROR_CTOR 1

/**
 * msg in case was error in ctor
 */
#define MSG_ERROR_CTOR "Error: invalid num of rows or num of cols (Negative numbers)"

/**
 * say that was error in opertor *
 */
#define TYPE_ERROR_MATRIX_MUL 2

/**
 * msg in case was error in opertor *
 */
#define MSG_ERROR_MATRIX_MUL "Error: num of cols of lhs different from the num of rows in rhs"

/**
 * say that error invalid idx
 */
#define TYPE_ERROR_IDX 3

/**
 * msg in case error invalid idx
 */
#define MSG_ERROR_IDX "Error: the index not in matrix"

/**
 * say that was error in opertor +
 */
#define TYPE_ERROR_MATRIX_ADD 4

/**
 * msg in case was error in opertor +
 */
#define MSG_ERROR_MATRIX_ADD "Error: num of rows and cols Must be equal in two matrix's"

/**
 * say that was error in input file
 */
#define TYPE_ERROR_INPUT_FILE 5

/**
 * msg in case was error in input file
 */
#define MSG_ERROR_INPUT_FILE "Error: there is a problem in input file"

/**
 *
 */
float const GRAY_PIXEL_MIN = 0.1f;


/**
 * constructor of matrix, create new matrix size row*col, allocate float array and initializes
 * values with 0
 * @param row num of row (int)
 * @param col num of col (int)
 */
Matrix::Matrix(const int &row, const int &col)
{
	if (row <= VALID_NUM_ROWS || col <= VALID_NUM_COLS)
	{
		_errorCase(TYPE_ERROR_CTOR);
	}
	_rows = row;
	_cols = col;
	_mat = new float[row * col];
	for (int i = 0; i < row * col; i++)
	{
		_mat[i] = INITIAL_VALUE;
	}

}

/**
 * default constructor of matrix, create new matrix size 1*1, allocate float array and initializes
 * values with 0
 */
Matrix::Matrix() : Matrix(DEFAULT_NUM_ROWS, DEFAULT_NUM_COLS)
{}

/**
 * copy constructor of matrix
 * @param rsh matrix in right hand side
 */
Matrix::Matrix(const Matrix &rsh) : Matrix(rsh._rows, rsh._cols)
{
	for (int i = 0; i < _rows * _cols; i++)
	{
		_mat[i] = rsh._mat[i];
	}
}

/**
 * dtor of matrix
 */
Matrix::~Matrix()
{
	delete[] _mat;
}

/**
 * get the num of rows
 */
int Matrix::getRows() const
{
	return _rows;
}

/**
 * get the num of cols
 */
int Matrix::getCols() const
{
	return _cols;
}

/**
 * we change the matrix into a vector
 * @return referns to vector
 */
Matrix &Matrix::vectorize()
{
	_rows = _rows * _cols;
	_cols = VEC_NUM_ROWS;
	return *this;
}

/**
 *we printed the matrix
 */
void Matrix::plainPrint() const
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			cout << _mat[i * _cols + j] << " ";
		}
		cout << endl;
	}
}

/**
 * opertor =
 * @param rsh
 * @return referns to matrix
 */
Matrix &Matrix::operator=(const Matrix &rsh)
{
	if (this == &rsh)
	{
		return *this;
	}
	delete[] _mat;
	_rows = rsh._rows;
	_cols = rsh._cols;
	_mat = new float[_rows * _cols];
	for (int i = 0; i < _rows * _cols; i++)
	{
		_mat[i] = rsh._mat[i];
	}
	return *this;
}

/**
 * operator * (2 matrix)
 * @param rsh
 * @return
 */
Matrix
Matrix::operator*(const Matrix &rsh) const // we assume that _cols and rsh._rows is equal!!!!!
// A*B
{
	if (_cols != rsh._rows)
	{
		_errorCase(TYPE_ERROR_MATRIX_MUL);
	}
	int newCol = rsh._cols;
	int newRow = _rows;
	Matrix newMat = Matrix(newRow, newCol);
	for (int i = 0; i < newRow; i++)
	{
		for (int j = 0; j < newCol; j++)
		{
			float sum = 0;
			for (int k = 0; k < _cols; k++)
			{
				sum += ((*this)(i, k)) * (rsh(k, j));
			}
			newMat(i, j) = sum;
		}
	}
	return newMat;
}

/**
 *get the value un place (i , j)
 */
float &Matrix::operator()(const int &i, const int &j)
{
	if (i >= _rows || i < 0 || j >= _cols || j < VALID_IDX)
	{
		_errorCase(TYPE_ERROR_IDX);
	}
	return _mat[i * _cols + j];
}

/**
 * operator * (matrix and scalar from right)
 */
Matrix Matrix::operator*(const float &scalar) const // M*c
{
	Matrix newMat(*this);
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			newMat(i, j) *= scalar;
		}
	}

	return newMat;
}

/**
 * operator * (matrix and scalar from left)
 */
Matrix operator*(const float &scalar, const Matrix &rsh) // c*M
{
	Matrix newMat(rsh);

	for (int i = 0; i < rsh._rows; i++)
	{
		for (int j = 0; j < rsh._cols; j++)
		{
			newMat(i, j) *= scalar;
		}
	}

	return newMat;
}

/**
 * the operator +
 */
Matrix Matrix::operator+(const Matrix &rsh) const
{
	if (_rows != rsh._rows || _cols != rsh._cols)
	{
		_errorCase(TYPE_ERROR_IDX);
	}
	Matrix newMat = Matrix(*this);
	for (int i = 0; i < _rows * _cols; i++)
	{
		newMat._mat[i] += rsh._mat[i];
	}
	return newMat;
}

/**
 * the operator +=
 */
Matrix &Matrix::operator+=(const Matrix &rsh)
{
	if (_rows != rsh._rows || _cols != rsh._cols)
	{
		_errorCase(TYPE_ERROR_MATRIX_ADD);
	}
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			(*this)(i, j) += rsh(i, j);
		}

	}
	return *this;
}

/**
 *get the value un place [i]
 */
float &Matrix::operator[](const int &i)
{
	if (i >= _rows * _cols || i < VALID_IDX)
	{
		_errorCase(TYPE_ERROR_MATRIX_ADD);
	}
	return _mat[i];
}

/**
 *get the value un place (i , j)
 */
float Matrix::operator()(const int &i, const int &j) const
{
	if (i >= _rows || i < VALID_IDX || j >= _cols || j < VALID_IDX)
	{
		_errorCase(TYPE_ERROR_IDX);
	}
	return _mat[i * _cols + j];
}

/**
 *get the value un place [i]
 */
float Matrix::operator[](const int &i) const
{
	if (i >= _rows * _cols || i < VALID_IDX)
	{
		_errorCase(TYPE_ERROR_IDX);
	}
	return _mat[i];
}

/**
 * print the num im img
 */
std::ostream &operator<<(std::ostream &out, const Matrix &matrix)
{
	for (int i = 0; i < matrix.getRows(); i++)
	{
		for (int j = 0; j < matrix.getCols(); j++)
		{
			if (matrix(i, j) <= GRAY_PIXEL_MIN)
			{
				out << DOUBLE_SPACE;
			}
			else
			{
				out << DOUBLE_ASTERISK;
			}
		}
		out << endl;
	}
	return out;
}

/**
 *read from file into a matrix
 */
std::istream &operator>>(std::istream &iStream, Matrix &matrix)
{
	if (!iStream)
	{
		Matrix::_errorCase(TYPE_ERROR_INPUT_FILE);
	}
	iStream.read((char *) matrix._mat, matrix._rows * matrix._cols * sizeof(float));
	return iStream;
}

/**
 *in  case of error we print msg according the error type and get out from the progrem
 * @param typeError
 */
void Matrix::_errorCase(const int &typeError)
{
	if (typeError == TYPE_ERROR_CTOR)
	{
		cerr << MSG_ERROR_CTOR << endl;
		exit(EXIT_FAILURE);
	}
	else if (typeError == TYPE_ERROR_MATRIX_MUL)
	{
		cerr << MSG_ERROR_MATRIX_MUL << endl;
		exit(EXIT_FAILURE);
	}
	else if (typeError == TYPE_ERROR_MATRIX_ADD)
	{
		cerr << MSG_ERROR_MATRIX_ADD << endl;
		exit(EXIT_FAILURE);
	}
	else if (typeError == TYPE_ERROR_IDX)
	{
		cerr << MSG_ERROR_IDX << endl;
		exit(EXIT_FAILURE);
	}
	else if (typeError == TYPE_ERROR_INPUT_FILE)
	{
		cerr << MSG_ERROR_INPUT_FILE << endl;
		exit(EXIT_FAILURE);
	}

}










