
// #include <stdio.h>
// #include <stdlib.h>
// #include "../input_manager/manager.h"

// int main(int argc, char const *argv[])
// {
//   char** input = read_user_input();
//   printf("%s\n", input[0]);
//   free_user_input(input);
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../input_manager/manager.h"

#define TRUE 1

int main(int argc, char const *argv[]) {
    int status;

    while (TRUE) { 
      // Mostrar el prompt
        printf("shell> ");  
        char** input = read_user_input(); 

        if (input[0] == NULL) {  
            free_user_input(input);
            continue;
        }

        pid_t pid = fork();  

        if (pid < 0) {  
            perror("Error al crear el proceso");
            free_user_input(input);
            exit(1);
        } else if (pid == 0) {  
            if (strcmp(input[0], "hello") == 0) {
                printf("Hello World!\n");
            } else {
                printf("Comando no reconocido: %s\n", input[0]);
            }
            free_user_input(input);
            exit(0);  // Terminar el proceso hijo
        } else {  // Código del proceso padre
            waitpid(pid, &status, 0);  // Esperar a que el proceso hijo termine
        }

        free_user_input(input);  // Liberar la memoria de la entrada del usuario
    }

    return 0;
}


