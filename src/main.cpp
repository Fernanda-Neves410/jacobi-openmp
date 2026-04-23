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
    double temp_inicial, temp_final, temp_total, 
            speedup, eficiencia;

    // alterar tamanho da matriz
    int n = 200;

    // Gera uma matriz diagonal dominante
    // Cria todos os elementos da matriz com valor 1.0
    // Add (soma de todos os elementos da linha + 0.5) nos elementos da diagonal principal
    // valores de b = {2, 4, 8, 10, ...)
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    vector<double> b(n, 0.0);

    for (int i = 0; i < n; i++) {
            double soma_linha = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    A[i][j] = 1.0; 
                    soma_linha += A[i][j];
                }
            }
            A[i][i] = soma_linha + 0.5; 
            b[i] = (i + 1) * 2.0; 
    }
        
    /*
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
    */

    //  sequencial
    temp_inicial = omp_get_wtime();
    auto resultado = jacobi_sequencial(A, b, max_iter, epsilon);
    temp_final = omp_get_wtime();
    temp_total = temp_final - temp_inicial;
    double temp_seq = temp_total;
    cout << "Tempo sequencial: " << temp_seq << "s\n\n";

    //  paralelo
    //  printa num de threads e valores de x
    //  printa tempo, speedup e (speedup / threads)
    for(int threads : num_threads_teste) {
        temp_inicial = omp_get_wtime();
        auto resultado = jacobi_paralelo(A, b, max_iter, epsilon, threads);
        temp_final = omp_get_wtime();
        temp_total = temp_final - temp_inicial;

        speedup = temp_seq / temp_total;
        eficiencia = speedup / threads;

        cout << "Threads: " << threads;
        cout << "   Tempo: " << temp_total << "s" << "\n";
        cout << "Speedup: " << speedup <<"X     " << "Eficiencia: " << eficiencia << "\n";
        for(i = 0; i < n; i++)
            cout << "x[" << i << "]=" << resultado[i] << "  ";
        cout << "\n\n";
    }
    

    return 0;
}
