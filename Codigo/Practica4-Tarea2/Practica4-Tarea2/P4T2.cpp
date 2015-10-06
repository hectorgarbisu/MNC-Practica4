#include <cstdio>
#include <cstdlib>
#include <random>
#include <mkl.h>
#define N 1000 
#define NTEST 20
int main(int argc, char *argv[]){
	double inicio, fin = dsecnd();
	double *A = (double *)mkl_malloc(N*N*sizeof(double), 64);
	double *B = (double *)mkl_malloc(N*sizeof(double), 64);
	int *pivot = (int *)mkl_malloc(N*sizeof(int), 32);
	// distribucion normal de media 0 y varianza 1 
	std::default_random_engine generador;
	std::normal_distribution<double> aleatorio(0.0, 1.0);
	for (int i = 0; i < N*N; i++) A[i] = aleatorio(generador);
	for (int i = 0; i < N; i++) B[i] = aleatorio(generador);
	// matriz A marcadamente diagonal para evitar riesgo de singularidad 
	for (int i = 0; i < N; i++) A[i*N + i] += 10.0;
	int result;
	inicio = dsecnd();
	for (int i = 0; i < NTEST; i++)
		result = LAPACKE_dgesv(LAPACK_ROW_MAJOR, N, 1, A, N, pivot, B, 1);
	fin = dsecnd();
	double tiempo = (fin - inicio) / (double)NTEST;
	printf("Tiempo: %lf msec\n", tiempo*1.0e3);
	mkl_free(A);
	mkl_free(B);
	std::getchar(); return 0;
}