/*
This is assignment 9
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"

int main(){
    while(1){
        quiz_t quiz;
        int check = play(&quiz);
        if (check==-1){
            fprintf(stderr, "error occured while playing the game\n");
            return -1;
        }
        printf("\n\n");
    }
    return 0;
}