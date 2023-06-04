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
        case 'i': return 0;
        case '+': return 1;
        case '-': return 2;
        case '*': return 3;
        case '/': return 4;
        case '$': return 5;
        default: return -1;
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

void parse(char *str) {
    int stack[20] = {'$'};
    int top = 0;
    char *ch = str;
    printf("Stack\t\t\tInput\t\t\tAction\n");
    while (*ch != '$' || stack[top] != '$') {
        if (!top && *ch != 'i') {
            printf("Rejected\n");
            return;
        }
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide a string expression as argument.\n");
        return -1;
    }
    char *ch = argv[1];

    for(int i = 0; i < strlen(ch); i++){
        if(isalpha(ch[i])){
            id_names[id_count++] = ch[i];
        }
    }

    printf("Enter integer values of the following identifiers:\n");
    for (int i = 0; i < id_count; i++) {
        printf("Value of %c: ", id_names[i]);
        scanf("%d", &id_values[i]);
    }

    parse(ch);
    
    return 0;
}
