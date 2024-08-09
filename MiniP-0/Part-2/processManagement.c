#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

int main (int argc, char *argv[]) {

    int gb = (int) getpid();
   
    int x = 25;

    int da1 = fork();

    if (da1 < 0) {
        fprintf(stderr, "first fork uncreated\n");

        exit(1);
    } 
    
    else if (da1 == 0) {
        printf("Value of the variable x in child process is %d.\n", x);
        exit(0);
    } 
    
    else {
        printf("Value of the variable x in parent process is %d.\n", x);

        wait(NULL);
    }

    int da2 = fork();
    
    if (da2 < 0) {
        fprintf(stderr, "second fork not created\n");
        exit(1);
    } 
    
    else if (da2 == 0) {
    
        char *jargs[3];
        jargs[0] = strdup("touch");         // program: touch (creates file)
        jargs[1] = strdup("newfile.txt");   // argument: file name to be created 
        jargs[2] = NULL;                    // rule

           execvp(jargs[0], jargs);

        fprintf(stderr, "execvp not able to execute\n");

         exit(1);
    } 
    
    else {
        wait(NULL);
    }

         int da2_cont = fork();

       if (da2_cont < 0) {
         
          fprintf(stderr, "second fork cont (continued) not created\n");
        exit(1);
    } 
    
    else if (da2_cont == 0) {
        int op = open("newfile.txt", O_WRONLY);
        if(op == -1) {
            printf("Error in opening file\n");
            exit(1);
        }

        
        char cc[100];
        int len = snprintf(cc, sizeof(cc), "%d", gb);
       
        write(op, cc, len);
        
        close(op);
        
        exit(0);
    }
    
     else {
        wait(NULL);
    }

    int da3 = fork();

    if (da3 < 0) {

        fprintf(stderr, "third fork uncreated\n");
        exit(1);

    } 

    else if (da3 == 0) {
        sleep(1);
        
        printf("\nMy new parent's id: %d\n", getppid());
        exit(0);
    } 

    else {

        exit(EXIT_SUCCESS);
        
        printf("\nI am old parent\n");
        
    }

    return 0;
}

