#include "tp2.h"

/*
 função de alocação da matriz, cujas matrizes utilizadas são as de vértices e a de resultado
*/
long int **alocarmatriz (long int linhas, long int colunas) { 
	long int **vetormorango,i;
	vetormorango = malloc ( linhas *sizeof ( long int));
	for(i = 0;i < linhas; i++) {
		vetormorango[i]= (long int *) malloc (colunas *sizeof(long int));
	}
	return vetormorango;
}
/* função calcprimeiracoluna
		Função que calcula o caso base, que seria a primeira coluna.
	Basicamente a função verifica os valores da primeira coluna e verifica as possibilidades
	que maximizam a soma dela, para ser utilizada posteriormente, e essa soma seria a solução ótima
	dessa coluna.
*/
long int *calcprimeiracoluna(long int **vertices, long int **resultado, long int linhas) {

	long int i,j,soma=0,*vetorUp,*vetorDown,*resp;

	vetorUp = malloc ( linhas *sizeof (long int));
	vetorDown = malloc ( linhas *sizeof (long int));
	resp = malloc ( linhas *sizeof (long int));

		for (i = 0; i < linhas; i++){
			
			for (j = i; (j >= 0) && (vertices[j][0] != 0 ); j--) { //sobe
					soma=soma+vertices[j][0];
			}

			vetorUp[i]=soma;
			soma=0;

			for (j = i; (j < linhas) && (vertices[j][0] != 0) ; j++) { //desce
					soma=soma+vertices[j][0];
				}

			vetorDown[i]=soma;
			soma=0;

			if (vetorUp[i] > vetorDown[i]) {
				resp[i]=resp[i]+vetorUp[i];
			} else { 
				resp[i]=resp[i]+vetorDown[i];
			}
			}
		
	return resp;	
}

/*	Função calculaall
		Essa função basicamente calcula os resultados ótimos de cada coluna, primeiramente se baseando na primeira
	que o valor ja foi calculado posteriormente. Primeiramente verificamos podemos nos movimentar, ou seja não tem
	0 no caminho. Se tiver, os possíveis vetores ótimos (subida e descida) recebem 0, se não, eles recebem a primeira coluna
	já calculada mais os valores da segunda coluna (simulando o movimento para a direita).
		Logo após isso, devemos verificar as bordas de cada caso, e sempre pegar o maior resultado
	se possível, do resultado posterior.
		E após verificarmos as bordas, podemos calcular dos vetores de subida e descida normalmente. 
	No caso do vetor de subida, começa-se do final logo acima da borda e verifica as condições de andar e sempre
	procurando pegar o maior resultado. Ambos vetores devem se considerar, se um dos valores é 0 e o anterior na original 
	também é 0, e se pudermos nos movimentar, realizamos o movimento e consideramos o maior valor sempre.
		Após isso, verificamos os vetores de subida e descida, e pega-se o maior resultado. E com o vetor resultado, 
	repetiremos o processo, mas agora com esse novo vetor ótimo.
*/
void calculaall (long int **vertices, long int **resultado, long int linhas, long int colunas) {

	long int i,j,*vetorSubida,*vetorDescida,*newVetorSubida,*newVetorDescida,*newVetorOtimo;

	vetorSubida = malloc ( linhas *sizeof (long int));
	vetorDescida = malloc ( linhas *sizeof (long int));
	newVetorSubida = malloc ( linhas *sizeof (long int));
	newVetorDescida = malloc ( linhas *sizeof (long int));
	newVetorOtimo = malloc ( linhas *sizeof (long int));

	for(j=1;j<colunas;j++) {
		for(i=0; i<linhas ; i++){ //vetores de subida e descida recebem de acordo com as condições
			if ( vertices[i][j] == 0 || resultado[i][j-1] == 0) {
				vetorSubida[i] = 0;
				vetorDescida[i] = 0;
			} else {
				vetorSubida[i]=	resultado[i][j-1] + vertices[i][j];
				vetorDescida[i]= resultado[i][j-1] + vertices[i][j];
			}
		}

	
	if (vetorSubida[linhas-1] > vertices[linhas-1][j]) { //comparação da borda de subida
		newVetorSubida[linhas-1] = vetorSubida[linhas-1];
	} else {
		newVetorSubida[linhas-1] = vertices[linhas-1][j]; 
	}


	for (i=linhas-2; i>=0 ;i--) { //subida
		if ((vetorSubida[i] == 0)  && (vertices[i][j] == 0)) {
			newVetorSubida[i]=0;
		} else if(vertices[i+1][j] != 0 && newVetorSubida[i+1] != 0 && (newVetorSubida[i+1]+vertices[i][j] > vetorSubida[i])) {
			newVetorSubida[i] = newVetorSubida[i+1] + vertices[i][j];
		} else {
			newVetorSubida[i] = vetorSubida[i];
		}
	}

	if	(vetorDescida[0] < vertices[0][j]) { //borda de descida
		newVetorDescida[0] = vertices[0][j];
	} else {
		newVetorDescida[0] = vetorDescida[0];
	}


	for (i=1;i<linhas;i++) { //descida
		if((vetorDescida[i] == 0) && (vertices[i][j] == 0)){
			newVetorDescida[i] = 0;
		} else if (vertices[i-1][j] != 0 && newVetorDescida[i-1] != 0 && (newVetorDescida[i-1]+vertices[i][j] > vetorDescida[i])) {
				newVetorDescida[i] = newVetorDescida[i-1] + vertices[i][j];
		} else {
				newVetorDescida[i] = vetorDescida[i];
		}
	}
	

	for(i=0;i<linhas;i++) { //maiores valores para utilizar no vetor Ótimo
		if(newVetorSubida[i] >= newVetorDescida[i]){
			newVetorOtimo[i] = newVetorSubida[i];
		} else {
			newVetorOtimo[i] = newVetorDescida[i];
		}
	}

	for(i=0;i<linhas;i++){
		resultado[i][j]=newVetorOtimo[i];
	}		
	}
}
/*
	função resposta
	Essa função verifica a última coluna e acha o maior valor para imprimí-lo

*/
long int resposta (long int **resultado, long int linhas, long int colunas) {

	long int i,maior=0;

	for(i=0;i<linhas;i++) {

		if(maior < resultado[i][colunas-1]){
			maior = resultado[i][colunas-1];
		}
	}
	return maior;
}


