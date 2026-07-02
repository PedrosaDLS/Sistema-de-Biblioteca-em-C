#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

#define ID_CADASTRAR 1
#define ID_LISTAR 2
#define ID_BUSCAR_CODIGO 3
#define ID_BUSCAR_TITULO 4
#define ID_EMPRESTAR 5
#define ID_DEVOLVER 6
#define ID_ORDENAR 7
#define ID_INDISPONIVEIS 8
#define ID_SALVAR 9

static HINSTANCE inst;
static char bufferSaida[8192];

static HWND hwndCodigo, hwndTitulo, hwndAutor, hwndAno, hwndQuantidade;
static HWND hwndCodigoAcao, hwndBuscaTitulo, hwndSaida, hwndMensagem;

static void criarLabel(HWND pai, const char *texto, int x, int y, int w, int h) {
    CreateWindowA("STATIC", texto, WS_CHILD | WS_VISIBLE, x, y, w, h, pai, NULL, inst, NULL);
}

static HWND criarCampo(HWND pai, int x, int y, int w, int h, int somenteNumero) {
    DWORD estilo = WS_CHILD | WS_VISIBLE | WS_BORDER;
    if (somenteNumero) {
        estilo |= ES_NUMBER;
    }
    return CreateWindowA("EDIT", "", estilo, x, y, w, h, pai, NULL, inst, NULL);
}

static void criarBotao(HWND pai, const char *texto, int id, int x, int y, int w, int h) {
    CreateWindowA("BUTTON", texto, WS_CHILD | WS_VISIBLE, x, y, w, h, pai, (HMENU)(INT_PTR)id, inst, NULL);
}

static int lerInt(HWND campo) {
    char texto[32];
    GetWindowTextA(campo, texto, sizeof(texto));
    return atoi(texto);
}

static void lerTexto(HWND campo, char *destino, int tamanho) {
    GetWindowTextA(campo, destino, tamanho);
}

static void mostrarMensagem(const char *texto) {
    SetWindowTextA(hwndMensagem, texto);
}

static void mostrarResultado(const char *texto, const char *mensagem) {
    SetWindowTextA(hwndSaida, texto);
    mostrarMensagem(mensagem);
}

static Livro lerLivroDoFormulario(void) {
    Livro livro;
    livro.codigo = lerInt(hwndCodigo);
    lerTexto(hwndTitulo, livro.titulo, sizeof(livro.titulo));
    lerTexto(hwndAutor, livro.autor, sizeof(livro.autor));
    livro.ano = lerInt(hwndAno);
    livro.quantidade = lerInt(hwndQuantidade);
    return livro;
}

static void tratarBotao(int id) {
    Livro livro;
    char titulo[100];
    int codigo;
    int resultado;

    switch (id) {
        case ID_CADASTRAR:
            livro = lerLivroDoFormulario();
            resultado = inserirLivro(livro);
            if (resultado == 1) {
                mostrarMensagem("Codigo ja cadastrado.");
            } else if (resultado == 2) {
                mostrarMensagem("Falha na alocacao de memoria.");
            } else {
                mostrarMensagem("Livro cadastrado.");
            }
            break;

        case ID_LISTAR:
            montarListaLivros(bufferSaida, sizeof(bufferSaida));
            mostrarResultado(bufferSaida, "Lista atualizada.");
            break;

        case ID_BUSCAR_CODIGO:
            codigo = lerInt(hwndCodigoAcao);
            if (buscarLivroPorCodigo(codigo, bufferSaida, sizeof(bufferSaida)) == 0) {
                mostrarResultado(bufferSaida, "Livro encontrado.");
            } else {
                mostrarMensagem("Livro nao encontrado.");
            }
            break;

        case ID_BUSCAR_TITULO:
            lerTexto(hwndBuscaTitulo, titulo, sizeof(titulo));
            if (buscarLivrosPorTitulo(titulo, bufferSaida, sizeof(bufferSaida)) == 0) {
                mostrarResultado(bufferSaida, "Busca concluida.");
            } else {
                mostrarMensagem("Livro nao encontrado.");
            }
            break;

        case ID_EMPRESTAR:
            codigo = lerInt(hwndCodigoAcao);
            resultado = emprestarPorCodigo(codigo);
            if (resultado == 1) {
                mostrarMensagem("Livro nao encontrado.");
            } else if (resultado == 2) {
                mostrarMensagem("Livro indisponivel.");
            } else {
                mostrarMensagem("Emprestimo realizado.");
            }
            break;

        case ID_DEVOLVER:
            codigo = lerInt(hwndCodigoAcao);
            if (devolverPorCodigo(codigo) == 1) {
                mostrarMensagem("Livro nao encontrado.");
            } else {
                mostrarMensagem("Devolucao realizada.");
            }
            break;

        case ID_ORDENAR:
            ordenarLivrosPorTitulo();
            montarListaLivros(bufferSaida, sizeof(bufferSaida));
            mostrarResultado(bufferSaida, "Livros ordenados.");
            break;

        case ID_INDISPONIVEIS:
            montarRelatorioIndisponiveis(bufferSaida, sizeof(bufferSaida));
            mostrarResultado(bufferSaida, "Relatorio gerado.");
            break;

        case ID_SALVAR:
            if (salvarArquivo() == 0) {
                mostrarMensagem("Dados salvos.");
            } else {
                mostrarMensagem("Erro ao salvar.");
            }
            break;
    }
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_COMMAND) {
        tratarBotao(LOWORD(wparam));
        return 0;
    }
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

