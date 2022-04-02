#ifndef LEITOR_H
#define LEITOR_H

int Letra(char caractere);

int LeLinhaDicionario(FILE *dicionario, char linha[TAMANHO_MAXIMO_LINHA],
                        char palavra[TAMANHO_MAXIMO_PALAVRA],
                        char sinonimo[TAMANHO_MAXIMO_PALAVRA]);

void LowerCase(char string[TAMANHO_MAXIMO_PALAVRA]);

void DespachaBufferDeSimbolos(char buffer[TAMANHO_BUFFER_SIMBOLOS], FILE *saida);

#endif