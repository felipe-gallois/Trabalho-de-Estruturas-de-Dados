#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "config.h"
#include "leitor.h"

// Retorna 1 se o caractere de entrada for caractere que compõe uma palavra.
// Senão, retorna 0.
int Letra(char caractere) {
    caractere = (char) tolower((int) caractere);
    unsigned char c = (unsigned char) caractere;
    if(c == 0x2d ||
        (c >= 0x61 && c <= 0x7a) ||
        (c >= 0xe0 && c <= 0xfc))
        return 1;
    return 0;
}

// Lê uma linha do dicionário a partir da posição no stream e
// copia as palavras para as strings destino.
// Retorna 1 se atingir fim de arquivo, senão retorna 0.
// ATENÇÃO: LEMBRAR DE HABILITAR SETLOCALE EM MAIN.
int LeLinhaDicionario(FILE *dicionario, char linha[TAMANHO_MAXIMO_LINHA],
                        char palavra[TAMANHO_MAXIMO_PALAVRA],
                        char sinonimo[TAMANHO_MAXIMO_PALAVRA]) {
    fgets(linha, TAMANHO_MAXIMO_LINHA, dicionario);

    int pos;
    for(pos = 0; pos < TAMANHO_MAXIMO_LINHA && linha[pos] != '\t' && linha[pos] != '\0'; pos++);
    strncpy(palavra, linha, pos);
    palavra[pos] = '\0';
    
    int pos2;
    for(pos2 = pos; pos2 < TAMANHO_MAXIMO_LINHA && linha[pos2] != '\n' && linha[pos2] != '\0'; pos2++);
    strncpy(sinonimo, linha+(pos+1)*sizeof(char), pos2-pos-1);
    sinonimo[pos2-pos-1] = '\0';

    if(feof(dicionario)) {
        return 1;
    } else {
        return 0;
    }
}

// Transforma todos os caracteres de uma string em lower case.
void LowerCase(char string[TAMANHO_MAXIMO_PALAVRA]) {
    int pos = 0;
    while(pos < TAMANHO_MAXIMO_PALAVRA && string[pos] != '\0') {
        string[pos] = (char) tolower((int) string[pos]);
        pos++;
    }
}

// Imprime uma string de símbolos no arquivo de saída.
void DespachaBufferDeSimbolos(char buffer[TAMANHO_BUFFER_SIMBOLOS], FILE *saida) { //TESTME
    fprintf(saida, "%s", buffer);
}