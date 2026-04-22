#include "jacobi.h"
#include <omp.h>
#include <cmath>
#include <vector>

vector<double> jacobi_paralelo(vector<vector<double>>& A, vector<double>& b, int max_iter, double epsilon, int num_threads) {
    int n = b.size();
    vector<double> x_old(n, 0.0);
    vector<double> x_new(n, 0.0);
    double max_diff = 0.0;
    int iter = 0;
    omp_set_num_threads(num_threads);

    do {
        #pragma omp parallel for reduction(max:max_diff) shared(A, b, x_old, x_new, n) schedule(static) default(none)
        for (int i = 0; i < n; i++) {
            double soma = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j)
                 soma += A[i][j] * x_old[j];
            }
            x_new[i] = (b[i] - soma) / A[i][i];

            double diff = std::abs(x_new[i] - x_old[i]);
            if (diff > max_diff) 
                max_diff = diff;
        }

        x_old = x_new;
        iter++;
    } while (max_diff > epsilon && iter < max_iter);

    return x_new;
}