static void criarInterface(HWND janela) {
    criarLabel(janela, "Codigo:", 10, 10, 60, 20);
    hwndCodigo = criarCampo(janela, 75, 8, 80, 22, 1);
    criarLabel(janela, "Ano:", 170, 10, 40, 20);
    hwndAno = criarCampo(janela, 215, 8, 80, 22, 1);

    criarLabel(janela, "Titulo:", 10, 38, 60, 20);
    hwndTitulo = criarCampo(janela, 75, 36, 420, 22, 0);
    criarLabel(janela, "Autor:", 10, 66, 60, 20);
    hwndAutor = criarCampo(janela, 75, 64, 420, 22, 0);
    criarLabel(janela, "Quantidade:", 10, 94, 70, 20);
    hwndQuantidade = criarCampo(janela, 85, 92, 80, 22, 1);

    criarBotao(janela, "Cadastrar", ID_CADASTRAR, 10, 125, 90, 28);
    criarBotao(janela, "Listar", ID_LISTAR, 105, 125, 90, 28);
    criarBotao(janela, "Ordenar", ID_ORDENAR, 200, 125, 90, 28);
    criarBotao(janela, "Indisponiveis", ID_INDISPONIVEIS, 295, 125, 100, 28);

    criarLabel(janela, "Codigo acao:", 10, 163, 80, 20);
    hwndCodigoAcao = criarCampo(janela, 95, 161, 80, 22, 1);
    criarBotao(janela, "Buscar Codigo", ID_BUSCAR_CODIGO, 185, 159, 100, 28);
    criarBotao(janela, "Emprestar", ID_EMPRESTAR, 290, 159, 90, 28);
    criarBotao(janela, "Devolver", ID_DEVOLVER, 385, 159, 90, 28);
    criarBotao(janela, "Salvar", ID_SALVAR, 480, 159, 70, 28);

    criarLabel(janela, "Busca titulo:", 10, 197, 80, 20);
    hwndBuscaTitulo = criarCampo(janela, 95, 195, 300, 22, 0);
    criarBotao(janela, "Buscar Titulo", ID_BUSCAR_TITULO, 405, 193, 100, 28);

    criarLabel(janela, "Resultado:", 10, 228, 80, 20);
    hwndSaida = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER |
        ES_MULTILINE | ES_READONLY | WS_VSCROLL,
        10, 250, 540, 220, janela, NULL, inst, NULL);
    hwndMensagem = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE,
        10, 478, 540, 20, janela, NULL, inst, NULL);
}

void iniciarGUI(void) {
    WNDCLASSA classe;
    HWND janela;
    MSG msg;

    inst = GetModuleHandle(NULL);
    memset(&classe, 0, sizeof(classe));
    classe.lpfnWndProc = WindowProc;
    classe.hInstance = inst;
    classe.hCursor = LoadCursor(NULL, IDC_ARROW);
    classe.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    classe.lpszClassName = "BibliotecaWin";
    RegisterClassA(&classe);

    janela = CreateWindowA("BibliotecaWin", "Sistema de Biblioteca",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 580, 540,
        NULL, NULL, inst, NULL);

    criarInterface(janela);
    ShowWindow(janela, SW_SHOW);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    salvarArquivo();
    free(livros);
}
