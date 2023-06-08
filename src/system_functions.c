#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * W języku C mamy kilka głównych metod do wykonywania function systemowych (bash).
 *
 * Jednym z nich jest `excel`.
 * ('p' oznacza, że nie musimy dorzucać dodatkowo pełnej ścieżki do skryptu).
 * - excel lub excelp -- `int excel(char* path, char* arg0, ... char* argn, char* null)`
 * - execv lub execvp -- `int execv( const char *path, char *const argv[])`
 * UWAGA!:
 * - każda z powyższych funkcji po uruchomieniu zakończy działanie procesu.
 * - każda z funkcji na końcu musi mieć NULL (wtedy wiemy, że kończymy argumenty)
 *
 * Należy także wspomnieć o funkcji — system. Skrypt wywołany przy użyciu tej funkcji nie zakończy programu.
 */
int main() {
    printf("Proces główny programu: %d\n", getpid());

    printf("Przykładowe użyciu funkcji excel lub excelp\n");
    // Tworzę nowy proces, aby móc go bezkarcie zabić i nie zakończyć programu.
    // Użycie execv jest analogiczne, ale przekazujemy tablicę argumentów
    const pid_t excel_pid = fork();
    if (0 == excel_pid) {
//        execl("/bin/ls", "ls", "-lha", NULL);
        execlp("ls", "ls", "-lha", NULL);
        printf("Ta wiadomość nie powinna się wyświetlić\n");
    }
    wait(NULL);

    printf("Miałem proces o pid: %d\n", excel_pid);
    system("ls -lha | wc -l");
    return 0;
}
