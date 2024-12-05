/*
This is assignment 9
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "quiz.h"

extern char* fetch(char *url){
    pid_t pid;
    int pfd[2];
    if (pipe(pfd) == -1) {//pipe is created
        perror("pipe");
        return NULL;
    }
    pid = fork();//we fork
    if (pid == -1) {
        (void) close(pfd[0]);
        (void) close(pfd[1]);
        perror("fork");
        return NULL;
    }
    if (pid == 0) {
        //CHILD
        if(dup2(pfd[1],STDOUT_FILENO)==-1){
            perror("dup2");
            (void) close(pfd[0]);
            (void) close(pfd[1]);
            exit(-1);
        }
        (void) close(pfd[0]);
        (void) close(pfd[1]);
        execlp("curl","curl","-s", url, NULL); // we launch the command in child
        perror("execlp");
        exit(-1);
    } else {
        //PARENT
        //we create a buffer
        char* temp;
        size_t already_read=0;
        size_t new_read=0;
        size_t size=2048;
        int status;
        temp = (char*) malloc(sizeof(char)*size);
        if(temp==NULL){ //check for correct allocation
            perror("malloc");
            (void) close(pfd[0]);
            (void) close(pfd[1]);
            return NULL;
        }
        //we close of the writing end
        (void) close(pfd[1]);
        //reading starts here
        while ((new_read = read(pfd[0], temp+already_read, size-already_read-1)) > 0) {
            already_read+=new_read;
            //do we need more space?
            if(already_read>size-1){
                size*=2;
                char* new_temp = realloc(temp, size);
                if (new_temp==NULL){
                    perror("realloc");
                    (void) close(pfd[0]);
                    free(temp);
                    return NULL;
                }
                temp=new_temp;
            }
        }        
        (void) close(pfd[0]);//we close the pipe
        temp[already_read]='\0';//we put the 0 at the end of a string to terminate it
        if(waitpid(pid,&status,0)==-1){//wait for child
            return NULL;
        }
        return temp;
    }
    return NULL;
}