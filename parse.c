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
#include <jansson.h>
#include <string.h>
#include <time.h>
#include "quiz.h"

int isArray(json_t* a, char* name, json_t* root){
    if(!json_is_array(a)){
        fprintf(stderr, "error: %s is not an array\n", name);
        json_decref(root);
        return 0;
    }
    return 1;
}

int isObject(json_t* a, char* name, json_t* root){
    if(!json_is_object(a)){
        fprintf(stderr, "error: %s is not an array\n", name);
        json_decref(root);
        return 0;
    }
    return 1;
}

extern int parse(quiz_t *quiz, char *msg){
    //variables
    json_t * root, *results, *question,*answer, *wrongs, *choice,  *data;
    json_error_t error;
    root = json_loads(msg, 0, &error);
    free(msg);//we free the remporary storage
    srand(time(NULL));
    if(!root){
        perror("error in json_loads");
        return -1;
    }
    json_t *response_code = json_object_get(root, "response_code");
    if (json_integer_value(response_code) != 0) {
        fprintf(stderr, "API error: response code %d\n", (int)json_integer_value(response_code));
        json_decref(response_code);
        json_decref(root);
        return -1;
    }
    json_decref(response_code);
    //we get results array
    results = json_object_get(root, "results");
    if (!isArray(results, "results", root)){
        json_decref(results);
        return -1;
    }
    //we need to get data from the array
    data = json_array_get(results, 0);
    if(!isObject(data, "data", root)){
        json_decref(data);
        json_decref(results);
        return -1;
    }
    //we get the question
    question = json_object_get(data, "question");
    if(!json_is_string(question)){
        perror("error in json-object_get: quesion");
        json_decref(question);
        json_decref(data);
        json_decref(results);
        json_decref(root);
        return -1;
    }
    //we transfer to struct
    quiz->question = strdup(json_string_value(question));
    json_decref(question);

    //we get the answer
    answer = json_object_get(data, "correct_answer");
    if(!json_is_string(answer)){
        perror("error in json-object_get: answer");
        json_decref(answer);
        json_decref(data);
        json_decref(results);
        json_decref(root);
        return -1;
    }
    //we copy to struct
    quiz->choices[3]=strdup(json_string_value(answer));
    quiz->answer = strdup(json_string_value(answer));
    json_decref(answer);

    //we get choices
    wrongs = json_object_get(data, "incorrect_answers");
    if(!isArray(wrongs,"wrongs", root)){
        json_decref(wrongs);
        json_decref(data);
        json_decref(results);
        return -1;
    }
    for(int i=0;i<json_array_size(wrongs);i++){
        choice = json_array_get(wrongs, i);
        if(!json_is_string(choice)){
            perror("error in json-object_get: answer");
            json_decref(choice);
            json_decref(wrongs);
            json_decref(data);
            json_decref(results);
            json_decref(root);
            return -1;
        }
        quiz->choices[i]=strdup(json_string_value(choice));
        json_decref(choice);
    }
    
    
    //the values are transfered to the struct
    json_decref(wrongs);
    json_decref(data);
    json_decref(results);
    json_decref(root);
    //we mix up the answers a bit
    int new_spot=rand()%4;
    char* temp=quiz->choices[new_spot];
    quiz->choices[new_spot]=quiz->choices[3];
    quiz->choices[3]=temp;
    return 0;
}