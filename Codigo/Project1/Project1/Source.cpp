#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mkl.h>
int main(int argc, char	*argv[]){

	double determinante = 1.0;
	for (int i = 0; i < 4; i++){
		if (pivot[i] != (i + l)){ // NOTA: MKL usa como Fortran como fila i+1 
			determinante *= -A2[i * 4 + i]j // producto de diagonal con -1
		}
		else{
			determinante *= A2[i * 4 + i];
		}
	}
	printf("\nDeterminante: %lf\n",determinante);
	std::getchar();
	return 0;
}