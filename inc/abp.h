#ifndef ABP_H
#define ABP_H

#include <stdio.h>

#include "config.h"

#define TIPO_DE_ARVORE "ABP"

typedef struct abp_t {
    char palavra[TAMANHO_MAXIMO_PALAVRA];
    char sinonimo[TAMANHO_MAXIMO_PALAVRA];
    struct abp_t *esq;
    struct abp_t *dir;
} Arvore;

Arvore* InicializaArvore();

Arvore* InsereNodo(char palavra[TAMANHO_MAXIMO_PALAVRA], char sinonimo[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz);

int ContaNodosArvore(Arvore *raiz);

int CalculaAlturaArvore(Arvore *raiz);

Arvore* ConsultaArvore(char palavra[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz);

void DespachaBufferDeLetras(char buffer[TAMANHO_MAXIMO_PALAVRA], FILE *saida, Arvore *dicionario);

#endif