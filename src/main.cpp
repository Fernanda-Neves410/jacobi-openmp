#include "jacobi.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() {
    double epsilon = 1e-6;
    int num_threads = 2;
    int max_iter = 1000;

    // alterar tamanho da matriz
    int n = 20;
    
    //  cria matriz aleatória
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    vector<double> b(n, 0.0);
    srand(time(NULL)); 
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (rand() % 10) + 1; 
        }
        b[i] = (rand() % 50) + 1; 
    }
    
    auto resultado = jacobi_paralelo(A, b, max_iter, epsilon, num_threads);
    cout << "x1 = " << resultado[0] << ", x2 = " << resultado[1] << endl;
    

    return 0;
}
