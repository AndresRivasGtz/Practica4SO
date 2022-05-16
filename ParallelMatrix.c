//
// ParallelMatrix.c
// Practica4
//
//

#include "ParallelMatrix.h"

//Definicion de funciones

int* crea_matriz(int ren, int col){
	return malloc((ren*col)*sizeof(int));
}

void llena_matriz(int *mat, int ren, int col){
	srand(time(NULL));
	int i;
	for(i=0; i<(ren*col); i++){
		*(mat+i) = rand()%256;
	}
}

void suma(int*mat1, int*mat2, int ren, int col){
	int i;
	for(i=0; i<(ren*col); i++){
		*(mat1+i) = *(mat1+i) + *(mat2+i);
	}
}

void sumap(int*mat1, int*mat2, int ren, int col, int numhilos){
	int i, j, n;
	#pragma omp parallel for num_threads(numhilos) private(i) private(j) shared(n)
	for(i=0; i<ren; i++){
		for(j=0 ; j<col ; j++){
			*(mat1+(j+(col*i))) = *(mat1+(j+(col*i))) + *(mat2+(j+(col*i)));
		}
		n= omp_get_num_threads();
	}
	printf("Se han utilizado %d nucleos\n", n);
}

int maximo(int*mat, int ren, int col){
	int i, max;
	max=0;
	for(i=0; i<(ren*col); i++){
		if(max<*(mat+i)){
			max=*(mat+i);
		}
	}
	return max;
}

int maximop(int* mat, int ren, int col, int numhilos){
	int i, j, max, n;
	max=0;
	#pragma omp parallel for num_threads(numhilos) private(i) private(j) shared(max) shared(n)
	for(i=0; i<ren; i++){
		for(j=0 ; j<col ; j++){
			if(max<*(mat+(j+(col*i)))){
				max=*(mat+(j+(col*i)));
			}
		}
		n= omp_get_num_threads();
	}
	printf("Se han utilizado %d nucleos\n", n);
	return max;
}

void libera_matriz(int *mat){
	if(mat!=NULL){
		free(mat);
	}
}
