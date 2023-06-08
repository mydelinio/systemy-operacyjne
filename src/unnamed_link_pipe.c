#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Tworzy nienazwane łącze (pipe) i sprawdza, czy się powiodło
    int pd[2];
    if (0 > pipe(pd)) {
        perror("Nie udało się utworzyć nienazwanego łącza\n");
        return 1;
    }

    // Proces macierzysty
    if (0 < fork()) {
        // Zamyka odczyt z łącza
        close(pd[0]);

        // Wczytuje dane z wejścia standardowego
        char buffer[1024];
        fgets(buffer, 1024, stdin);

        // Zapisuje dane do łącza
        write(pd[1], buffer, 1024);
        printf("Zapisano: %s do łącza nienazwanego\n", buffer);

        // Zamyka zapis do łącza
        close(pd[1]);
    } else {
        // Proces potomny
        // Zamyka zapis do łącza
        close(pd[1]);

        // Odczytuje dane z łącza
        char buffer[1024];
        read(pd[0], buffer, 1024);

        // Wyświetla odczytane dane
        printf("Wyczytano: %s z łącza nienazwanego\n", buffer);

        // Zamyka odczyt z łącza
        close(pd[0]);
    }
    // Oczekuje na zakończenie procesu potomnego
    wait(NULL);

    return 0;
}
