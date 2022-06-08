#include "Matrix.h"

Matrix::Matrix(int size_x, int size_y) : size(size_x, size_y)
{
	allocateMemory();
}

Matrix::Matrix(Point size) : size(size)
{
	allocateMemory();
}

Matrix::Matrix(int size) : size(size, size)
{
	allocateMemory();
}

Matrix::~Matrix()
{
	for (int x = 0; x < size.x; x++)
	{
		delete container[x];
	}
	delete container;
}

Point Matrix::GetSize() const
{
	return size;
}

MatrixPtr Matrix::GetCopy()
{
	auto result = std::make_shared<Matrix>(size);
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			(*result)[i][j] = container[i][j];
		}
	}
	return result;
}

void Matrix::Fill(containerType value)
{
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			container[x][y] = value;
		}
	}
}

void Matrix::SetDiagonal(containerType value) {
	for (int i = 0; i < size.x; i++)
	{
		container[i][i] = value;
	}
}

containerType*& Matrix::operator[](int index)
{
	return container[index];
}

void Matrix::allocateMemory()
{
	container = new containerType * [size.x];
	for (int i = 0; i < size.x; i++)
	{
		container[i] = new containerType[size.y];
	}
}


MatrixPtr operator*(Matrix& left, Matrix& right)
{
	auto result = std::make_shared<Matrix>(right.GetSize().x, left.GetSize().y);
	for (int x = 0; x < result->GetSize().x; x++)
	{
		for (int y = 0; y < result->GetSize().y; y++)
		{
			(*result)[x][y] = 0;
			for (int i = 0; i < left.GetSize().x; i++)
			{
				(*result)[x][y] += left[i][y] * right[x][i];
			}
		}
	}
	return result;
}

MatrixPtr operator-(Matrix& left, Matrix& right)
{
	auto result = std::make_shared<Matrix>(left.GetSize());

	for (int x = 0; x < result->GetSize().x; x++)
	{
		for (int y = 0; y < result->GetSize().y; y++)
		{
			(*result)[x][y] = left[x][y] - right[x][y];
		}
	}
	return result;
}