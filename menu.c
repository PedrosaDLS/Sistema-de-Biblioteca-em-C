#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

static void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void pausar(void) {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}

static void limparTela(void) {
    system("cls");
}

static void acaoCadastrar(void) {
    Livro livro;
    int resultado;

    limparTela();
    printf("\n--- Cadastrar Livro ---\n\n");

    printf("Codigo: ");
    scanf("%d", &livro.codigo);
    limparBuffer();

    printf("Titulo: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &livro.ano);

    printf("Quantidade: ");
    scanf("%d", &livro.quantidade);
    limparBuffer();

    resultado = inserirLivro(livro);

    limparTela();
    printf("\n--- Resultado ---\n\n");
    if (resultado == 1) {
        printf("Codigo ja cadastrado.\n");
    } else if (resultado == 2) {
        printf("Falha na alocacao de memoria.\n");
    } else {
        printf("Livro cadastrado.\n");
    }
    pausar();
}

static void acaoListar(void) {
    char buffer[8192];

    limparTela();
    printf("\n--- Lista de Livros ---\n\n");
    montarListaLivros(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    pausar();
}

static void acaoBuscarCodigo(void) {
    int codigo;
    char buffer[8192];
    int resultado;

    limparTela();
    printf("\n--- Buscar por Codigo ---\n\n");
    printf("Codigo: ");
    scanf("%d", &codigo);
    limparBuffer();

    resultado = buscarLivroPorCodigo(codigo, buffer, sizeof(buffer));

    limparTela();
    printf("\n--- Resultado ---\n\n");
    if (resultado == 0) {
        printf("%s\n", buffer);
    } else {
        printf("Livro nao encontrado.\n");
    }
    pausar();
}

static void acaoBuscarTitulo(void) {
    char titulo[100];
    char buffer[8192];
    int resultado;

    limparTela();
    printf("\n--- Buscar por Titulo ---\n\n");
    printf("Titulo: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    resultado = buscarLivrosPorTitulo(titulo, buffer, sizeof(buffer));

    limparTela();
    printf("\n--- Resultado ---\n\n");
    if (resultado == 0) {
        printf("%s\n", buffer);
    } else {
        printf("Livro nao encontrado.\n");
    }
    pausar();
}

static void acaoEmprestar(void) {
    int codigo;
    int resultado;

    limparTela();
    printf("\n--- Emprestar Livro ---\n\n");
    printf("Codigo: ");
    scanf("%d", &codigo);
    limparBuffer();

    resultado = emprestarPorCodigo(codigo);

    limparTela();
    printf("\n--- Resultado ---\n\n");
    if (resultado == 1) {
        printf("Livro nao encontrado.\n");
    } else if (resultado == 2) {
        printf("Livro indisponivel.\n");
    } else {
        printf("Emprestimo realizado.\n");
    }
    pausar();
}

static void acaoDevolver(void) {
    int codigo;
    int resultado;

    limparTela();
    printf("\n--- Devolver Livro ---\n\n");
    printf("Codigo: ");
    scanf("%d", &codigo);
    limparBuffer();

    resultado = devolverPorCodigo(codigo);

    limparTela();
    printf("\n--- Resultado ---\n\n");
    if (resultado == 1) {
        printf("Livro nao encontrado.\n");
    } else {
        printf("Devolucao realizada.\n");
    }
    pausar();
}

static void acaoIndisponiveis(void) {
    char buffer[8192];

    limparTela();
    printf("\n--- Livros Indisponiveis ---\n\n");
    montarRelatorioIndisponiveis(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    pausar();
}

static void acaoOrdenar(void) {
    limparTela();
    printf("\n--- Ordenar por Titulo ---\n\n");
    ordenarLivrosPorTitulo();
    printf("Livros ordenados.\n");
    pausar();
}

static void acaoSalvar(void) {
    limparTela();
    printf("\n--- Salvar Dados ---\n\n");
    if (salvarArquivo() == 0) {
        printf("Dados salvos.\n");
    } else {
        printf("Erro ao salvar.\n");
    }
    pausar();
}

void menu(void) {
    int opcao;

    do {
        limparTela();
        printf("\n--- Sistema de Biblioteca ---\n\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar por codigo\n");
        printf("4 - Buscar por titulo\n");
        printf("5 - Emprestar livro\n");
        printf("6 - Devolver livro\n");
        printf("7 - Relatorio de indisponiveis\n");
        printf("8 - Ordenar por titulo\n");
        printf("9 - Salvar dados\n");
        printf("0 - Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: acaoCadastrar(); break;
            case 2: acaoListar(); break;
            case 3: acaoBuscarCodigo(); break;
            case 4: acaoBuscarTitulo(); break;
            case 5: acaoEmprestar(); break;
            case 6: acaoDevolver(); break;
            case 7: acaoIndisponiveis(); break;
            case 8: acaoOrdenar(); break;
            case 9: acaoSalvar(); break;
            case 0:
                limparTela();
                printf("\nEncerrando...\n");
                salvarArquivo();
                free(livros);
                break;
            default:
                limparTela();
                printf("\nOpcao invalida.\n");
                pausar();
        }
    } while (opcao != 0);
}
