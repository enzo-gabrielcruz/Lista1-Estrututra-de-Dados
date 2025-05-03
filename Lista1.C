#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 500
// Integrantes da equipe: Enzo Gabriel Calado da Cruz e João Neto


int VerificadorVariavel(){
// Verifica e transforma os caracteres em variáveis de acordo com o que esse caractere representa.
}
//----------------------------------------------
void ordenacao(){
// realizar ordenação dos vetores.
}
//----------------------------------------------
void printer(){
    // Impressão das variáveis.
}
//-----------------------------------------------
int main(){
    FILE* file_in = fopen("L0Q1.in","r");
    FILE* file_out = fopen("L0Q1.out", "w");

    if(file_in == NULL || file_out==NULL){
        printf("%s\n", "Falha na criação dos arquivos!");
        return EXIT_FAILURE;
    }

    if(file_in == NULL || file_out==NULL){
        printf("%s\n", "Falha na criação dos arquivos!");
        return EXIT_FAILURE;
    }

    char * line = malloc(LINE_MAX_SIZE * sizeof(char));
    const char * separator = " ";
    char * slice;
    int qtd_str,qtd_int,qtd_real,int_ponto;
    int inteiros[qtd_int];
    char string[qtd_str];
    float real[qtd_real];
    char ponto[12][int_ponto];
    
    while(fgets(line,LINE_MAX_SIZE,file_in) != NULL){ //Responsável por realizar a varredura da linha até encontrar todos os caracteres e após isso passa pra próxima linha
        





        
    }

    
    free(line);
    fclose(file_in);
    fclose(file_out);

}