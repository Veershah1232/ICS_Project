#include<stdio.h>
#include<stdlib.h>
#include"dictionary.c"

//#include "all lib.h"

typedef struct vectors{
    void *variable;
}vectors;

typedef struct{
    int capacity;
    int vars;
    int type;
    vectors *vector_var;
}variables;

variables* variable_initialiser(){
    variables variable_list[11];
    for(int i = 0; i < 10; i++){
        variable_list[i].capacity = 1;
        variable_list[i].vars = 0;
        variable_list[i].type = i;
        variable_list[i].vector_var = (vectors *)malloc(sizeof(vectors));
        variable_list[i].vector_var->variable = NULL;
    }
    return variable_list;
}

void increase_var_list(int type, variables *variable_list){
    if(variable_list[type].capacity <= variable_list[type].vars){ //only increase if needed
        variable_list[type].capacity *= 2;
        variable_list[type].vector_var = (vectors *)realloc(variable_list[type].vector_var,variable_list[type].capacity * sizeof(vectors));
        for(int i = variable_list[type].vars; i < variable_list[type].capacity; i++){
            variable_list[type].vector_var[i].variable = NULL;
        }
    }
}

vectors* Add_variable(int type, variables *variable_list,char name[50]){
    if(variable_list[type].vars >= variable_list[type].capacity){
        increase_var_list(type, variable_list);
    }
    for(int i=0; i<variable_list[type].capacity;i++){
        if(variable_list[type].vector_var[i].variable == NULL){
            if(type == 0){
                variable_list[type].vector_var[i].variable = (dictionary_C_C *)create_dictionary_C_C(1,name);
            }
            //else if other all variables
        }
    }
}

int main(void){
    printf("Hi");
    return 0;
}
/*
10 Variables types
capacity
no.of variables
vector locations

*/