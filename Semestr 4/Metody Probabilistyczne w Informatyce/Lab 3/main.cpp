#include <iostream>

#define ARRAY_SIZE 10
#define N 100000

double randomZad1(int* v, double* p, int size) {
    double random = (double)rand() / RAND_MAX;
    double currentP = 0;
    for (int i = 0; i < size; i++) {
        currentP += p[i];
        if (random <= currentP) {
            return v[i];
        }
    }
}

double randomZad2() {
    double random = (double)rand() / RAND_MAX;
    return random * 100 + 50;
}

void zadanie1() {
    //creating empty array (filled by zeros)
    int result[4] = {};

    int values[] = { 1, 2, 3, 4 };
    double probabilities[] = { 0.2, 0.4, 0.15, 0.25 };

    //drawing numbers
    for (int i = 0; i < N; i++) {
        auto randValue = randomZad1(values, probabilities, sizeof values / sizeof values[0]);
        int index = randValue - 1;
        result[index]++;
    }

    //printing array
    for (int i = 0; i < sizeof values / sizeof values[0]; i++) {
        std::cout << result[i] << std::endl;
    }
}

void zadanie2() {
    //creating empty array (filled by zeros)
    int result[ARRAY_SIZE] = {};

    //drawing numbers
    for (int i = 0; i < N; i++) {
        auto randValue = randomZad2();
        auto temp = 150.0;
        for (int index = ARRAY_SIZE - 1; index >= 0; index--) {
            temp -= 10.0;
            if (randValue > temp) {
                result[index]++;
                break;
            }
        }
    }

    //printing array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        std::cout << result[i] << std::endl;
    }
}

int main()
{
    srand(time(NULL));
    
    std::cout << "\nZadanie 1:" << std::endl;
    zadanie1();


    std::cout << "\n\nZadanie 2:" << std::endl;
    zadanie2();
}
