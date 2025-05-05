

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LINE_MAX_SIZE 501

typedef struct {
    char string[501];
    double distancia;
}ponto;

// Função para identificar o tipo
int ContVar(const char *valor) {
    if (valor[0] == '(' && valor[strlen(valor)-1] == ')') return 4; // ponto

    int has_digit = 0, has_dot = 0;
    const char *p = valor;

    if (*p == '-' || *p == '+') p++;
    if (*p == '\0') return 0;

    while (*p) {
        if (isdigit(*p)) {
            has_digit = 1;
        } else if (*p == '.') {
            has_dot++;
            if (has_dot > 1) return 0;
        } else {
            has_digit = 0;
            break;
        }
        p++;
    }

    if (has_digit) return has_dot ? 2 : 1; // 2 = float, 1 = int

    p = valor;
    while (*p) {
        if (!isalpha(*p)) return 0;
        p++;
    }
    return 3; // string
}

void PreencherVetor(const char *valor, int *qtd_int, int *qtd_str, int *qtd_real, int *qtd_ponto,
                    int *inteiros, float *reais, char **strings, ponto pontos[]) {
    int tipo = ContVar(valor);
    if (tipo == 1) inteiros[(*qtd_int)++] = atoi(valor);
    else if (tipo == 2) reais[(*qtd_real)++] = atof(valor);
    else if (tipo == 3) strings[(*qtd_str)++] = strdup(valor);
    else if (tipo == 4) {
        strncpy(pontos[*qtd_ponto].string, valor, 500);
        pontos[*qtd_ponto].string[500] = '\0';
        (*qtd_ponto)++;
    }
}

int cmp_str(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_float(const void *a, const void *b) {
    float fa = *(float *)a, fb = *(float *)b;
    return (fa > fb) - (fa < fb);
}

void calcular_distancia_euclidiana(ponto pontos[],int qtd_ponto) {
    int x, y;
    for (int i = 0; i < qtd_ponto; i++)
    {
        if (sscanf(pontos[i].string, "(%d,%d)", &x, &y) == 2) {
           pontos[i].distancia = sqrt(x*x + y*y);
        } 
    }
}

void OrdenarPontos(ponto pontos[],int qtd_ponto, ponto chave) {
    int i, j;
    for (i = 0; i < qtd_ponto; i++) {
        chave = pontos[i];
        j = i - 1;
        while (j >= 0 && pontos[j].distancia > chave.distancia) {
            pontos[j + 1] = pontos[j];
            j = j - 1;
        }
            pontos[j + 1] = chave;
        }
}


void printer(FILE *out, int qtd_str, char **strings, int qtd_int, int *inteiros, int qtd_real, float *reais, int qtd_ponto,ponto pontos[]) {
    if (qtd_str == 0) fprintf(out, "str: ");
    else fprintf(out,"str:");
    for (int i = 0; i < qtd_str; i++) fprintf(out, "%s ", strings[i]);
    
    if (qtd_int == 0) fprintf(out, "int: ");
    else  fprintf(out, "int:");
    for (int i = 0; i < qtd_int; i++) fprintf(out, "%d ", inteiros[i]);
    
    if (qtd_real == 0)fprintf(out, "float: ");
    else fprintf(out, "float:");
    for (int i = 0; i < qtd_real; i++) fprintf(out, "%.6g ", reais[i]);
    
    fprintf(out, "p:");
    for(int i = 0; i < qtd_ponto; i++){
        if (i < qtd_ponto -1 )fprintf(out, "%s ", pontos[i].string);
        if (i == qtd_ponto -1)fprintf(out,"%s",pontos[i].string);
    } 
    fprintf(out,"\n");
   
}

void remover_ultima_linha_em_branco(const char *file_out) {
    FILE *arquivo = fopen(file_out, "rb");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    // Descobre tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    // Lê todo o conteúdo
    char *conteudo = malloc(tamanho + 1);
    if (!conteudo) {
        fclose(arquivo);
        fprintf(stderr, "Erro de alocação\n");
        return;
    }

    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';
    fclose(arquivo);

    // Remove último \n se existir
    if (tamanho > 0 && conteudo[tamanho - 1] == '\n') {
        conteudo[tamanho - 1] = '\0';
        tamanho--;
    }

    // Regrava o arquivo sem a última quebra de linha
    arquivo = fopen(file_out, "wb");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        free(conteudo);
        return;
    }

    fwrite(conteudo, 1, tamanho, arquivo);
    fclose(arquivo);
    free(conteudo);
}

int main() {
    ponto pontos[500],chave;
    FILE *file_in = fopen("L0Q1.in", "r");
    FILE *file_out = fopen("L0Q1.out", "w");
    if (!file_in || !file_out) {
        printf("Erro ao abrir arquivos\n");
        return 1;
    }

    char line[LINE_MAX_SIZE];
    
    while (fgets(line, LINE_MAX_SIZE, file_in)) {
        char *p = line;
        int qtd_int = 0, qtd_real = 0, qtd_str = 0, qtd_ponto = 0;
        int inteiros[500];
        float reais[500];
        char *strings[500];

        while (*p == ' ' || *p == '\n') p++;  // pula espaços no começo
        {
        }
        if (*p == '\0') continue;  // linha vazia → pula

        char *token = strtok(line, " \n");
        while (token) {
            PreencherVetor(token, &qtd_int, &qtd_str, &qtd_real, &qtd_ponto, inteiros, reais, strings, pontos);
            token = strtok(NULL, " \n");
        }

        qsort(strings, qtd_str, sizeof(char *), cmp_str);
        qsort(inteiros, qtd_int, sizeof(int), cmp_int);
        qsort(reais, qtd_real, sizeof(float), cmp_float);
        calcular_distancia_euclidiana(pontos,qtd_ponto);
        OrdenarPontos(pontos,qtd_ponto,chave);
   
        printer(file_out, qtd_str, strings, qtd_int, inteiros, qtd_real, reais, qtd_ponto, pontos);
        for (int i = 0; i < qtd_str; i++) {
            free(strings[i]);
        }
    }
    
   
    fclose(file_in);
    fclose(file_out);
    remover_ultima_linha_em_branco("L0Q1.out");

}
