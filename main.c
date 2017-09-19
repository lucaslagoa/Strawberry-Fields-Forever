//************************************************
//* Aluno: Lucas Lagôa Nogueira                   *                 
//* Matéria: Algoritmo e estruturas de dados III  *
//* Professor: Leonardo Rocha                     * 
//* Segundo Trabalho Prático.	                  *                    
//************************************************

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include "tp2.h"
#include "args.h"

typedef struct timeval Time;

int main (int argc, char *argv[]) {

	arg entrada, saida; //argumentos de entrada e saída

	struct rusage usage;     //estruturas utilizadas para o getusage
	struct timeval start,end;

	long int colunas,linhas,**vertices,**resultado,*resp,i,j,final;

	double tempo; 
	Time inicio, fim; //variáveis para o tempo do gettimeofday
	
	entrada = leitura_parametro(argc,argv);

	getrusage(RUSAGE_SELF,&usage);
	start = usage.ru_stime;
	gettimeofday(&inicio,0);

	FILE *arq;    //abertura do arquivo de entrada
	FILE *arq2;    //abertura do arquivo de saída
	arq = fopen(entrada.i,"r");
	arq2 = fopen(entrada.o,"w");
	
	while(fscanf(arq,"%li",&linhas)!=EOF) {	 //leitura das linhas do arquivo

		fscanf(arq,"%li",&colunas);				//leitura das colunas do arquivo

		vertices=alocarmatriz(linhas,colunas);  //chamada da função de alocar a matriz de vertices
		resultado=alocarmatriz(linhas,colunas);  //chamada da função de alocar a matriz de resultado 
	
		for(i = 0;i < linhas;i++){
			for(j = 0;j < colunas;j++){
				fscanf(arq,"%li",&vertices[i][j]);  //leitura do arquivo de acordo com as linhas e colunas
			}										//da matriz à ser calculada
		}


		resp=calcprimeiracoluna(vertices,resultado,linhas); //chamada da função que resolve a primeira coluna 
		
		for(i=0;i<linhas;i++){
			resultado[i][0]=resp[i];                        //primeira coluna da matriz de resultados recebe
		}	

		long int cont=0;

		for(j=0;j<colunas;j++){  //contador para verificar se alguma coluna possui somente 0
			cont=0;
			for(i=0;i<linhas;i++){
				if(vertices[i][j] == 0 ) {
					cont++;
				}
			}
			if (cont==linhas){
				i=linhas;
				j=colunas;
			}      
		}

		if (cont==linhas){  //verificação se alguma coluna possui 0 em todos elementos, ai não poderia se movimentar
			fprintf(arq2,"0\n");
		} else {
			calculaall(vertices,resultado,linhas,colunas);
			final=resposta(resultado,linhas,colunas);
			fprintf(arq2,"%li\n",final);
		
		}
		
		getrusage(RUSAGE_SELF, &usage);     //função dos getusage e gettimeofday e seus prints de acordo
		end = usage.ru_stime;               //com a especificação
		gettimeofday(&fim, 0);
		tempo = (fim.tv_sec + fim.tv_usec/1000000.0) - (inicio.tv_sec  + inicio.tv_usec/1000000.0);
		printf("Tempo do sistema: %f segundos\n",tempo);
		printf("Tempo de usuário: Começo: %ld.%lds\n",start.tv_sec,start.tv_usec);
		printf("Tempo de usuário: Fim: %ld.%lds\n",end.tv_sec,end.tv_usec);
		printf("\n");
	}
		
	fclose(arq);  //fechamento dos arquivos que foram utilizados
	fclose(arq2);
	return 0;

}
