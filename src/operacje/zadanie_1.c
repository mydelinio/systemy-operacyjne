#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

const char *lorem = {
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
        "Donec egestas nulla vel finibus porta.\n"
        "Nam tincidunt odio nec arcu pulvinar tempor.\n"
        "Praesent et justo dictum, suscipit mi id, varius ex.\n"
        "Cras blandit turpis quis nisl rutrum, eleifend vestibulum nisl volutpat.\n"
        "Duis varius purus ac mattis eleifend.\n"
        "Etiam sit amet sem sodales, blandit lorem in, convallis sapien.\n"
        "Maecenas vitae lectus eu ligula imperdiet porta et eget turpis.\n"
        "Donec vitae lacus ac orci rutrum maximus eget sit amet dui.\n"
        "Nulla ultrices ex congue leo vestibulum, eu gravida ligula scelerisque.\n"
        "Nam venenatis nisl quis ex euismod, sed tristique tellus feugiat.\n"
        "Curabitur placerat ligula elementum facilisis viverra.\n"
        "Vestibulum convallis mi ut pharetra posuere.\n"
        "Ut eget nisl accumsan, blandit ante vitae, facilisis lacus.\n"
        "Duis tempus mauris at nunc ultrices, eget ornare eros pulvinar.\n"
};

// 1) Napisz program, który utworzy plik o nazwie „Lorem” i zapisze w nim 15 lini tekstu lorem ipsum.
int main() {
    const char *file_name = "Lorem";
    const int descriptor = open(file_name, O_CREAT | O_RDWR, 0600);
    if (-1 == descriptor) {
        perror("Nie można utworzyć pliku\n");
        return 1;
    }

    printf("buffer: %s", lorem);
    write(descriptor, lorem, strlen(lorem));
    close(descriptor);
    return 0;
}
