#include <iostream>
#include <fstream>
#include <memory>
#include "Matrix.h"
#include "Timer.h"

#define ID1 1
#define ID2 7
#define ID3 5
#define ID4 7
#define ID5 9
#define ID6 3

struct Result {
	int iterations = 0;
	containerType norm = 0;
	Time time;
};
struct CreateData {
	int N = 0;
	containerType a1 = 0;
	containerType a2 = 0;
	containerType a3 = 0;
};

MatrixPtr Create_A(int size, containerType a1, containerType a2, containerType a3);
MatrixPtr Create_b(int size);
MatrixPtr Create_x(int size);
void PrepareMatrixes(CreateData data, MatrixPtr& A, MatrixPtr& b, MatrixPtr& x);

MatrixPtr CalculateResiduum(MatrixPtr A, MatrixPtr B, MatrixPtr X);
containerType CalculateNorm(MatrixPtr residuum);
containerType CalculateNormOfResiduum(MatrixPtr A, MatrixPtr B, MatrixPtr X);

Result Jacobiego(MatrixPtr A, MatrixPtr B, MatrixPtr X, const double NORM);
Result GaussaSeidla(MatrixPtr A, MatrixPtr B, MatrixPtr X, const double NORM);
Result LU(MatrixPtr A, MatrixPtr B, MatrixPtr X);

void PrintTime(Time time);
void PrintIterations(int iterations);
void PrintNorm(containerType norm);
void PrintResult(Result result);
void PrintMethod(std::string title, CreateData data);

void ZadanieB();
void ZadanieC();
void ZadanieD();
void ZadanieE(std::string filename);

int main()
{
	ZadanieB();
	//ZadanieC();
	ZadanieD();
	ZadanieE("results.csv");
}

MatrixPtr Create_A(int size, containerType a1, containerType a2, containerType a3) {
	auto result = std::make_shared<Matrix>(size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j) {
				(*result)[i][j] = a1;
			}
			else if (i + 1 == j || i - 1 == j) {
				(*result)[i][j] = a2;
			}
			else if (i + 2 == j || i - 2 == j) {
				(*result)[i][j] = a3;
			}
			else {
				(*result)[i][j] = 0;
			}
		}
	}
	return result;
}
MatrixPtr Create_b(int size) {
	auto result = std::make_shared<Matrix>(1, size);

	for (int n = 0; n < size; n++)
	{
		(*result)[0][n] = sin(n * (ID3 + 1));
	}
	return result;
}
MatrixPtr Create_x(int size) {
	auto result = std::make_shared<Matrix>(1, size);
	result->Fill(1);
	return result;
}
void PrepareMatrixes(CreateData data, MatrixPtr& A, MatrixPtr& b, MatrixPtr& x) {
	A = Create_A(data.N, data.a1, data.a2, data.a3);
	b = Create_b(data.N);
	x = Create_x(data.N);
}

MatrixPtr CalculateResiduum(MatrixPtr A, MatrixPtr B, MatrixPtr X) {
	auto result = (*A) * (*X);
	result = (*result) - (*B);
	return result;
}
containerType CalculateNorm(MatrixPtr residuum) {
	containerType result = 0;
	for (int i = 0; i < residuum->GetSize().y; i++)
	{
		result += pow((*residuum)[0][i], 2);
	}
	return sqrt(result);
}
containerType CalculateNormOfResiduum(MatrixPtr A, MatrixPtr B, MatrixPtr X) {
	auto residuum = CalculateResiduum(A, B, X);
	return CalculateNorm(residuum);
}

Result Jacobiego(MatrixPtr A, MatrixPtr B, MatrixPtr X, const double NORM) {
	Timer timer;
	timer.Start();

	Result result;

	auto lastX = std::make_shared<Matrix>(X->GetSize());
	lastX->Fill(1);

	do
	{
		for (int y = 0; y < X->GetSize().y; y++)
		{
			(*X)[0][y] = (*B)[0][y];
			for (int x = 0; x < A->GetSize().x; x++)
			{
				if (x == y) {
					continue;
				}
				(*X)[0][y] -= (*A)[x][y] * (*lastX)[0][x];
			}
			(*X)[0][y] /= (*A)[y][y];
		}
		lastX = X->GetCopy();
		result.iterations++;

		result.norm = CalculateNormOfResiduum(A, B, X);
	} while (result.norm > NORM);

	timer.Stop();
	result.time = timer.GetTime();
	return result;
}
Result GaussaSeidla(MatrixPtr A, MatrixPtr B, MatrixPtr X, const double NORM) {
	Timer timer;
	timer.Start();

	Result result;

	auto lastX = std::make_shared<Matrix>(X->GetSize());
	lastX->Fill(1);

	do
	{
		for (int i = 0; i < X->GetSize().y; i++)
		{
			(*X)[0][i] = (*B)[0][i];
			for (int j = 0; j < A->GetSize().x; j++)
			{
				if (j < i) {
					(*X)[0][i] -= (*A)[i][j] * (*X)[0][j];
				}
				else if (j > i) {
					(*X)[0][i] -= (*A)[i][j] * (*lastX)[0][j];
				}
			}
			(*X)[0][i] /= (*A)[i][i];
		}
		lastX = X->GetCopy();
		result.iterations++;

		result.norm = CalculateNormOfResiduum(A, B, X);
	} while (result.norm > NORM);

	timer.Stop();
	result.time = timer.GetTime();

	return result;
}
Result LU(MatrixPtr A, MatrixPtr B, MatrixPtr X) {
	Timer timer;
	timer.Start();

	Result result;

	auto size = A->GetSize().x;

	//PrepareMatrixes U & L Matrixes
	auto U = A->GetCopy();
	auto L = std::make_shared<Matrix>(A->GetSize());
	L->Fill(0);
	L->SetDiagonal(1);

	for (int k = 0; k < size - 1; k++)
	{
		for (int j = k + 1; j < size; j++)
		{
			(*L)[j][k] = (*U)[j][k] / (*U)[k][k];

			for (int i = k; i < size; i++)
			{
				(*U)[j][i] = (*U)[j][i] - (*L)[j][k] * (*U)[k][i];
			}
		}
	}
	auto Y = std::make_shared<Matrix>(1, size);

	//L * y = b
	for (int i = 0; i < size; i++)
	{
		(*Y)[0][i] = (*B)[0][i];

		for (int j = 0; j < i; ++j)
			(*Y)[0][i] -= (*L)[i][j] * (*Y)[0][j];

		(*Y)[0][i] = (*Y)[0][i] / (*L)[i][i];
	}
	//U * x = y
	for (int i = size - 1; i >= 0; --i)
	{
		(*X)[0][i] = (*Y)[0][i];
		for (int j = i + 1; j < size; ++j)
			(*X)[0][i] -= (*U)[i][j] * (*X)[0][j];

		(*X)[0][i] = (*X)[0][i] / (*U)[i][i];
	}

	result.norm = CalculateNormOfResiduum(A, B, X);

	timer.Stop();
	result.time = timer.GetTime();
	result.iterations = 1;

	return result;
}

