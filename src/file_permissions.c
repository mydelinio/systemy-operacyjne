#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static const char *DIRECTORY_NAME = "testowy_katalog";
static const char *FILE_NAME = "testowy_katalog/testowy_plik";

int main() {
    if (mkdir(DIRECTORY_NAME, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        perror("Nie można utworzyć katalogu");
        return 1;
    }

    // tworzę plik z dostępami oct: 600, czyli (+rw-)
    const int descriptor = open(FILE_NAME, O_CREAT | O_RDONLY, 0600);
    if (descriptor < 0) {
        perror("Nie można utworzyć pliku\n");
        return 1;
    }

    // sprawdzam dostęp do pliku
    const int access_result = access(FILE_NAME, R_OK | W_OK);
    printf("access: %d\n", access_result);
    if (access_result == -1) {
        perror("Plik nie posiada odpowiednich dostępów\n");
        return 1;
    } else {
        printf("Plik zawiera odpowiednie permisje\n");
    }

    // sprawdzamy, czy mamy dostęp
    const int is_executable = access(FILE_NAME, X_OK);
    if (is_executable == -1) { // is not executable
        // chmod usuwa wszystkie inne dostępy poza nadanymi poniżej
        // tworzenie tej definicji jest banalnie proste
        // S_I<akcja, którą chcemy dodać><grupa permisji>
        const int status = chmod(FILE_NAME, S_IXUSR | S_IRUSR | S_IWUSR);
        if (status != -1) {
            printf("Dodano permisję pomyślnie\n");
        }
    }

    // usuwamy plik możemy także katalog
    if (remove(FILE_NAME) == -1) {
        perror("Nie można usunąć pliku\n");
        return 1;
    }

    if (remove(DIRECTORY_NAME) == -1) {
        perror("Nie można usunąć katalogu\n");
        return 1;
    }

    return 0;
}
