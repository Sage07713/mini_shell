#include <stdio.h>
#include <string.h>
#include <process.h>
#include <direct.h>
#define MAX_INPUT 1024
#include <fcntl.h>

int main() {
    char input[MAX_INPUT];
   const char *args[64];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;
        }

        // remove the newline
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0') {
            i++;
        }
        input[i] = '\0';

     /*   char *token;
        token =strtok(input, " ");
        while(token!=NULL){
            printf("Token: %s\n",token);
            token =strtok(NULL, " ");
        }*/

      //  printf("You typed: %s\n", input);
      char *pipe_pos = strchr(input,'|');
      if(pipe_pos!=NULL){
        *pipe_pos='\0';
        char *cmd1= input;
        char *cmd2=pipe_pos+1;

         const char *args1[64];
       int j = 0;
        char *token = strtok(cmd1, " ");
        while (token != NULL) {
            args1[j] = token;
            j++;
            token = strtok(NULL, " ");
        }
        args1[j] = NULL; 

         const char *args2[64];
        j = 0;
        token = strtok(cmd2, " ");
        while (token != NULL) {
            args2[j] = token;
            j++;
            token = strtok(NULL, " ");
        }
        args2[j] = NULL; 

           // create pipe
            int fd[2];
            _pipe(fd, 1024, O_BINARY);

            // save original stdout and stdin
            int saved_stdout = _dup(1);
            int saved_stdin  = _dup(0);

            // run cmd1 with output going into pipe
            _dup2(fd[1], 1);
            _close(fd[1]);
            _spawnvp(_P_WAIT, args1[0], args1);

            // restore stdout
            _dup2(saved_stdout, 1);
            _close(saved_stdout);

            // run cmd2 with input coming from pipe
            _dup2(fd[0], 0);
            _close(fd[0]);
            _spawnvp(_P_WAIT, args2[0], args2);

            // restore stdin
            _dup2(saved_stdin, 0);
            _close(saved_stdin);

      }else {
            // no pipe, normal command
            int j = 0;
            char *token = strtok(input, " ");
            while (token != NULL) {
                args[j++] = token;
                token = strtok(NULL, " ");
            }
            args[j] = NULL;
      
        
      
    
    if(strcmp(args[0],"exit")==0){
        break;
    }
    else if(strcmp(args[0],"cd")==0){
        _chdir(args[1]);
    } else if (strcmp(args[0], "pwd") == 0) {
    char cwd[1024];
    _getcwd(cwd, 1024);
    printf("%s\n", cwd);
}
    else{
          _spawnvp(_P_WAIT,args[0],args);
    }
} 
}
    return 0;
}
