#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

const key_t key = 0x0000E006;

int main() {
    const int shm_id = shmget(key, sizeof(short), IPC_CREAT | 0600);
    if (-1 == shm_id) {
        perror("Nie udało się utworzyć segmentu pamięci współdzielonej\n");
        exit(1);
    }

    char *address = shmat(shm_id, NULL, 0);
    if (NULL == address) {
        perror("Nie udało się pobrać adresu");
    }

    char buffer[1024];
    printf("Podaj wiadomość:\n");
    fgets(buffer, 1024, stdin);

    strncpy(address, buffer, strlen(buffer));
    printf("Zapisano\n");

    return 0;
}
