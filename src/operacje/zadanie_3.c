#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

int count_words(char *buffer);

// 3) Napisz program zliczający słowa w pliku.
int main() {
    const char *file_name = "Lorem";
    const int descriptor = open(file_name, O_CREAT | O_RDWR, 0600);
    if (-1 == descriptor) {
        perror("Nie można utworzyć pliku\n");
        return 1;
    }

    char buffer[15 * 1024];
    read(descriptor, buffer, 15 * 1024);
    close(descriptor);

    const int words = count_words(buffer, 15 * 1024);
    printf("Policzyłem: %d słów\n", words);
    return 0;
}

int count_words(char *buffer) {
    int counter = 0;
    char *copy = strtok(buffer, " ");
    while (NULL != copy) {
        ++counter;
        copy = strtok(NULL, " ");
    }
    return counter;
}
