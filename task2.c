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

int id_values[MAX_TOKENS];
char id_names[MAX_TOKENS];
int id_count = 0;

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

void evaluate(char op, int *stack, int *top) {
    int b = stack[(*top)--];
    int a = stack[(*top)--];
    switch (op) {
        case '+': stack[++(*top)] = a + b; break;
        case '-': stack[++(*top)] = a - b; break;
        case '*': stack[++(*top)] = a * b; break;
        case '/': stack[++(*top)] = a / b; break;
    }
}
float res = 0.0;
void foo(int stackI, int chI, int* top, char* stack, char* ch, char* tempStack, int* tempTop){
    switch(precedence[stackI][chI]){
        case '<':
            stack[++(*top)] = *(ch++);
            printf("%s\t\t\t%s\t\t\tPush\n", stack, ch);
            break;
        case '>':
            tempStack[++(*tempTop)] = stack[(*top)];
            stack[(*top)--] = ' ';
            printf("%s\t\t\t%s\t\t\tPop\n", stack, ch);
            if(isOperand(tempStack[*tempTop]) && (*tempTop > 1)){
                switch(tempStack[*tempTop]){
                    case '+':
                        res += (tempStack[*tempTop - 2] - '0') + (tempStack[*tempTop - 1] - '0');
                        break;
                    case '-':
                        res += (tempStack[*tempTop - 2] - '0') - (tempStack[*tempTop - 1] - '0');
                        break;
                    case '*':
                        res += (tempStack[*tempTop - 2] - '0') * (tempStack[*tempTop - 1] - '0');
                        break;
                    case '/':
                        res += (float)(tempStack[*tempTop - 2] - '0') / (tempStack[*tempTop - 1] - '0');
                        break;
                }
            }
            break;
        default:
            printf("Rejected\n");
            exit(1);
    }
}
void parse(const char *str) {
    char *stack = (char *) malloc(sizeof(char) * 10);
    stack[0] = '$';
    char *tempStack = (char *) malloc(sizeof(char) * 10);
    int top = 0;
    char *ch = str;
    printf("Stack\t\t\tInput\t\t\tAction\n");
    while (*ch != '$' || stack[top] != '$') {
        
        int stackIndex = get_index(stack[top]);
        int nextInputIndex = get_index(*ch);



        



        int stackTop = get_index(stack[top] == 'i' ? 'i' : stack[top]);
        int nextInput = get_index(*ch);
        if (precedence[stackTop][nextInput] == '<' || precedence[stackTop][nextInput] == '=') {
            printf("%s\t\t\t%s\t\t\tPush\n", stack, ch);
            stack[++top] = *(ch++);
        } else if (precedence[stackTop][nextInput] == '>') {
            printf("%s\t\t\t%s\t\t\tPop\n", stack, ch);
            if (stack[top] == 'i') stack[top] = id_values[*(--ch) - 'a'];
            else evaluate(stack[top--], stack, &top);
        } else {
            printf("Rejected\n");
            return;
        }
    }
    printf("%s\t\t\t%s\t\t\tAccepted\n", stack, ch);
    printf("The output of the given expression is: %d\n", stack[top]);
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
                    id_names[id_count] = ch;
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
        

        printf("Number of operands found: %d\n", id_count);
        for(int i = 0; i < id_count; ++i){
            printf("Enter value for %c: ", id_names[i]);
            scanf("%d", &id_values[i]);
        }

        parse(input);

        sen = 0;
    }

    return 0;
}

int isOperand(const char* ch){
    return (*ch >= 'a' && *ch <= 'z');
}
int isOperator(const char* ch){
    return (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/');
}