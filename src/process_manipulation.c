#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * "S" - proces w stanie działającym (running),
 * "R" - proces czekający na wykonanie (runnable),
 * "T" - proces zatrzymany (stopped),
 * "Z" - proces zombie (zombie).
 * Oznaczenie "S+" oznacza, że proces jest w stanie działającym i monitorowany w trybie szczegółowym.
 *
 * Aby zrobić proces zombie:
 * - Pozwalamy, aby dziecko jak najszybciej umarło.
 * - W ciągu tych 30 sekund dziecko jest zombi, ponieważ jest martwe,
 *      ale jeszcze nie zostało odebrane przez waitpid.
 *      Użyj polecenia "ps", aby zobaczyć je na liście procesów w tym czasie.
 * - Jeśli nie odebraliśmy dziecka przed zakończeniem działania programu,
 *      zostanie ono albo usunięte przez system operacyjny, albo odebrane przez proces init,
 *      gdy zostanie mu przypisane nowego rodzica.
 */
int main() {
    printf("Proces główny programu: %d\n", getpid());

    // proces czekający na obsłużenie (proces zombie)
    const pid_t zombie_pid = fork();
    if (0 == zombie_pid) {
        printf("proces zombie: %d\n", getpid());
        exit(EXIT_SUCCESS); // zabijamy dziecko
    }

    // czekamy 10 sekund, aby wymusić czekanie na dalsze akcje
    sleep(10);

    if (0 == fork()) {
        // Proces adoptowany to taki który nie zostanie obsłużony przez proces główny,
        // ponieważ on nie istnieje — przeskakuje na proces macierzysty (pid: 1)
        printf("proces adoptowany: %d\n", getpid());
        sleep(5);
        exit(EXIT_SUCCESS);
    }

    printf("Kontynuacja pracy głównego programu... \n");

    return 0;
}
