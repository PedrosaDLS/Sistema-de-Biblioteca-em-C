#include <string.h>
#include "livro.h"

int buscarLivroPorCodigo(int codigo, char *buffer, int tamanho) {
    int indice = buscarIndicePorCodigo(codigo);

    if (indice == -1) {
        return 1;
    }

    formatarLivro(&livros[indice], buffer, tamanho);
    return 0;
}

int buscarLivrosPorTitulo(const char *titulo, char *buffer, int tamanho) {
    int i, encontrou = 0;
    char linha[512];

    buffer[0] = '\0';
    for (i = 0; i < total; i++) {
        if (strstr(livros[i].titulo, titulo) != NULL) {
            formatarLivro(&livros[i], linha, sizeof(linha));
            strncat(buffer, linha, tamanho - strlen(buffer) - 1);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        return 1;
    }
    return 0;
}
