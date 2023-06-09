#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

// 2) Napisz program, który skopiuje zawartość pliku „Lorem” do innego pliku.
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

    const int copy_descriptor = open("Lorem-copy", O_CREAT | O_RDWR, 0600);
    if (-1 == copy_descriptor) {
        perror("Nie można utworzyć pliku\n");
        return 1;
    }

    write(copy_descriptor, buffer, strlen(buffer));
    close(copy_descriptor);
    return 0;
}
