#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TOK_BUFSIZE 64
#define DELIMITERS " \n\t\r\a"
char *read_line(void)
{
    ssize_t bufsize = 0; 
    char *line = NULL;
    
    if (getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)) {
        
        exit(EXIT_SUCCESS);
        } else  {
        perror("readline");
        exit(EXIT_FAILURE);
        }
    }
    
    return line;
}
int process_fork_and_execute_deneme(char **args){
    pid_t pid, pid_w;
    pid = fork();
    if(pid == 0){
        //cocuk proses
        if(execvp(args[0],args) == -1){
            perror("execute hatasi");
        }
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("forklama hatasi");
    }
    else{
        //parent proses
        wait(NULL); //cocugun tamamlanmasini bekle
    }
    
    return 1; 
}
char** space_parse(char* line){
    int buf_size = TOK_BUFSIZE;
    int position = 0;
    char** args = malloc(sizeof(char*) * buf_size);
    char delimiter[] = DELIMITERS;

    if (!args) {
        perror("allocation error\n");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(line,delimiter);
    
    while (token != NULL) {
        args[position] = token;
        position++;

        if(position >= buf_size){
            //daha fazla alan allocate et
            buf_size += TOK_BUFSIZE;
            args = realloc(args, buf_size*sizeof(char*));
            if(!args){
                perror("allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL,delimiter);
    }
    
    args[position] = NULL;
    return args;
}
int main_loop(){
    char* line;
    char** args;
    int status;
    do
    {
        printf("> ");
        fflush(stdout);
        line = read_line();
        args = space_parse(line);
        status = process_fork_and_execute_deneme(args);
        free(line);
        free(args);
    } while (status);
    
    return 1;
}
int main(int argc, char **argv)
{
    //char test_cmd[] = "sh -c echo hello";
    //process_fork_and_execute_deneme(space_parse(test_cmd));
    main_loop();
    return EXIT_SUCCESS;
}
