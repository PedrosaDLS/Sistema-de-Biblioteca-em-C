#include <locale.h>
#include <windows.h>
#include "livro.h"

static void configurarAcentos(void) {
    setlocale(LC_ALL, "");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");
}

int main(void) {
    configurarAcentos();
    carregarArquivo();
    menu();
    return 0;
}
