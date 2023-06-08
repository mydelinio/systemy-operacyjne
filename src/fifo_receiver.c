#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <stdlib.h>

static const int BUF_SIZE = 1024;
static const char *FIFO = "my_fifo";

int main() {
    // otwieram dołączenie
    const int fifo_descriptor = open(FIFO, O_RDONLY);
    if (fifo_descriptor < 0) {
        perror("Nie udało się otworzyć pliku fifo\n");
        exit(EXIT_FAILURE);
    }

    // czytam dołączenie fifo
    char buffer[BUF_SIZE];
    read(fifo_descriptor, buffer, BUF_SIZE);
    printf("Przeczytano z nazwanej pamięci współdzielonej: %s\n", buffer);

    // zamykam deskryptor dołączenia
    close(fifo_descriptor);

    // usuwam dołączenie
    unlink(FIFO);
    return 0;
}