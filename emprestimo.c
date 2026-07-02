#include "livro.h"

int emprestarPorCodigo(int codigo) {
    int indice = buscarIndicePorCodigo(codigo);

    if (indice == -1) {
        return 1;
    }

    if (livros[indice].quantidade <= 0) {
        return 2;
    }

    livros[indice].quantidade--;
    return 0;
}

int devolverPorCodigo(int codigo) {
    int indice = buscarIndicePorCodigo(codigo);

    if (indice == -1) {
        return 1;
    }

    livros[indice].quantidade++;
    return 0;
}
