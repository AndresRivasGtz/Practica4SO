//
// ParallelMatrix.h
// Practica4
//
//

#pragma once

#ifndef ParallelMatrix_h
#define ParallelMatrix_h

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Prototipos de funciones

int* crea_matriz(int, int);
void llena_matriz(int *, int, int);
void suma(int*, int*, int, int);
void sumap(int*, int*, int, int, int);
int maximo(int*, int, int);
int maximop(int*, int, int, int);
void libera_matriz(int*);
#endif
