/*
This is assignment 9
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"

#define MAX_ATTEMPS 3

//is the given answer correct?
static int isCorrect(char* answ, quiz_t* quiz){
    return (strcmp(quiz->answer, answ)==0);
}
//free question data from quiz
static void die(quiz_t* quiz){
    free(quiz->question);
    free(quiz->answer);
    for(int i = 0; i < 4; i++){
        free(quiz->choices[i]);
    }
}
//get input and check for errors
static int getInput(quiz_t* quiz){
    char answer[100];
    if (fgets(answer, sizeof(answer), stdin) == NULL) {//check for end of stdin
        printf("\n");
        return -2;
    }
    int opt=answer[0]-'a';//we can get array position
    if(answer[1]!='\n'){//is it only 1 char?
        fprintf(stderr,"too much input given\n");
        die(quiz);
        return -1;
    }
    if (opt>3 || opt<0){//is it a-d?
        fprintf(stderr,"input out range\n");
        die(quiz);
        return -1;
    }
    return opt;
}

extern int play(quiz_t *quiz){
    char options[4]="abcd";
    quiz->n=0;
    quiz->max=0;
    quiz->score=0;
    int attempt=0;
    printf("\
Answer multiple choice questions about computer science.\n\
You score points for each correctly answered question.\n\
If you need multiple attempts to answer a question, the\n\
points you score for a correct answer go down.\n\
    ");
    while(1){
        int leave=0;
        attempt=0;
        quiz->n++;
        quiz->max+=8;
        int points=8;
        //we get data for question
        char* request = fetch(URL);
        if (request==NULL){
            fprintf(stderr,"error occured while fetching\n");
            return -1;
        }
        //we parse data into the struct
        int prs = parse(quiz, request);
        if (prs==-1){
            fprintf(stderr,"error occured while parsing\n");
            return -1;
        }
        //we print the initial info
        printf("\n%s\n\n", quiz->question);
        //printf("answer: %s\n", quiz->answer);//for debugging
        for(int i=0;i<4;i++){
            printf("[%c] %s\n", options[i],quiz->choices[i]);
        }
        printf("\n");
        while(attempt<MAX_ATTEMPS){
            //we prompt the input
            printf("(%dpt) > ", points);
            int opt=getInput(quiz);
            if(opt==-1){//did we receive error?
                return -1;
            } else if(opt==-2){//was EOF?
                exit(0);
            }
            char* answ = quiz->choices[opt];
            //check the input and act accordingly
            if(isCorrect(answ, quiz)){
                quiz->score+=points;
                printf("Congratulation, answer [%c] is correct. Your current score is %d/%d points.\n", 'a'+opt, quiz->score, quiz->max);
                attempt=0;
                break;
            } else {
                printf("Answer [%c] is wrong, try again.\n", 'a'+opt);
                points/=2;
                attempt++;
            }
        }
        //we free the memory
        die(quiz);
        //we check how we left the loop
        if (attempt>=MAX_ATTEMPS){
            printf("Number of attempts acceeded!\n");
            break;
        }
        if (leave){
            exit(0);
        }
    }
    printf("Thanks for playing today.\n");
    printf("Your final score is %d/%d points\n",quiz->score, quiz->max);
    return 0;
}