void PrintTime(Time time) {
	printf("\t\ttime: %dmin %dsec %dms\n\n", time.min, time.sec, time.ms);
}
void PrintIterations(int iterations) {
	printf("\t\titerations: %d\n", iterations);
}
void PrintNorm(containerType norm) {
	printf("\t\tnorm of residuum: %e\n", norm);
}
void PrintResult(Result result) {
	PrintIterations(result.iterations);
	PrintNorm(result.norm);
	PrintTime(result.time);
}
void PrintMethod(std::string title, CreateData data) {
	printf("\t%s Method (N=%d, a1=%d, a2=%d, a3=%d)\n", title.c_str(), data.N, (int)data.a1, (int)data.a2, (int)data.a3);
}

void ZadanieB() {
	printf("Zadanie B\n");

	MatrixPtr A, b, x;
	CreateData data;
	Result result;

	data.N = 9 * 100 + ID5 * 10 + ID6;
	data.a1 = 5 + ID4;
	data.a2 = -1;
	data.a3 = -1;

	PrintMethod("Jacobi", data);
	PrepareMatrixes(data, A, b, x);
	result = Jacobiego(A, b, x, 1e-9);
	PrintResult(result);

	PrintMethod("Gauss-Seidl", data);
	PrepareMatrixes(data, A, b, x);
	result = GaussaSeidla(A, b, x, 1e-9);
	PrintResult(result);
}
void ZadanieC() {
	printf("Zadanie C\n");

	MatrixPtr A, b, x;
	CreateData data;
	Result result;

	data.N = 9 * 100 + ID5 * 10 + ID6;
	data.a1 = 3;
	data.a2 = -1;
	data.a3 = -1;

	PrintMethod("Jacobi", data);
	PrepareMatrixes(data, A, b, x);
	result = Jacobiego(A, b, x, 1e-9);
	PrintResult(result);

	PrintMethod("Gauss-Seidl", data);
	PrepareMatrixes(data, A, b, x);
	result = GaussaSeidla(A, b, x, 1e-9);
	PrintResult(result);
}
void ZadanieD() {
	printf("Zadanie D\n");

	MatrixPtr A, b, x;
	CreateData data;
	Result result;

	data.N = 9 * 100 + ID5 * 10 + ID6;
	data.a1 = 3;
	data.a2 = -1;
	data.a3 = -1;

	PrintMethod("LU", data);
	PrepareMatrixes(data, A, b, x);
	result = LU(A, b, x);
	PrintResult(result);
}
void ZadanieE(std::string filename) {
	printf("Zadanie E\n");

	std::ofstream outputFile(filename.c_str());

	MatrixPtr A, b, x;
	CreateData data;
	Result result;

	data.a1 = 5 + ID4;
	data.a2 = -1;
	data.a3 = -1;

	data.N = 9 * 100 + ID5 * 10 + ID6;
	int N[] = { 100, 500, 1000, 2000, 3000 };

	outputFile << "N,Jacobi,GaussSeidl,LU\n";
	for (int i = 0; i < sizeof N / sizeof N[0]; i++)
	{
		data.N = N[i];
		outputFile << data.N << ",";
		PrintMethod("Jacobi", data);
		PrepareMatrixes(data, A, b, x);
		result = Jacobiego(A, b, x, 1e-9);
		outputFile << result.time.min << ":" << result.time.sec << ":" << result.time.ms << ",";
		PrintResult(result);

		PrintMethod("Gauss-Seidl", data);
		PrepareMatrixes(data, A, b, x);
		result = GaussaSeidla(A, b, x, 1e-9);
		outputFile << result.time.min << ":" << result.time.sec << ":" << result.time.ms << ",";
		PrintResult(result);

		PrintMethod("LU", data);
		PrepareMatrixes(data, A, b, x);
		result = LU(A, b, x);
		outputFile << result.time.min << ":" << result.time.sec << ":" << result.time.ms << "\n";
		PrintResult(result);
	}
	outputFile.close();
}
