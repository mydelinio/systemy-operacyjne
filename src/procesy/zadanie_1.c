#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 1) Napisz program tworzący dwa procesy. Każdy ze stworzonych procesów powinien utworzyć proces – potomka.
// Należy wyświetlać identyfikatory procesów rodziców i potomków po każdym wywołaniu funkcji fork.
void info() {
    printf("Proces: %d ppid: %d\n", getpid(), getppid());
}

int main() {
    info();
    if (0 == fork()) {
        info();
        if (0 == fork()) {
            info();
            exit(EXIT_SUCCESS);
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
    wait(NULL);

    if (0 == fork()) {
        info();
        if (0 == fork()) {
            info();
            exit(EXIT_SUCCESS);
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    return 0;
}
