#include "jacobi.h"
#include <omp.h>
#include <cmath>
#include <vector>
#include <iostream>

vector<double> jacobi_paralelo(vector<vector<double>>& A, vector<double>& b, int max_iter, double epsilon, int num_threads) {
    int n = b.size();
    vector<double> x_old(n, 0.0);
    vector<double> x_new(n, 0.0);
    double erro_max;
    int k;
    
    omp_set_num_threads(num_threads);

    for (k = 0; k < max_iter; k++) {
        erro_max = 0.0;

        #pragma omp parallel for reduction(max:erro_max) shared(A, b, x_old, x_new, n) schedule(static) default(none)
        for (int i = 0; i < n; i++) {
            double soma = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    soma += A[i][j] * x_old[j];
                }
            }
            
            x_new[i] = (b[i] - soma) / A[i][i];

            double erro = fabs(x_new[i] - x_old[i]);
            if (erro > erro_max) {
                erro_max = erro;
            }
        }

        if (erro_max < epsilon) {
            cout << "Convergiu em " << k + 1 << " iteracoes.\n";
            break; 
        }
        
        x_old = x_new;
    }

    return x_new;
}
