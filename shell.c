#include <stdio.h>
#include <string.h>
#include <process.h>
#include <direct.h>
#define MAX_INPUT 1024

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
       int j = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[j] = token;
            j++;
            token = strtok(NULL, " ");
        }
        args[j] = NULL;  
        
      
    
    if(strcmp(args[0],"exit")==0){
        break;
    }
    else if(strcmp(args[0],"cd")==0){
        chdir(args[1]);
    } else if (strcmp(args[0], "pwd") == 0) {
    char cwd[1024];
    _getcwd(cwd, 1024);
    printf("%s\n", cwd);}
    else{
          _spawnvp(_P_WAIT,args[0],args);
    }
} 
    return 0;
}
