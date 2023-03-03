#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int exitCode = 0;
    char **args = malloc(3*sizeof(NULL));
    args[0] = "echo";
    args[1] = "a";
    args[2] = NULL;
    pid_t pid = fork();
    if(pid == 0){
        printf("%s\n",args[0]);
        int success = execvp(args[0],args);
        if(success == -1){
            perror("command failed\n");
            exit(-1);
        }
        exit(0);
    }
    wait(&exitCode);//set lastExit based on exit of child process
    printf("exit Code: %d\n",exitCode);
}
