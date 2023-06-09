#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 2) Napisz program, którego rezultatem będzie wydruk zawartości bieżącego katalogu poprzedzony
// napisem „Początek” a zakończony napisem „Koniec”
int main() {
    printf("Początek\n");
    if (0 == fork()) {
        execl("/bin/ls", "ls", NULL);
    }
    wait(NULL);
    printf("Koniec\n");
    return 0;
}
