#ifndef LIVRO_H
#define LIVRO_H

typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int quantidade;
} Livro;

extern Livro *livros;
extern int total;
extern int capacidade;

int buscarIndicePorCodigo(int codigo);
void formatarLivro(Livro *l, char *buffer, int tamanho);

int inserirLivro(Livro novo);
void montarListaLivros(char *buffer, int tamanho);
int buscarLivroPorCodigo(int codigo, char *buffer, int tamanho);
int buscarLivrosPorTitulo(const char *titulo, char *buffer, int tamanho);
int emprestarPorCodigo(int codigo);
int devolverPorCodigo(int codigo);
void ordenarLivrosPorTitulo(void);
void montarRelatorioIndisponiveis(char *buffer, int tamanho);

int salvarArquivo(void);
void carregarArquivo(void);
void iniciarGUI(void);

#endif
