#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "livro.h"

static void configurarAcentos(void) {
    setlocale(LC_ALL, "");
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");
#endif
}

int main(void) {
    configurarAcentos();
    carregarArquivo();
    menu();
    return 0;
}
