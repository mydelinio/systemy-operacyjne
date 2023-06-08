#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

/*
 *  IPC_CREAT       001000           Create entry if key does not exist
 *  IPC_EXCL        002000           Fail if key exists
 *  IPC_NOWAIT      004000           Error if request must wait
 *
 * Keys
 *  IPC_PRIVATE     ((key_t) 0)       Private key
 *
 * Control commands
 *  IPC_RMID        0                Remove identifier
 *  IPC_SET         1                Set options
 *  IPC_STAT        2                Get options
*/
int main() {
    // dobieramy adres pamięci, w której stworzymy segment
    const key_t shm_key = 0x0000B0E1;

    // podłączmy segment pamięci, mode IPC_CREAT pozwala nam na jego stworzenie
    const int shm_id = shmget(shm_key, sizeof(int), IPC_CREAT | 0600);
    if (-1 == shm_id) {
        perror("Nie udało się utworzyć segmentu pamięci współdzielonej\n");
        return 1;
    }

    // bierzemy adres pamięci, który będziemy modyfikować
    int *stored_address = shmat(shm_id, NULL, 0);
    if (NULL == stored_address) {
        perror("Nie udało się pobrać adresu pamięci dla segmentu pamięci współdzielonej\n");
        return 1;
    }

    // zapiszmy wartość do pamięci
    const int value = 12;
    *stored_address = value;

    shmdt(NULL); // odłączmy segment

    // powtarzamy otarcie to tego samego segmentu
    stored_address = shmat(shm_id, NULL, 0);
    if (NULL == stored_address) {
        perror("Nie udało się pobrać adresu pamięci dla segmentu pamięci współdzielonej\n");
        return 1;
    }

    // czytamy zachowaną wartość
    const int stored_value = *stored_address;
    printf("Zachowana wartość to: %d\n", stored_value);

    shmdt(NULL); // odłączamy
    system("ipcrm -M 0x0000B0E1"); // usuwamy segment pamięci
    printf("Usunięto segment pamięci współdzielonej\n");
    return 0;
}
