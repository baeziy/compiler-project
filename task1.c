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


#include<stdio.h>
#include <string.h>

int isOperand(const char*);
int isOperator(const char*);

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
        for (int i = 0, sen = 0, opCount = 0; i < strlen(input); i++) {
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
                else
                printf("Operand found: %c\n", ch);
                
            }

            // Check if character is an operator (+, -, *, /)
            else if(isOperator(&ch)){
                printf("Operator found: %c\n", ch);
            }

            // If character is not an operand or an operator, then it is invalid
            else{
               printf("Invalid token encountered: %c. Program terminated prematurely.\n", ch);
               return 1;
            }

        }

        printf("Sentinal character not found for: %s\n", input);


    }



    return 0;
}

int isOperand(const char* ch){
    return (*ch >= 'a' && *ch <= 'z');
}
int isOperator(const char* ch){
    return (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/');
}