#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 2) Napisz program, który utworzy dwóch potomków. Jeden z nich wyświetli ścieżkę
// bieżącego katalogu, drugi wyświetli listę procesów. Zadanie należy wykonać z użyciem funkcji exec.
int main() {
    printf("Znajdujesz się w katalogu: \n");
    if (0 == fork()) {
        execlp("pwd", "pwd", NULL);
    }
    wait(NULL);
    printf("\nAktualna lista procesów: \n");
    if (0 == fork()) {
        execlp("ps", "ps", NULL);
    }
    wait(NULL);
    return 0;
}
