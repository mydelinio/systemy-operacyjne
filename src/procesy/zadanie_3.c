#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//3) Napisz program, którego wynikiem jest sformatowana lista procesów:
//--------początek listy-------------
//proces 1
//proces2 .....
//--------koniec listy---------------
// UWAGA: rozumiem jako ps
int main() {
    printf("--------początek listy-------------\n");
    if (0 == fork()) {
        execlp("ps", "ps", NULL);
    }
    wait(NULL);
    printf("--------koniec listy---------------\n");
    return 0;
}
