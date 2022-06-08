#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <memory>

struct Point {
	Point(int x, int y) : x(x), y(y) {};
	int x;
	int y;
};

typedef double containerType;

class Matrix
{
public:
	Matrix(int size_x, int size_y);
	Matrix(Point size);
	Matrix(int size);
	~Matrix();

	Point GetSize() const;
	std::shared_ptr<Matrix> GetCopy(); 
	void Fill(containerType value);
	void SetDiagonal(containerType value);

	containerType*& operator[](int index);
private:
	void allocateMemory();

	containerType** container;
	Point size;
};

using MatrixPtr = std::shared_ptr<Matrix>;

MatrixPtr operator*(Matrix& left, Matrix& right);
MatrixPtr operator-(Matrix& left, Matrix& right);

#endif // !_MATRIX_H_