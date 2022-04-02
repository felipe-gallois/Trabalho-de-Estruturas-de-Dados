#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#include "config.h"
#include "leitor.h"

#if defined(PROGRAMA_ABP)
#include "abp.h"
#elif defined(PROGRAMA_AVL)
#include "avl.h"
#else
#include "default.h"
#error Versao do programa nao reconhecida.
#endif

int numero_de_nodos;
int altura_da_arvore;
int numero_de_rotacoes;
int numero_de_comparacoes;

// Carrega as palavras do dicionário para a árvore.
#if defined(PROGRAMA_ABP)
Arvore* CarregaDicionario(FILE* dicionario, Arvore* raiz) {
    char linha[TAMANHO_MAXIMO_LINHA];
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    char sinonimo[TAMANHO_MAXIMO_PALAVRA];

    int sinal = 0;
    while(!sinal) {
        sinal = LeLinhaDicionario(dicionario, linha, palavra, sinonimo);
        if(!sinal)
            raiz = InsereParDeNodos(palavra, sinonimo, raiz);
    }
    return raiz;
}
#elif defined(PROGRAMA_AVL)
Arvore* CarregaDicionario(FILE* dicionario, Arvore* raiz, int *ok) {
    char linha[TAMANHO_MAXIMO_LINHA];
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    char sinonimo[TAMANHO_MAXIMO_PALAVRA];

    int sinal = 0;
    while(!sinal) {
        sinal = LeLinhaDicionario(dicionario, linha, palavra, sinonimo);
        if(!sinal)
            raiz = InsereParDeNodos(palavra, sinonimo, raiz, ok);
    }
    return raiz;
}
#endif

// Percorre o texto de entrada, salvando o conteúdo no arquivo de saída e
// realizando as devidas substituições por sinônimos.
void ParafraseiaEntrada(FILE *entrada, FILE *saida, Arvore *arvore) {
    int letra;
    char c = fgetc(entrada);
    if(Letra(c))
        letra = 1;
    else
        letra = 0;
    
    char buffer[TAMANHO_MAXIMO_PALAVRA];
    buffer[0] = '\0';
    while(!feof(entrada)) {
        if(Letra(c) == letra) {
            strncat(buffer, &c, 1);
            c = fgetc(entrada);
        } else {
            if(letra) {
                DespachaBufferDeLetras(buffer, saida, arvore);
                buffer[0] = '\0';
                letra = 0;
            } else {
                DespachaBufferDeSimbolos(buffer, saida);
                buffer[0] = '\0';
                letra = 1;
            }
        }
    }
    if(buffer[0] != '\0') {
        if(letra)
            DespachaBufferDeLetras(buffer, saida, arvore);
        else
            DespachaBufferDeSimbolos(buffer, saida);
    }
}

// Imprime as estatísticas sobre a operação após o texto alvo ter sido
// parafraseado.
void ImprimeEstatisticas() {
    printf("============ ESTAT%cSTICAS %s ============\n", 0xcd, TIPO_DE_ARVORE);
    printf("N%cmero de Nodos: %d\n", 0xfa, numero_de_nodos);
    printf("Altura: %d\n", altura_da_arvore);
    printf("Rota%c%ces: %d\n", 0xe7, 0xf5, numero_de_rotacoes);
    printf("Compara%c%ces: %d\n", 0xe7, 0xf5, numero_de_comparacoes);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if(argc != 4) {
        fprintf(stderr, "Erro! N%cmero inv%clido de argumentos.\n", 0xfa, 0xe1);
        return 1;
    }
    
    FILE *dicionario = fopen(argv[1], "r");
    if(dicionario == NULL) {
        fprintf(stderr, "Erro! N%co foi poss%cvel abrir o arquivo de dicion%crio.\n", 0xe3, 0xed, 0xe1);
        return 1;
    }

    Arvore *arvore = InicializaArvore();

    #if defined(PROGRAMA_ABP)
    arvore = CarregaDicionario(dicionario, arvore);
    #elif defined(PROGRAMA_AVL)
    int ok;
    arvore = CarregaDicionario(dicionario, arvore, &ok);
    #endif

    numero_de_nodos = ContaNodosArvore(arvore);
    altura_da_arvore = CalculaAlturaArvore(arvore);

    FILE *entrada = fopen(argv[2], "r");
    if(entrada == NULL) {
        fprintf(stderr, "Erro! N%co foi poss%cvel abrir o arquivo de entrada.\n", 0xe3, 0xed);
        return 1;
    }
    FILE *saida = fopen(argv[3], "w");
    if(saida == NULL) {
        fprintf(stderr, "Erro! N%co foi poss%cvel abrir o arquivo de sa%cda.\n", 0xe3, 0xed, 0xed);
        return 1;
    }

    ParafraseiaEntrada(entrada, saida, arvore);

    ImprimeEstatisticas();

    return 0;
}