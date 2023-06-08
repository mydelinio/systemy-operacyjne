#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdlib.h>

static const int BUF_SIZE = 1024;
static const char *FIFO = "my_fifo";

int main() {
    // Usuwa istniejący plik fifo (jeśli istnieje).
    unlink(FIFO);
    // tworzę dołączenie nazwane (fifo)
    if (mkfifo(FIFO, 0666) == -1) {
        perror("Nie udało się utworzyć fifo\n");
        exit(EXIT_FAILURE);
    }

    // pobieram tekst wyżej, nad open, ponieważ to dowiązanie blokuje proces
    printf("Wprowadź jakiś tekst: ");
    char buffer[BUF_SIZE];
    fgets(buffer, BUF_SIZE, stdin);

    // otwieram dowiązanie
    const int fifo_descriptor = open(FIFO, O_WRONLY);
    if (fifo_descriptor < 0) {
        perror("Nie udało się otworzyć pliku fifo - write\n");
        exit(EXIT_FAILURE);
    }

    // zapisuje wartość wprowadzoną od użytkownika
    write(fifo_descriptor, buffer, BUF_SIZE);

    // zamykam deskryptor jak proces się odblokuje
    close(fifo_descriptor);
    return 0;
}
