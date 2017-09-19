#ifndef TP2_H
#define	TP2_H
#include <stdio.h>
#include <stdlib.h>

// título das funções que foram utilizadas na main

void calculaall (long int **vertices, long int **resultado, long int linhas, long int colunas);
long int *calcprimeiracoluna(long int **vertices, long int **resultado, long int linhas);
long int **alocarmatriz (long int linhas, long int colunas);
long int resposta (long int **resultado, long int linhas, long int colunas);

#endif
