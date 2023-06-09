#include <stdio.h>
#include <pthread.h>

// 2) Napisz program tworzący 2 wątki, które zapisują odpowiednio wartości 1
// (pierwszy wątek) i 2 (drugi wątek) do tablicy o zadanym przez użytkownika rozmiarze.
// Zsynchronizuj pracę wątków tak, aby pierwsza połowa tablicy była zapisana tylko wartościami 1,
// a druga tylko wartościami 2.
const int array_size = 10;
int array[array_size];
int relative_index = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *fill_array(void *input) {
    pthread_mutex_lock(&mutex);
    const int value = *((int *) input);
    for (int i = 0; i < array_size / 2; ++i) {
        array[relative_index + i] = value;
    }
    if (relative_index == 0) {
        relative_index = 5;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    int first = 1, second = 2;
    pthread_t first_thread, second_thread;
    if (pthread_create(&first_thread, NULL, fill_array, &first)) {
        perror("Cannot create first thread");
        return 1;
    }
    if (pthread_create(&second_thread, NULL, fill_array, &second)) {
        perror("Cannot create first thread");
        return 1;
    }
    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);

    for (int i = 0; i < array_size; ++i) {
        printf("%d ", array[i]);
    }
    return 0;
}
