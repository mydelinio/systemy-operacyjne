#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *counter_function(void *ignored) {
    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&mutex);
        ++counter;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t first_counter_thread;

    if (pthread_create(&first_counter_thread, NULL, counter_function, NULL)) {
        perror("Nie udało się stworzyć nowego wątku\n");
        return 1;
    }

    if (pthread_join(first_counter_thread, NULL)) {
        perror("Błąd podczas wywołania wątku\n");
        return 1;
    }

    pthread_t second_counter_thread;
    if (pthread_create(&second_counter_thread, NULL, counter_function, NULL)) {
        perror("Nie udało się stworzyć nowego wątku\n");
        return 1;
    }

    if (pthread_join(second_counter_thread, NULL)) {
        perror("Błąd podczas wywołania wątku\n");
        return 1;
    }

    printf("Uruchomiony program\n");
    printf("Wyliczyliśmy: %d\n", counter);
    return 0;
}
