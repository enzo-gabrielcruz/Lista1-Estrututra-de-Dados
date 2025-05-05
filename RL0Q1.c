#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 100

int main(){
    FILE* file_in = fopen("L0Q1.in","r");
    FILE* file_out = fopen("L0Q1.out", "w");
    if(file_in == NULL || file_out==NULL){
        printf("%s\n", "Falha na criação dos arquivos!");
        return EXIT_FAILURE;
    }
    char * line = malloc(LINE_MAX_SIZE * sizeof(char));
    const char * separator = " ";
    char * slice;
    int sum = 0;
    while(fgets(line,LINE_MAX_SIZE,file_in) != NULL){
        //printf("%s", line);
        slice = strtok(line, separator);
        while(slice != NULL){
            int value = atoi(slice);
            sum = sum + value;
            slice = strtok(NULL, separator);
        }
        //printf("soma: %d\n", sum);
        fprintf(file_out,"soma: %d\n", sum);
        sum = 0;
    }
    free(line);
    fclose(file_in);
    fclose(file_out);
}

/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX_SIZE 500
// Integrantes da equipe: Enzo Gabriel Calado da Cruz e João Neto


int ContVar(const char *valor){ // esse valor está direcionado para a var slice
        const char* original = valor; // deixa copiado a string a parrtir da posicao inicial.
        int verificador_int = 0;
    // Verifica e transforma os caracteres em variáveis de acordo com o que esse caractere representa, além de contar variáveis distintas
    if (*valor == '-' || *valor == '+') valor++;  // permite sinal no início
    {
        if (*valor == '\0') return 0;  // string só com sinal → inválido
        
        while (*valor) {
            if (!isdigit(*valor))
            {
                verificador_int = 1;
                break;
            } 
            valor++;
        }
        if (verificador_int == 1) return 1;
    }
    valor = original;
    int has_digit = 0;
    int point_count = 0;

    for (; *valor != '\0'; valor++) {
        if (isdigit(*valor)) {
            has_digit = 1;
        } else if (*valor == '.') {
            point_count++;
            if (point_count > 1) return 0; // mais de um ponto
        } else {
            return 0; // caractere inválido
        }
    }
    if(has_digit == 1 && point_count == 1) return 2;
    // return 2 se caractere for um real

    valor = original;
    int only_letter = 1;
    while (*valor) {
        // Verifica se o caractere é alfabético
        if (!isalpha(*valor)) {
            only_letter = 0;
            break;  // Se encontrar um caractere não alfabético, não é uma string válida
        }
        valor++;  // Avança para o próximo caractere
    }
    if(only_letter == 1) return 3;  // Se todos os caracteres forem alfabéticos, é uma string válida

    valor = original;
    int ponto_count = 0;
    has_digit = 0;

        
    // Permite sinal negativo ou positivo no início
    if (*valor == '-' || *valor == '+') valor++;

    // Verifica se a string não está vazia após o sinal
    if (*valor == '\0') return 0;

    while (*valor) {
        if (isdigit(*valor)) {
            // Continuação da verificação de número

        } else if (*valor == ',') {
            ponto_count++;  // Encontrou um ponto
            has_digit = 1;
            if (ponto_count > 1) return 0;   // Mais de um ponto não é válido
        } else {
            return 0;  // Caractere inválido
        }
        valor++;
    }
    if (has_digit == 1 && ponto_count == 1) return 4; // Verifica se existe exatamente um ponto

    return 0;
}

