#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define size 100

typedef enum {
    Q0, Q1, Q2, Q3, Q4_END, Q5, Q6, Q7_END, Q8, Q9, ERROR
} State;

bool is_final_state(State state){
    return (state == Q4_END || state == Q7_END);
}

State next_state(State actual_state, char input_char){
    switch(actual_state){
        case Q0:
            if(input_char == 'f') return Q1;
            else if(input_char == 'c') return Q8;
            break;
        case Q1:
            if(input_char == 'l') return Q2;
            else if(input_char == 'o') return Q3;
            break;
        case Q2:
            if(input_char == 'o') return Q5;
            break;
        case Q3:
            if(input_char == 'r') return Q4_END;
            break;
        case Q5:
            if (input_char == 'a') return Q6;
            break;
        case Q6:
            if(input_char == 't') return Q7_END;
            break;
        case Q8:
            if(input_char == 'h') return Q9;
            break;
        case Q9:
            if(input_char == 'a') return Q3;
            break;
        default:
            return ERROR;
    }
    return ERROR;
}

void proccess_string(char input_string[]){
    State state = Q0;
    int length = strlen(input_string);

    for (int i = 0; i < length && state != ERROR; i++){
        state = next_state(state, input_string[i]);
    }

    if(is_final_state(state)){
        printf("The string \"%s\" is accepted.\n", input_string);
    } else {
        printf("The string \"%s\" is not accepted.\n", input_string);
    }
}

int main() {

    proccess_string("float");
    proccess_string("for");
    proccess_string("chara");
    proccess_string("floa");

    return 0;
}