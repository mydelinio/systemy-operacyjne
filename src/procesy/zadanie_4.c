#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 4) Napisz program tworzący równocześnie trzy procesy zombi.
int main() {
    for (int i = 0; i < 3; i++) {
        const pid_t zombie_pid = fork();
        if (0 == zombie_pid) {
            printf("proces zombie: %d\n", getpid());
            exit(EXIT_SUCCESS); // zabijamy dziecko
        }
    }

    sleep(20);
    return 0;
}
