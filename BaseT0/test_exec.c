#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Inicio del proceso. PID: %d\n", getpid());

    if (argc > 1) {
        printf("Argumentos recibidos:\n");
        for (int i = 1; i < argc; i++) {
            printf("  Argumento %d: %s\n", i, argv[i]);
        }
    }

    printf("Simulando tarea de 5 seg sleep...\n");
    sleep(5);

    printf("Proceso de prueba finalizado. PID: %d\n", getpid());
    return 0;
}
