#include <iostream>

int* container;
int n = 0;
int m = 0;

void printC(int currentDepth = 0);
void printArray();

int main(){

    std::cout << "podaj n: ";
    std::cin >> n;

    std::cout << "podaj m: ";
    std::cin >> m;

    container = new int[m];
    for (int i = 0; i < m; i++) {
        container[i] = 0;
    }
    printC();
}

void printC(int currentDepth){
    if (currentDepth == m) {
        printArray();
        return;
    }

    for (int i = (currentDepth == 0) ? 1 : container[currentDepth - 1] + 1; i <= n; i++) {
        container[currentDepth] = i;
        if (currentDepth < m) {
            printC(currentDepth + 1);
        }
    }
    
}

void printArray() {
    for (int j = 0; j < m; j++) {
        std::cout << container[j];
    }
    std::cout << std::endl;
}