#ifndef AVL_H
#define AVL_H

#include <stdio.h>

#include "config.h"

#define TIPO_DE_ARVORE "AVL"

typedef struct avl_t {
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    char sinonimo[TAMANHO_MAXIMO_PALAVRA];
    int fator;
    struct avl_t *esq;
    struct avl_t *dir;
} Arvore;

Arvore* InicializaArvore();

Arvore* RotacaoSimplesDireita(Arvore *raiz);

Arvore* RotacaoDuplaDireita(Arvore* raiz);

Arvore* RotacaoSimplesEsquerda(Arvore *raiz);

Arvore* RotacaoDuplaEsquerda(Arvore *raiz);

Arvore* RotacaoDireita(Arvore *raiz , int *ok);

Arvore* RotacaoEsquerda(Arvore *raiz , int *ok);

Arvore* InsereNodo(char palavra[TAMANHO_MAXIMO_PALAVRA], char sinonimo[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz, int *ok);

int ContaNodosArvore(Arvore *raiz);

int CalculaAlturaArvore(Arvore *raiz);

Arvore* ConsultaArvore(char palavra[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz);

void DespachaBufferDeLetras(char buffer[TAMANHO_MAXIMO_PALAVRA], FILE *saida, Arvore *dicionario);

#endif