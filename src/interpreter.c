/* Copyright (C) 2025 by GPU Governor, All Rights Reserved. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//-------------------------------------------------------------

// 									GLOBAL VARIABLES
// Buffer-based Lexer
char inputBuffer[256];  // Holds input for tokenization
int bufferPos = 0;      // Tracks current position in inputBuffer
int line = 1;           // Tracks the line number
void lexer(); // declared the lexer function as global but the definition (implemetations) is done later
//-------------------------------------------------------------

// 									TOKENS

enum TokenType {
    KEYWORD,
    // OPERATORS
    PLUS, MINUS, DIVISION, MULT, EQUAL,
    // SYMBOLS
    LBRACE, RBRACE, LPAREN, RPAREN, LESS, GREAT, SEMI,
    // 
    NUMBER,
    //
    EOI,
    ID
};

typedef struct {
    enum TokenType type;
    char *value;
    int line;
} Token;


Token token;  // Global token instance
char *keywords[] = {"call","print", "push", NULL};


void show_tokens() {
    do {
        lexer();
        if (token.type != EOI) {
            // Print token type
            switch (token.type) {
                case PLUS: printf("PLUS"); break;
                case MINUS: printf("MINUS"); break;
                case DIVISION: printf("DIVISION"); break;
                case MULT: printf("MULT"); break;
                case EQUAL: printf("EQUAL"); break;
                case LBRACE: printf("LBRACE"); break;
                case RBRACE: printf("RBRACE"); break;
                case LPAREN: printf("LPAREN"); break;
                case RPAREN: printf("RPAREN"); break;
                case LESS: printf("LESS"); break;
                case GREAT: printf("GREAT"); break;
                case SEMI: printf("SEMI"); break;
                case NUMBER: printf("NUMBER"); break;
                case EOI: printf("EOI"); break;
                case KEYWORD: printf("KEYWORD"); break;
                case ID: printf("ID"); break;
                default: printf("UNKNOWN"); break;
            }
            // Print token value if it exists
            if (token.value) {
                printf(" (%s)", token.value);
            }
            printf("\n");
        }
    } while (token.type != EOI);
}

// ----------------------------------------------------------------------------------------------------------------
//										ERROR HANDLING

void syntax_error() {
    fprintf(stderr, "Syntax Error at line %d\n", token.line);
    exit(1);
}

// ----------------------------------------------------------------------------------------------------------------
//										LEXER

char next_ch() {
    char ch = inputBuffer[bufferPos++];
    if (ch == '\n') line++; // tracks new line
    return ch;
}

void lexer() {
    // Free the previous token's value if allocated
    if (token.value) {
        free(token.value);
        token.value = NULL;
    }

    char ch;
    do {
        ch = next_ch();  // Read next character
    } while (isspace(ch));  // Skip whitespace

    token.line = line;  // Store the line number for error reporting

    if (ch == '\0') {  // End of input (EOI)
        token.type = EOI;
        return;
    }

    switch (ch) {
        case '{': token.type = LBRACE; break;
        case '}': token.type = RBRACE; break;
        case '(': token.type = LPAREN; break;
        case ')': token.type = RPAREN; break;
        case '+': token.type = PLUS; break;
        case '-': token.type = MINUS; break;
        case '<': token.type = LESS; break;
        case '>': token.type = GREAT; break;
        case ';': token.type = SEMI; break;
        case '=': token.type = EQUAL; break;

        default:
            if (isdigit(ch)) {
                char num_buffer[20];
                int i = 0;
                while (isdigit(ch)) {
                    num_buffer[i++] = ch;
                    ch = next_ch();
                }
                num_buffer[i] = '\0';
                bufferPos--;  // Move back one step as we read one extra character
                token.value = strdup(num_buffer);
                token.type = NUMBER;
            }
            else if (isalpha(ch) || ch == '_') {
                char id_buffer[100];
                int i = 0;
                while (isalnum(ch) || ch == '_') {
                    id_buffer[i++] = ch;
                    ch = next_ch();
                }
                id_buffer[i] = '\0';
                bufferPos--;  // Move back one step

                token.value = strdup(id_buffer);
                for (int j = 0; keywords[j] != NULL; j++) {
                    if (strcmp(id_buffer, keywords[j]) == 0) {
                        token.type = KEYWORD;
                        return;
                    }
                }
                token.type = ID;
            }
            else {
                syntax_error();
            }
    }
}
// ----------------------------------------------------------------------------------------------------------------
//								PARSER

// ----------------------------------------------------------------------------------------------------------------
//										INTERPRETER LOOP
void interpreter_shell(){
    printf("Stak interpreter 0.1.0  --  [Press CTRL+C to exit]\n");
	printf("Type \"help\" for more info.\n");
    while (1) {
        printf(">> ");
        
        if (!fgets(inputBuffer, sizeof(inputBuffer), stdin)) {
            break;  // Exit on EOF
        }

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';  // Trim newline

        if (strcmp(inputBuffer, "help") == 0) {
            // TODO
        }
        bufferPos = 0;  // Reset buffer position for new input
        
		show_tokens(); // you
    }	
}

// ----------------------------------------------------------------------------------------------------------------
//					main function
int main() {
//		example	
//		push "Hello, World!"
//		call print
//		
//		push 5
//		push 10
//		call add


interpreter_shell();

    return 0;
}