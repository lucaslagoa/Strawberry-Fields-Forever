#ifndef ARGS_H
#define ARGS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//título da função de leitura de parâmetro

typedef struct arg
{
	char *i, *o;
}arg;

arg leitura_parametro(int argc, char *argv[]);

#endif



