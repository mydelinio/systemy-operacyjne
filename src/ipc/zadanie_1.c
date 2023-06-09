#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

// 1) Napisz dwa programy, w których jeden zapisuje do pamięci współdzielonej liczbę z zakresu od 1 do 20,
// a drugi z niej odczytuje i wyświetla napis wskazany przez użytkownika, tyle razy ile wynosi liczba z pamięci.

const short stored_number = 14;
const key_t key = 0x0000E006;

void save_to_shm();

void read_from_shm();

int main() {
    if (0 == fork()) {
        save_to_shm();
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    read_from_shm();

    return 0;
}

void save_to_shm() {
    const int shm_id = shmget(key, sizeof(short), IPC_CREAT | 0600);
    if (-1 == shm_id) {
        perror("Nie udało się utworzyć segmentu pamięci współdzielonej\n");
        exit(1);
    }

    short *address = shmat(shm_id, NULL, 0);
    if (NULL == address) {
        perror("Nie udało się pobrać adresu");
    }

    *address = stored_number;
    printf("Zapisano do pamięci współdzielonej\n");

    shmdt(NULL); // odłączmy segment
}

void read_from_shm() {
    const int shm_id = shmget(key, sizeof(short), IPC_CREAT | 0600);
    if (-1 == shm_id) {
        perror("Nie udało się utworzyć segmentu pamięci współdzielonej\n");
        exit(1);
    }

    short *address = shmat(shm_id, NULL, 0);
    if (NULL == address) {
        perror("Nie udało się pobrać adresu");
    }

    const int repeats = *address;

    shmdt(NULL); // odłączmy segment

    printf("Wprowadź tekst, zostanie on powtórzony %d razy\n", repeats);
    char buffer[1024];
    fgets(buffer, 1024, stdin);
    for (int i = 0; i < repeats; ++i) {
        printf("%d: %s", i + 1, buffer);
    }
}
