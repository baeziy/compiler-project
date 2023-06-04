/*
              DATA DICTIONARY
              COMP 451 Section X
              Spring 2023
              Project
              Group Members: Muhammad Mustafa Kamal Malik
                             Mahnoor
              Roll Number:   241610047
                             231450813
              Date of Submission: June 04, 2023
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 10

int isOperand(const char*);
int isOperator(const char*);

char precedence[6][6] = {
    {' ', '>', '>', '>', '>', '>'},
    {'<', '>', '>', '<', '<', '>'},
    {'<', '>', '>', '<', '<', '>'},
    {'<', '>', '>', '>', '>', '>'},
    {'<', '>', '>', '>', '>', '>'},
    {'<', '<', '<', '<', '<', ' '}
};

float id_values[MAX_TOKENS];
char id_names[MAX_TOKENS];
int id_count = 0;
char *ch;
int get_index(char ch) {
    switch (ch) {
        case '+': return 1;
        case '-': return 2;
        case '*': return 3;
        case '/': return 4;
        case '$': return 5;
        default: return 0;
    }
}

float res = 0.0;
void foo(int stackI, int chI, int* top, char* stack, char* tempStack, int* tempTop){
    switch(precedence[stackI][chI]){
        // stackI < chI
        case '<':
            stack[++(*top)] = *(ch++);
            printf("\t%s\t\t\t%s\t\t\tPush\n", stack, ch);
            break;
        // stackI > chI
        case '>':
            tempStack[(*tempTop)] = stack[(*top)];
            *tempTop += 1;
            stack[*top] = ' ';
            *top -= 1;
            printf("\t%s\t\t\t%s\t\t\tPop\n", stack, ch);

            // if an operator is found, perform operation on top 2 operands
            if(isOperator(&tempStack[*tempTop-1]) && (*tempTop > 1)){
                switch(tempStack[*tempTop-1]){
                    case '+':
                    // add top 2 operands and store result in first operand + res
                        res = id_values[((tempStack[*tempTop - 3]) - 'a')] + id_values[((tempStack[*tempTop - 2]) - 'a')];
                        id_values[((tempStack[*tempTop - 3]) - 'a')] = res;
                        break;
                    case '-':
                    // subtract top 2 operands and store result in first operand + res
                        res = id_values[((tempStack[*tempTop - 3]) - 'a')] - id_values[((tempStack[*tempTop - 2]) - 'a')];
                        id_values[((tempStack[*tempTop - 3]) - 'a')] = res;
                        break;
                    case '*':
                    // multiply top 2 operands and store result in first operand + res
                        res = id_values[((tempStack[*tempTop - 3]) - 'a')] * id_values[((tempStack[*tempTop - 2]) - 'a')];
                        id_values[((tempStack[*tempTop - 3]) - 'a')] = res;
                        break;
                    case '/':
                    // divide top 2 operands and store result in first operand + res
                        res = (float)id_values[((tempStack[*tempTop - 3]) - 'a')] / id_values[((tempStack[*tempTop - 2]) - 'a')];
                        id_values[((tempStack[*tempTop - 3]) - 'a')] = res;
                        break;
                }
                // remove top 2 operands from stack and replace with first operand
                tempStack[*(tempTop) - 2] = ' ';
                tempStack[*(tempTop) - 1] = ' ';
                *tempTop -= 2;
            }

            break;
        default:
            printf("Rejected\n");
            exit(1);
    }
}
void parse(char *str) {
    char *stack = (char *) malloc(sizeof(char) * 10);
    stack[0] = '$';
    int top = 0;
    char *tempStack = (char *) malloc(sizeof(char) * 10);
    int tempTop = 0;
    ch = str;
    printf("\tStack\t\t\tInput\t\t\tAction\n");
    printf("\t%s\t\t\t%s\t\t\t\n", stack, ch);

    // checking if sentinal character is found in both stack and input
    while (*ch != '$' || stack[top] != '$') {
        
        int stackIndex = get_index(stack[top]);
        int nextInputIndex = get_index(*ch);

        // foo() will print the action taken and update the stack and input + res
        foo(stackIndex, nextInputIndex, &top, stack, tempStack, &tempTop);
    }
    printf("\t%s\t\t\t%s\t\t\tAccepted\n", stack, ch);
    printf("The output of the given expression is: %f\n", res);
}

int main(int argc, char ** argv){

    // checking if there is atleast one input string
    if (argc < 2) {
        printf("Please provide atleast one input string as an argument.\n");
        return 1;
    }

    // looping over all input strings
    for(int i = 1; i < argc; ++i){

        // input has whole string
        char *input = argv[i];

        printf("\n***Program finds following tokens in the expression:***\n");
        printf("Expression received: %s\n", input);

        int sen = 0;
        // looping over all characters in input string
        for (int i = 0, opCount = 0; i < strlen(input); i++) {
            char ch = input[i];

            // checking if sentinal character is found
            if (ch == '$') {
                sen = 1;
                break;
            }

            // Check if character is an operand (lower-case alphabet)
            else if (isOperand(&ch)) {
                opCount++;
                if(opCount > 5){
                    printf("More than 5 operands found. Program terminated prematurely.\n");
                    return 1;
                }
                else{
                    id_names[id_count++] = ch;
                }
                
                
            }

            // Check if character is an operator (+, -, *, /)
            else if(isOperator(&ch)){
                continue;
            }

            // If character is not an operand or an operator, then it is invalid
            else{
               printf("Invalid token encountered: %c. Program terminated prematurely.\n", ch);
               return 1;
            }

        }

        if(!sen){
            printf("Sentinal character not found for: %s\n", input);
            return 1;
        }
        
        // getting values for operands
        printf("Number of operands found: %d\n", id_count);
        for(int i = 0; i < id_count; ++i){
            printf("Enter value for %c: ", id_names[i]);
            scanf("%f", &id_values[id_names[i] - 'a']);
        }

        // parsing the input string
        parse(input);

        // resetting values for next input string
        sen = 0;
    }

    return 0;
}

// function definitions
int isOperand(const char* ch){
    return (*ch >= 'a' && *ch <= 'z');
}
int isOperator(const char* ch){
    return (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/');
}
