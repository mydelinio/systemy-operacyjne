#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    printf("Proces główny programu: %d\n", getpid());

    int status;
    const pid_t pid = fork();
    if (pid == 0) {
        sleep(5);
        exit(EXIT_SUCCESS);
    }
    printf("Mam przodka o pid: %d\n", pid);
    // bez kill, proces ubije się dopiero po 5 sekundach
    // printf zwróci nam status 100 w przypadku 1
    kill(pid, 9); // zabijamy proces wcześniej niż się zakończy
    const pid_t clone = wait(&status);
    printf("Status zakończenia procesu: %d, %x\n", pid, status);
    printf("Czy proces zwracany z wait jest ten sam co wchodzący? %d\n", (pid == clone));
    return 0;
}
