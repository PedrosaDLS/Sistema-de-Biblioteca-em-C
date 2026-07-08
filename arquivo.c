#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

static int salvarBinario(void) {
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

static int salvarTexto(void) {
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

static void carregarBinario(void) {
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

static void carregarTexto(void) {
    FILE *arq;
    char linha[100];
    int n, i;

    arq = fopen("biblioteca.txt", "r");
    if (arq == NULL) {
        return;
    }

    if (fgets(linha, sizeof(linha), arq) == NULL) {
        fclose(arq);
        return;
    }
    sscanf(linha, "%d", &n);

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
            fgets(linha, sizeof(linha), arq);
            sscanf(linha, "%d", &livros[i].codigo);

            fgets(livros[i].titulo, sizeof(livros[i].titulo), arq);
            livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

            fgets(livros[i].autor, sizeof(livros[i].autor), arq);
            livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

            fgets(linha, sizeof(linha), arq);
            sscanf(linha, "%d", &livros[i].ano);

            fgets(linha, sizeof(linha), arq);
            sscanf(linha, "%d", &livros[i].quantidade);

            total++;
        }
    }

    fclose(arq);
}

int salvarArquivo(void) {
    if (salvarBinario() != 0) {
        return 1;
    }
    if (salvarTexto() != 0) {
        return 1;
    }
    return 0;
}

void carregarArquivo(void) {
    FILE *arqBin = fopen("biblioteca.bin", "rb");

    if (arqBin != NULL) {
        fclose(arqBin);
        carregarBinario();
        return;
    }

    carregarTexto();
}
