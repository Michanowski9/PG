#include <iostream>

#define SIZE_X 4
#define SIZE_Y 4
#define N 100000

double p[SIZE_X][SIZE_Y] = {
    {0.1,   0,      0.1,    0.2},     //p[0][x]
    {0,     0.05,   0.05,   0},
    {0,     0.05,   0.05,   0},
    {0.2,   0.1,    0,      0.1}
};
double py[SIZE_Y] = {};
double px[SIZE_X][SIZE_Y] = {};

double result[SIZE_X][SIZE_Y] = {};

void makePxPy() {
    for (int i = 0; i < SIZE_X; i++)
    {
        for (int j = 0; j < SIZE_Y; j++)
        {
            py[i] += p[i][j];
        }
    }

    for (int i = 0; i < SIZE_X; i++)
    {
        for (int j = 0; j < SIZE_Y; j++)
        {
            px[i][j] = p[i][j] / py[i];
        }
    }
}
void writePPxPy() {

    for (int x = 0; x < SIZE_X; x++)
    {
        for (int y = 0; y < SIZE_Y; y++)
        {
            std::cout << p[x][y] << "\t\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int x = 0; x < SIZE_X; x++)
    {
        std::cout << py[x] << "\n";
    }

    std::cout << std::endl;

    for (int x = 0; x < SIZE_X; x++)
    {
        for (int y = 0; y < SIZE_Y; y++)
        {
            std::cout << px[x][y] << "\t\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int x = 0; x < SIZE_X; x++)
    {
        for (int y = 0; y < SIZE_Y; y++)
        {
            std::cout << result[x][y] << "\t\t";
        }
        std::cout << std::endl;
    }
}

double random(int* v, double* p, int size) {
    double random = (double)rand() / RAND_MAX;
    double currentP = 0;
    for (int i = 0; i < size; i++) {
        currentP += p[i];
        if (random <= currentP) {
            return v[i];
        }
    }
}

int main()
{
    makePxPy();
    int values[] = { 1, 2, 3, 4 };
    for (int i = 0; i < N; i++)
    {
        auto randX = random(values, py, sizeof values / sizeof values[0]);
        int indexX = randX - 1;
        auto randY = random(values, px[indexX], sizeof values / sizeof values[0]);
        int indexY = randY - 1;
        result[indexX][indexY]++;
    }
    writePPxPy();
}