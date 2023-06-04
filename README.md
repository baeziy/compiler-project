# COMP 451 Section X - Spring 2023 Semester Project

This project includes two key components: the lexer (`lex.c`) and the parser (`parser.c`). These are fundamental components in a compiler pipeline, handling lexical analysis and syntax analysis, respectively. 

## Members:
- Muhammad Mustafa Kamal Malik (Roll Number: 241610047)
- Mahnoor (Roll Number: 231450813)

## Submission Date:
June 04, 2023

## lex.c

`lex.c` is a simple lexer or lexical analyzer. This program reads a series of strings passed as command-line arguments. For each character in the strings, the program identifies whether it's an operand (lower-case alphabet), an operator (+, -, *, /), or an invalid character. It also checks for the presence of a sentinel character ('$') and the count of operands (not exceeding 5).

To run `lex.c`, compile the program using a C compiler, then run it with your strings as command-line arguments.

```bash
gcc lex.c -o lex
./lex "your first string here" "your second string here" "more strings..."
```

## parser.c

`parser.c` is a rudimentary implementation of a parser that analyzes expressions based on operator precedence parsing. It uses a pre-defined table of operator precedence to decide the course of action. It can handle arithmetic operations including addition, subtraction, multiplication, and division on operands. The operands are represented by lowercase alphabets. 

For each operand, the user is required to input the associated value when the program is running. The parser then evaluates the expression based on the operator precedence and the provided operand values. It outputs the final result of the expression.

To run `parser.c`, compile the program using a C compiler, then run it with your strings as command-line arguments.

```bash
gcc parser.c -o parser
./parser "your first string here" "your second string here" "more strings..."
```

> Please note: the expressions should be input in postfix format. The end of the expression should be denoted by the '$' character.

Both programs are essential in understanding the basics of how compilers work, specifically in the steps of lexical and syntax analysis. This project provides a rudimentary understanding of these operations. For any queries or concerns, please reach out to the group members.
