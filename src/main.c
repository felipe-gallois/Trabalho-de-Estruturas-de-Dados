#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#include "config.h"
#include "leitor.h"

// Inclui os cabeçalhos para a versão selecionada do programa
#if defined(PROGRAMA_ABP)
    #include "abp.h"
#elif defined(PROGRAMA_AVL)
    #include "avl.h"
#else
    #include "default.h"
    #error Versao do programa nao reconhecida.
#endif

// Variáveis globais
int numero_de_nodos;
int altura_da_arvore;
int numero_de_rotacoes;
int numero_de_comparacoes;

// Define a assinatura da função de acordo com a versão do programa selecionada
#if defined(PROGRAMA_ABP)
    Arvore* CarregaDicionario(FILE* dicionario, Arvore* raiz);
#else
    Arvore* CarregaDicionario(FILE* dicionario, Arvore* raiz, int *ok);
#endif

// Assinaturas das demais funções
void ParafraseiaEntrada(FILE *entrada, FILE *saida, Arvore *arvore);
void ImprimeEstatisticas();

int main(int argc, char *argv[]) {
    // Permite escrita na linha de comando com caracteres extendidos
    setlocale(LC_ALL, "");

    // Valida comando
    if(argc != 4) {
        fprintf(stderr, "Erro! N%cmero inv%clido de argumentos.\n", 0xfa, 0xe1);
        return 1;
    }

    FILE *dicionario = fopen(argv[1], "r");
    if(dicionario == NULL) {
        fprintf(stderr, "Erro! N%co foi poss%cvel abrir o arquivo de dicion%crio.\n", 0xe3, 0xed, 0xe1);
        return 1;
    }

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

    // Monta a árvore com as palavras do dicionário
    Arvore *arvore = InicializaArvore();

    #if defined(PROGRAMA_ABP)
        arvore = CarregaDicionario(dicionario, arvore);
    #elif defined(PROGRAMA_AVL)
        int ok;
        arvore = CarregaDicionario(dicionario, arvore, &ok);
    #endif

    // Percorre o texto de entrada e escreve o texto de saída
    ParafraseiaEntrada(entrada, saida, arvore);

    // Calcula estatísticas restantes
    numero_de_nodos = ContaNodosArvore(arvore);
    altura_da_arvore = CalculaAlturaArvore(arvore);

    // Imprime as estatísticas na linha de comando
    ImprimeEstatisticas();

    return 0;
}

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
            raiz = InsereNodo(palavra, sinonimo, raiz);
    }
    return raiz;
}
#else
Arvore* CarregaDicionario(FILE* dicionario, Arvore* raiz, int *ok) {
    char linha[TAMANHO_MAXIMO_LINHA];
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    char sinonimo[TAMANHO_MAXIMO_PALAVRA];

    int sinal = 0;
    while(!sinal) {
        sinal = LeLinhaDicionario(dicionario, linha, palavra, sinonimo);
        if(!sinal)
            raiz = InsereNodo(palavra, sinonimo, raiz, ok);
    }
    return raiz;
}
#endif

// Percorre as palavras do texto de entrada, salvando-as no arquivo de
// saída ou realizando as devidas substituições por sinônimos.
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

// Imprime as estatísticas ao fim da reescrita
void ImprimeEstatisticas() {
    printf("============ ESTAT%cSTICAS %s ============\n", 0xcd, TIPO_DE_ARVORE);
    printf("N%cmero de Nodos: %d\n", 0xfa, numero_de_nodos);
    printf("Altura: %d\n", altura_da_arvore);
    printf("Rota%c%ces: %d\n", 0xe7, 0xf5, numero_de_rotacoes);
    printf("Compara%c%ces: %d\n", 0xe7, 0xf5, numero_de_comparacoes);
}