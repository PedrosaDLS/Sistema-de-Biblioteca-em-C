#include <stdio.h>
#include <stdlib.h>
#include "livro.h"

int salvarArquivo(void) {
    FILE *arq;
    int i;

    arq = fopen("biblioteca.bin", "wb");
    if (arq == NULL) {
        return 1;
    }

    fwrite(&total, sizeof(int), 1, arq);
    for (i = 0; i < total; i++) {
        fwrite(&livros[i], sizeof(Livro), 1, arq);
    }

    fclose(arq);
    return 0;
}

void carregarArquivo(void) {
    FILE *arq;
    int n, i;

    arq = fopen("biblioteca.bin", "rb");
    if (arq == NULL) {
        return;
    }

    if (fread(&n, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        return;
    }

    if (n > 0) {
        free(livros);
        livros = malloc(n * sizeof(Livro));
        if (livros == NULL) {
            fclose(arq);
            return;
        }

        total = 0;
        capacidade = n;

        for (i = 0; i < n; i++) {
            if (fread(&livros[i], sizeof(Livro), 1, arq) != 1) {
                break;
            }
            total++;
        }
    }

    fclose(arq);
}
