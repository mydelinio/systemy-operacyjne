#include <stdio.h>
#include <pthread.h>

// 1) Stwórz 2 wątki, które będą jako swój parametr pobierały dowolną liczbę typu int i
// zwracały jej podwojoną wartość.
void *value_times_two(void *input) {
    const int value = *((int *) input);
    printf("doubled value: %d\n", value * 2);
    return NULL;
}

int main() {
    int first = 3, second = 6;
    pthread_t first_thread, second_thread;
    if (pthread_create(&first_thread, NULL, value_times_two, &first)) {
        perror("Cannot create first thread");
        return 1;
    }
    if (pthread_create(&second_thread, NULL, value_times_two, &second)) {
        perror("Cannot create first thread");
        return 1;
    }
    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);
    return 0;
}
