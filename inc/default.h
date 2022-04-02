#ifndef DEFAULT_H
#define DEFAULT_H

// Arquivo com definições vazias para evitar que a IDE marque erros no
// código-fonte desnecessariamente.

#define TIPO_DE_ARVORE "null"

typedef void Arvore;

Arvore* InicializaArvore();

Arvore* InsereNodo(char palavra[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz, Arvore **pt_nodo);

void ImprimeArvore(Arvore *raiz, int nivel, char lado);

Arvore* InsereParDeNodos(char palavra1[TAMANHO_MAXIMO_PALAVRA], char palavra2[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz);

int ContaNodosArvore(Arvore *raiz);

int CalculaAlturaArvore(Arvore *raiz);

Arvore* ConsultaArvore(char palavra[TAMANHO_MAXIMO_PALAVRA], Arvore *raiz);

void DespachaBufferDeLetras(char buffer[TAMANHO_MAXIMO_PALAVRA], FILE *saida, Arvore *dicionario);

#endif