void PreencherVetor(const char *valor, int *qtd_int, int *qtd_str, int *qtd_real, int *qtd_ponto,int *inteiros, float *real,char** string,char** ponto){
    
    int resultado = ContVar(valor);
    if(resultado == 1){
        inteiros[*qtd_int] = atoi(valor);
        (*qtd_int)++;
    }

    if(resultado == 2){
        real[*qtd_real] = atof(valor);
        (*qtd_real)++;
    }

    if(resultado == 3){
        string[*qtd_str] = strdup(valor);
        (*qtd_str)++;
    }
    
    if(resultado == 4){
        ponto[*qtd_ponto] = strdup(valor);
        (*qtd_ponto)++;
    }

    else{

    }
}
//----------------------------------------------
void ordenacao_int(int *inteiros,int *qtd_int){
    for (int i = 1; i < *qtd_int; i++) {
        int chave = inteiros[i];
        int j = i - 1;
        // move os elementos maiores que a chave para frente
        while (j >= 0 && inteiros[j] > chave) {
            inteiros[j + 1] = inteiros[j];
            j = j - 1;
        }
        inteiros[j + 1] = chave;
    }
}
void ordenacao_real(float *real, int *qtd_real){
    for (int i = 1; i < *qtd_real; i++) {
        float chave = real[i];
        int j = i - 1;
        // move os elementos maiores que a chave para frente
        while (j >= 0 && real[j] > chave) {
            real[j + 1] = real[j];
            j = j - 1;
        }
        real[j + 1] = chave;
    }
}
void ordenacao_string(char **string, int *qtd_str){
    for (int i = 1; i < *qtd_str; i++) {
        char *chave = string[i];
        int j = i - 1;

        // Usa strcmp para comparar as strings
        while (j >= 0 && strcmp(string[j], chave) > 0) {
            string[j + 1] = string[j];
            j--;
        }
        string[j + 1] = chave;
    }
}
void ordenacao_ponto(char **ponto, int *qtd_ponto){
    for (int i = 1; i < *qtd_ponto; i++) {
        char *chave = ponto[i];
        int j = i - 1;

        // Usa strcmp para comparar as strings
        while (j >= 0 && strcmp(ponto[j], chave) > 0) {
            ponto[j + 1] = ponto[j];
            j--;
        }
        ponto[j + 1] = chave;
    }
}

void printer(FILE *file_out,int qtd_str, char **string, int qtd_int, int *inteiros, int qtd_real, float *real, int qtd_ponto, char **ponto){
    // Impressão das variáveis.
    fprintf(file_out,"str: ");
    for(int i = 0; i < qtd_str;i++)
    {
       fprintf(file_out,"%s ",string[i]); 
    }   
    fprintf(file_out,"int: ");
    for(int i = 0; i < qtd_int;i++)
    {
        fprintf(file_out,"%d ",inteiros[i]); 
    } 
    fprintf(file_out,"float: ");
    for(int i = 0; i < qtd_real;i++)
    {
        fprintf(file_out,"%f ",real[i]); 
    } 
    fprintf(file_out,"p: ");
    for(int i = 0; i < qtd_ponto;i++)
    {
        fprintf(file_out,"%s ",ponto[i]);
    } 
    printf("\n\n");
}
 
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
    int qtd_str,qtd_int,qtd_real,qtd_ponto;
    
    while(fgets(line,LINE_MAX_SIZE,file_in) != NULL){ //Responsável por realizar a varredura da linha até encontrar todos os caracteres e após isso passa pra próxima linha
        slice = strtok(line, separator);
        // sempre que começo a fazer a varredura de uma nova linha, os contadores zeram sua contagem;
        qtd_int = 0;
        qtd_real = 0;
        qtd_str = 0;
        qtd_ponto = 0;
        int* inteiros = malloc(LINE_MAX_SIZE * sizeof(int));
        float* real = malloc(LINE_MAX_SIZE * sizeof(float));
        char** string = malloc(LINE_MAX_SIZE * sizeof(char*));
        char **ponto = malloc(LINE_MAX_SIZE * sizeof(char*));
            
        while(slice != NULL){
            // aqui vai uma função para realizar a separação dos tipos de variáveis presentes na linha
            PreencherVetor(slice,&qtd_int, &qtd_str, &qtd_real, &qtd_ponto, inteiros, real, string,ponto);       
            slice = strtok(NULL, separator); 
        }
        ordenacao_string(string,&qtd_str);
        ordenacao_int(inteiros,&qtd_int);
        ordenacao_real(real,&qtd_real);
        ordenacao_ponto(ponto,&qtd_ponto);    
        printer(file_out,qtd_str, string, qtd_int, inteiros, qtd_real, real, qtd_ponto, ponto);

        free(inteiros);
        free(real);
        for(int i = 0; i < qtd_str; i++) {
            if (string[i] != NULL) free(string[i]);
        }
        for(int i = 0; i < qtd_ponto; i++) {
            if (ponto[i] != NULL) free(ponto[i]);
        }
        free(string);
        free(ponto);
    }

    free(line);
    fclose(file_in);
    fclose(file_out);

}*/