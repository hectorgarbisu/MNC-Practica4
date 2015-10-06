#include <cstdio>
#include <cstdlib>
#include <random>
#include <mkl.h>
int main(int argc, char *argv[]){
	// matriz en banda, ku=kl=l 
	double A[25] = {
		1.0, 2.0, 0.0, 0.0, 0.0,
		3.0, 0.0, 4.0, 5.0, 0.0,
		0.0, 6.0, 7.0, 8.0, 0.0,
		0.0, 0.0, 9.0, 10.0, 11.0,
		0.0, 0.0, 0.0, 12.0, 13.0};

	double Ab[20] = {	// A codificada en forma de bandas para LU
		0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 2.0, 5.0, 8.0, 11.0,
		1.0, 4.0, 7.0, 10.0, 13.0,
		3.0, 6.0, 9.0, 12.0, 0.0};

	double B[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	double X[5];
	int pivot[5];
	int result;

	// soluci6n como matriz general
	memcpy(X, B, 5 * sizeof(double)); // la rutina destruye A y B 
	result = LAPACKE_dgesv(LAPACK_ROW_MAJOR, 5, 1, A, 5, pivot, X, 1);
	printf("Solucion general\n");
	for (int i = 0; i < 5; i++) printf("%lf\n", X[i]);

	// soluci6n como matriz de bandas, se debe codificar A en forma de bandas 
	result = LAPACKE_dgbsv(LAPACK_ROW_MAJOR, 5, 1, 1, 1, Ab, 5, pivot, B, 1);
	printf("\nSolucion en bandas\n");
	for (int i = 0; i < 5; i++) printf("%lf\n", B[i]);

	printf("\nHéctor Garbisu MNC 2015\n");
	std::getchar();
	return 0;
}