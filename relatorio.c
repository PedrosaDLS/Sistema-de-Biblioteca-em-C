#include <string.h>
#include "livro.h"

void ordenarLivrosPorTitulo(void) {
    int i, j;
    Livro temp;

    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (strcmp(livros[j].titulo, livros[j + 1].titulo) > 0) {
                temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

void montarRelatorioIndisponiveis(char *buffer, int tamanho) {
    int i, encontrou = 0;
    char linha[512];

    buffer[0] = '\0';
    for (i = 0; i < total; i++) {
        if (livros[i].quantidade == 0) {
            formatarLivro(&livros[i], linha, sizeof(linha));
            strncat(buffer, linha, tamanho - strlen(buffer) - 1);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        strncpy(buffer, "Nenhum livro indisponivel.", tamanho - 1);
        buffer[tamanho - 1] = '\0';
    }
}
