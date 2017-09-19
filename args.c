#include "args.h"

/*
    estrutura para a leitura dos parâmetro argc e argv 
*/
arg leitura_parametro(int argc, char *argv[]){
   
    int opt;
    arg entrada, saida;
   
    if (argc == 1){
        printf("Não tem argumento!\n");
        exit(0);
    }
   
    while(1){
         opt = getopt (argc, argv, "i:o:");
        switch (opt){
         case 'i':
            entrada.i = optarg;
            break;
         case 'o':
            entrada.o = optarg;
            break;
      }
      if (opt == -1)
        break;
      if (opt == '?'){
         printf ("%c: Esta opção não existe!\n", optopt);
         break;
      }
    }
    
    return entrada;
}
		