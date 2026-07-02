#include <stdlib.h>
#include <string.h>
#include "livro.h"

Livro *livros = NULL;
int total = 0;
int capacidade = 0;

int inserirLivro(Livro novo) {
    if (buscarIndicePorCodigo(novo.codigo) != -1) {
        return 1;
    }

    if (total == capacidade) {
        int novaCap = capacidade == 0 ? 2 : capacidade * 2;
        Livro *temp = realloc(livros, novaCap * sizeof(Livro));
        if (temp == NULL) {
            return 2;
        }
        livros = temp;
        capacidade = novaCap;
    }

    livros[total] = novo;
    total++;
    return 0;
}

void montarListaLivros(char *buffer, int tamanho) {
    int i;
    char linha[512];

    buffer[0] = '\0';
    if (total == 0) {
        strncpy(buffer, "Nenhum livro cadastrado.", tamanho - 1);
        buffer[tamanho - 1] = '\0';
        return;
    }

    for (i = 0; i < total; i++) {
        formatarLivro(&livros[i], linha, sizeof(linha));
        strncat(buffer, linha, tamanho - strlen(buffer) - 1);
    }
}
