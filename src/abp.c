#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "leitor.h"
#include "abp.h"

extern int numero_de_comparacoes;

// Retorna o valor de ponteiro NULL para inicializar a ABP. 
Arvore* InicializaArvore() {
    return NULL;
}

// Insere um nodo na ABP com o ponteiro de sinônimo em NULL e registra o endereço do nodo adicionado em um ponteiro.
// Retorna o endereço para a nova raiz.
Arvore* InsereNodo(char palavra[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz, Arvore **pt_nodo) {
    if(raiz == NULL) {
        Arvore *novo_nodo = (Arvore*) malloc(sizeof(Arvore));
        char chave[TAMANHO_MAXIMO_PALAVRA];
        strncpy(chave, palavra, TAMANHO_MAXIMO_PALAVRA);
        LowerCase(chave);
        strncpy(novo_nodo->palavra, chave, TAMANHO_MAXIMO_PALAVRA);
        novo_nodo->esq = NULL;
        novo_nodo->dir = NULL;
        novo_nodo->sinonimo = NULL;
        *pt_nodo = novo_nodo;
        raiz = novo_nodo;
    } else {
        if(strncmp(palavra, raiz->palavra, TAMANHO_MAXIMO_PALAVRA) < 0) {
            raiz->esq = InsereNodo(palavra, raiz->esq, pt_nodo);
        } else {
            raiz->dir = InsereNodo(palavra, raiz->dir, pt_nodo);
        }
    }
    return raiz;
}

// Insere duas palavras sinônimas na Arvore e faz seus ponteiros de sinônimo apontarem um ao outro.
// Retorna o endereço para a nova raiz da árvore.
Arvore* InsereParDeNodos(char palavra1[TAMANHO_MAXIMO_PALAVRA], char palavra2[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz) {
    Arvore *nodo1, *nodo2;
    raiz = InsereNodo(palavra1, raiz, &nodo1);
    raiz = InsereNodo(palavra2, raiz, &nodo2);
    nodo1->sinonimo = nodo2;
    nodo2->sinonimo = nodo1;
    return raiz;
}

// Retorna o número de nodos em uma ABP.
int ContaNodosArvore(Arvore *raiz) {
    if(raiz == NULL)
        return 0;
    return ContaNodosArvore(raiz->esq) + ContaNodosArvore(raiz->dir) + 1;
}

// Retorna a altura de uma ABP.
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

// Procura uma palavra na ABP e retorna o endereço do nodo caso tenha sido encontrado.
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
        strncpy(buffer, endereco->sinonimo->palavra, TAMANHO_MAXIMO_PALAVRA);
    }
    fprintf(saida, "%s", buffer);
}