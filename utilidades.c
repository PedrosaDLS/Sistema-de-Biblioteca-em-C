#include <stdio.h>
#include "livro.h"

int buscarIndicePorCodigo(int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (livros[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void formatarLivro(Livro *l, char *buffer, int tamanho) {
    snprintf(buffer, tamanho,
        "Codigo: %d\r\nTitulo: %s\r\nAutor: %s\r\nAno: %d\r\nQuantidade: %d\r\n------------------------\r\n",
        l->codigo, l->titulo, l->autor, l->ano, l->quantidade);
}
