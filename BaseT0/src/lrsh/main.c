
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

int main(int argc, char const *argv[]) {

    // Bucle para mantener la shell
    while (1) { 

      // recibir input
        char** input = read_user_input();  
        
        if (input[0] == NULL) {  
            continue;
        }

        // manejar comando hello

        if (strcmp(input[0], "hello") == 0) { 
            pid_t pid = fork();  
            
            if (pid < 0) {  
                perror("Error");
                exit(1);
            } else if (pid == 0) { 
                printf("Hello World!\n");
                exit(0);  
            } else { 

        // Esperar a que el proceso hijo termine
                waitpid(pid, NULL, 0);  
            }
        } else {
            printf("Comando no reconocido: %s\n", input[0]);
        }

        // Liberar memoria

        free_user_input(input);  
    }

    return 0;
}


