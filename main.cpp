#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Генерація випадкових чисел в діапазоні [0, 1)
double rand_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Генерація випадкової матриці зв'язності
void generate_adjacency_matrix(int N, double R, int **A) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 0;
        }
    }

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                double distance = fabs(i - j);
                if (distance < R) {
                    A[i][j] = 1;
                }
            }
        }
    }
}

// Виведення матриці
void print_matrix(int N, int **A) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N = 10000;  // Розмірність сітки
    double R = 100; // Радіус зв'язності

    // Виділення пам'яті для матриці
    int **A = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
    }

    // Генерація матриці зв'язності
    double start_time = omp_get_wtime();
    generate_adjacency_matrix(N, R, A);
    double end_time = omp_get_wtime();

    printf("Time taken: %f seconds\n", end_time - start_time);

    // Виведення матриці (опціонально)
    // print_matrix(N, A);

    // Звільнення пам'яті
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}
