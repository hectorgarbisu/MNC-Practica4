#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mkl.h>
int main(int argc, char	*argv[]){
	// matriz de	datos				
	double A[16] = {5.0, 5.0, 7.0, 9.0,
		4.0, 8.0, 8.0, 10.0,
		5.0, 7.0, 11.0, 11.0,
		6.0, 8.0, 10.0, 14.0};
	int pivot[4]; // vector para los pivotamientos
	// buffer para resultados, recordar que LAPACK destruye los datos 
	double A2[16];
	for (int i = 0; i < 16; i++) A2[i] = A[i];
	// memcpy(A2, A, 16 * sizeof(double)); // una forma mas eficiente de hacer la copia
	// obtener la descomposici�n LU con pivotamientc|
	int result = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, 4, 4, A2, 4, pivot);
	// NOTA: check de result, lo excluimos en este ejemplo
	// imprimir el resultado
	printf("Matriz con L y U mezcladas:\n");
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			printf("%lf ",A2[i*4+j]);
		}
		printf("\n");
	}
	printf("\nVector de pivotamientos:\n");
	for (int i = 0; i < 4; i++) printf("%d ",pivot[i]);
		printf("\n");
	/////
	double determinante = 1.0;
	for (int i = 0; i < 4; i++){
		if (pivot[i] != (i+1)){ // NOTA: MKL usa como Fortran como fila i+1 
			determinante *= -A2[i * 4 + i]; // producto de diagonal con -1
		}
		else{
			determinante *= A2[i * 4 + i];
		}
	}
	printf("\nDeterminante: %lf\n",determinante);
	/////////////// PAGINA 10 ///////////////////////
	double B[16];
	memset(B, 0, 16 * sizeof(double));
	for (int i = 0; i < 4; i++) B[i * 4 + i] = 1.0; // matriz identidad 
	result = LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'N' ,4,4,A2,4,pivot,B,4); 
		printf("\nMatriz inversa:\n");
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			printf("%lf ", B[i * 4 + j]);
		}
		printf("\n");
	}
	/////////////// PAGINA 11 ///////////////////////
	double C[16]; 
	memcpy(C, A2, 16 * sizeof(double)); // copia de la descomposici6n LU 
	result = LAPACKE_dgetri(LAPACK_ROW_MAJOR, 4, C, 4, pivot);
	printf("\nMatriz inversa (segundo metodo):\n");
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			printf("%lf ", C[i * 4 + j]);
		}
		printf("\n");
	}
	


	printf("\nH�ctor Garbisu MNC 2015\n");
	std::getchar();
	return 0;
}