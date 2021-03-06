#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "leitor.h"
#include "avl.h"

extern int numero_de_rotacoes;
extern int numero_de_comparacoes;

// Retorna o valor de ponteiro NULL para inicializar a AVL. 
Arvore* InicializaArvore() {
    return NULL;
}

// Realiza rotação simples à direita de uma dada subárvore.
Arvore* RotacaoSimplesDireita(Arvore *raiz) {
    Arvore *aux;
    aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->fator = 0;
    raiz = aux;
    return raiz;
}

// Realiza rotação dupla à direita de uma dada subárvore.
Arvore* RotacaoDuplaDireita(Arvore* raiz) {
    Arvore *aux1, *aux2;
    aux1 = raiz->esq;
    aux2 = aux1->dir;
    aux1->dir = aux2->esq;
    aux2->esq = aux1;
    raiz->esq = aux2->dir;
    aux2->dir = raiz;
    if(aux2->fator == 1)
        raiz->fator = -1;
    else
        raiz->fator = 0;
    
    if(aux2->fator == -1)
        aux1->fator = 1;
    else
        aux1->fator = 0;
    raiz = aux2;
    return raiz;
}

// Realiza rotação dupla à esquerda de uma dada subárvore.
Arvore* RotacaoSimplesEsquerda(Arvore *raiz) {
    Arvore *aux;
    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->fator = 0;
    raiz = aux;
    return raiz;
}

// Realiza rotação dupla à esquerda de uma dada subárvore.
Arvore* RotacaoDuplaEsquerda(Arvore *raiz) {
    Arvore *aux1, *aux2;
    aux1 = raiz->dir;
    aux2 = aux1->esq;
    aux1->esq = aux2->dir;
    aux2->dir = aux1;
    raiz->dir = aux2->esq;
    aux2->esq = raiz;
    if(aux2->fator == -1)
        raiz->fator = 1;
    else
        raiz->fator = 0;

    if(aux2->fator == 1)
        aux1->fator = -1;
    else
        aux1->fator = 0;
    raiz = aux2;
    return raiz;
}

// Realiza rotação à direita em uma AVL e decide se fará rotação simples ou dupla.
Arvore* RotacaoDireita(Arvore *raiz , int *ok) {
    Arvore *aux;
    aux = raiz->esq;
    if(aux->fator == 1) {
        raiz = RotacaoSimplesDireita(raiz);
    } else {
        raiz = RotacaoDuplaDireita(raiz);
    }
    raiz->fator = 0;
    *ok = 0;
    numero_de_rotacoes++;
    return raiz;
}

// Realiza rotação à esquerda em uma AVL e decide se fará rotação simples ou dupla.
Arvore* RotacaoEsquerda(Arvore *raiz , int *ok) {
    Arvore *aux;
    aux = raiz->dir;
    if(aux->fator == -1) {
        raiz = RotacaoSimplesEsquerda(raiz);
    } else {
        raiz = RotacaoDuplaEsquerda(raiz);
    }
    raiz->fator = 0;
    *ok = 0;
    numero_de_rotacoes++;
    return raiz;
}

// Insere um nodo na AVL com a palavra e seu sinônimo.
// Retorna o endereço para a nova raiz.
Arvore* InsereNodo(char palavra[TAMANHO_MAXIMO_PALAVRA], char sinonimo[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz, int *ok) {
    if(raiz == NULL) {
        raiz = (Arvore*) malloc(sizeof(Arvore));
        strncpy(raiz->palavra, palavra, TAMANHO_MAXIMO_PALAVRA);
        LowerCase(raiz->palavra);
        strncpy(raiz->sinonimo, sinonimo, TAMANHO_MAXIMO_PALAVRA);
        LowerCase(raiz->sinonimo);
        raiz->esq = NULL;
        raiz->dir = NULL;
        raiz->fator = 0;
        *ok = 1;
    } else if(strncmp(palavra, raiz->palavra, TAMANHO_MAXIMO_PALAVRA) < 0) {
        raiz->esq = InsereNodo(palavra, sinonimo, raiz->esq, ok);
        if(*ok) {
            switch(raiz->fator) {
                case -1:
                raiz->fator = 0;
                *ok = 0;
                break;
                case 0:
                raiz->fator = 1;
                break;
                case 1:
                raiz = RotacaoDireita(raiz, ok);
                break;
            }
        }
    } else {
        raiz->dir = InsereNodo(palavra, sinonimo, raiz->dir, ok);
        if(*ok) {
            switch (raiz->fator) {
                case 1:
                raiz->fator = 0;
                *ok = 0;
                break;
                case 0:
                raiz->fator = -1;
                break;
                case -1:
                raiz = RotacaoEsquerda(raiz, ok);
                break;
            }
        }
    }
    return raiz;
}

// Retorna o número de nodos em uma AVL.
int ContaNodosArvore(Arvore *raiz) {
    if(raiz == NULL)
        return 0;
    return ContaNodosArvore(raiz->esq) + ContaNodosArvore(raiz->dir) + 1;
}

// Retorna a altura de uma AVL.
int CalculaAlturaArvore(Arvore *raiz) {
    if(raiz == NULL)
        return 0;
    else {
        int alt_esq = CalculaAlturaArvore(raiz->esq);
        int alt_dir = CalculaAlturaArvore(raiz->dir);
        if(alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}

// Procura uma palavra na AVL e retorna o endereço do nodo caso tenha sido encontrado.
// Se não houver correspondente, retorna NULL.
Arvore* ConsultaArvore(char palavra[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz) {
    while(raiz != NULL) {
        numero_de_comparacoes++;
        if(strcmp(raiz->palavra, palavra) == 0) {
            numero_de_comparacoes++;
            return raiz;
        }
        else {
            numero_de_comparacoes++;
            if(strcmp(raiz->palavra, palavra) > 0)
                raiz = raiz->esq;
            else
                raiz = raiz->dir;
        }
    }
    return NULL;
}

// Imprime uma string de letras no arquivo de saída após consultar se é palavra do dicionário e
// realizar as devidas alterações.
void DespachaBufferDeLetras(char buffer[TAMANHO_MAXIMO_PALAVRA], FILE *saida, Arvore *dicionario) {
    LowerCase(buffer);
    Arvore *endereco = ConsultaArvore(buffer, dicionario);
    if(endereco != NULL) {
        strncpy(buffer, endereco->sinonimo, TAMANHO_MAXIMO_PALAVRA);
    }
    fprintf(saida, "%s", buffer);
}