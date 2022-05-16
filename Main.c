//
// Main.c
// Practica4
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	
	//Variables a utilizar
	int ren[6] = {10, 50, 200, 1000, 1200, 1920};
	int col[6] = {20, 50, 100, 1000, 1200, 1080};
	int numhilos[4] = {1, 2, 3, 4};
	int *mat1, *mat2, *matp1, *matp2;
	int forhilos, format, max;
	double tiemposuma[4][6], tiemposumap[4][6], tiempomax[4][6], tiempomaxp[4][6];
	struct timespec s1, s2, sp1, sp2, m1, m2, mp1, mp2;
	//Instrucciones para realizar la simulacion con 1, 2, 3 y 4 hilos disponibles para 4 nucleos.
	for(forhilos=0 ; forhilos<4 ; forhilos++){
		//Instrucciones para utilizar una cantidad de hilos.	
	

		//Instruccion para imprimir la cantidad de nucleos disponibles en la computadora
		printf("-----------------------------------------------------------------");
		printf("Cantidad de nucleos disponibles: %d\n", omp_get_max_threads());
		//y la cantidad maxima de hilos que se solicitaron.
		printf("Cantidad de hilos a utilizar: %d\n", numhilos[forhilos]);
		/*Instrucciones para realizar la simulacion con matrices de
		10 x 20
		50 x 50
		200 x 100
		1000 x 1000
		1200 x 1200
		1920 x 1080.
		*/
		for(format=0 ; format<6 ; format++){
		
		//Funcion para inicializar las matrices.
		mat1 = crea_matriz(ren[format], col[format]);
		mat2 = crea_matriz(ren[format], col[format]);
		matp1 = crea_matriz(ren[format], col[format]);
		matp2 = crea_matriz(ren[format], col[format]);
		llena_matriz(mat1, ren[format], col[format]);
		llena_matriz(mat2, ren[format], col[format]);
		llena_matriz(matp1, ren[format], col[format]);
		llena_matriz(matp2, ren[format], col[format]);
		printf("Se han creado 2 matrices de dimensiones: %d * %d\n", ren[format], col[format]);
	
		//Funcion para sumar las matrices de forma no paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &s1);
		suma(mat1, mat2, ren[format], col[format]);
		clock_gettime(CLOCK_MONOTONIC, &s2);
		tiemposuma[forhilos][format]=(double)(s2.tv_sec-s1.tv_sec)+((double)(s2.tv_nsec-s1.tv_nsec)/1000000000L);
		
		//Funcion para sumar las matrices de forma paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &sp1);
		sumap(matp1, matp2, ren[format], col[format], numhilos[forhilos]);
		clock_gettime(CLOCK_MONOTONIC, &sp2);
		tiemposumap[forhilos][format]=(double)(sp2.tv_sec-sp1.tv_sec)+((double)(sp2.tv_nsec-sp1.tv_nsec)/1000000000L);

		//Funcion para obtener el valor maximo de forma no paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &m1);
		max=maximo(mat1, ren[format], col[format]);
		clock_gettime(CLOCK_MONOTONIC, &m2);
		tiempomax[forhilos][format]=(double)(m2.tv_sec-m1.tv_sec)+((double)(m2.tv_nsec-m1.tv_nsec)/1000000000L);
		printf("El maximo de la matriz es: %d\n", max);

		//Funcion para obtener el valor maximo de forma paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &mp1);
		max=maximop(matp1, ren[format], col[format], numhilos[forhilos]);
		clock_gettime(CLOCK_MONOTONIC, &mp2);
		tiempomaxp[forhilos][format]=(double)(mp2.tv_sec-mp1.tv_sec)+((double)(mp2.tv_nsec-mp1.tv_nsec)/1000000000L);
		printf("El maximo en paralelo de la matriz es: %d\n\n", max);
		
		}
		printf("\n\n\n\n");
		libera_matriz(mat1);
		libera_matriz(mat2);
		libera_matriz(matp1);
		libera_matriz(matp2);
	}
	
	//Impresion de tabla de tiempos de TODA la simulacion.
	for(forhilos=0 ; forhilos<4 ; forhilos++){
		printf("\n\n\nPara %d nucleos:\n\n", forhilos+1);
		for(format=0 ; format<6 ; format++){
			printf("\nEn la matriz de: %d*%d\n\n", ren[format], col[format]);		
			printf("suma: %.4f\n", tiemposuma[forhilos][format]);
			printf("suma paralelo: %.4f\n", tiemposumap[forhilos][format]);
			printf("maximo: %.4f\n", tiempomax[forhilos][format]);
			printf("maximop: %.4f\n", tiempomaxp[forhilos][format]);
		}
	}

	return EXIT_SUCCESS;
}
