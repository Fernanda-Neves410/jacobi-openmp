#include "jacobi.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() {
    double epsilon = 1e-6;
    vector<int> num_threads_teste = {1, 2, 4, 6, 8, 12};
    int max_iter = 1000;
    int i, j;

    // alterar tamanho da matriz
    int n = 5;
    
    //  cria matriz aleatória
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    vector<double> b(n, 0.0);
    srand(time(NULL)); 
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = (rand() % 10) + 1;
        }
        b[i] = (rand() % 50) + 1; 
    }
    
    //  printa num de threads e valores de x
    //  printa tempo
    for(int threads : num_threads_teste) {
        double temp_inicio = omp_get_wtime();
        auto resultado = jacobi_paralelo(A, b, max_iter, epsilon, threads);
        double temp_final = omp_get_wtime();
        double tempo_total = temp_final - temp_inicio;


        cout << "Threads: " << threads;
        cout << "   Tempo: " << tempo_total << "s" << "\n";
        for(i = 0; i < n; i++)
            cout << "x[" << i << "]=" << resultado[i] << "  ";
        cout << "\n\n";
    }
    

    return 0;
}
