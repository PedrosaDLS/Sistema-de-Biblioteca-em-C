#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

int salvarArquivo(void) {
    FILE *arq;
    int i;

    arq = fopen("biblioteca.txt", "w");
    if (arq == NULL) {
        return 1;
    }

    fprintf(arq, "%d\n", total);
    for (i = 0; i < total; i++) {
        fprintf(arq, "%d\n", livros[i].codigo);
        fprintf(arq, "%s\n", livros[i].titulo);
        fprintf(arq, "%s\n", livros[i].autor);
        fprintf(arq, "%d\n", livros[i].ano);
        fprintf(arq, "%d\n", livros[i].quantidade);
    }
    fclose(arq);
    return 0;
}

void carregarArquivo(void) {
    FILE *arq;
    char linha[100];
    int n, i;

    arq = fopen("biblioteca.txt", "r");
    if (arq == NULL) {
        return;
    }

    if (fgets(linha, 100, arq) == NULL) {
        fclose(arq);
        return;
    }
    sscanf(linha, "%d", &n);

    if (n > 0) {
        free(livros);
        livros = malloc(n * sizeof(Livro));
        total = 0;
        capacidade = n;

        for (i = 0; i < n; i++) {
            fgets(linha, 100, arq);
            sscanf(linha, "%d", &livros[i].codigo);

            fgets(livros[i].titulo, 100, arq);
            livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

            fgets(livros[i].autor, 100, arq);
            livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

            fgets(linha, 100, arq);
            sscanf(linha, "%d", &livros[i].ano);

            fgets(linha, 100, arq);
            sscanf(linha, "%d", &livros[i].quantidade);

            total++;
        }
    }

    fclose(arq);
}
