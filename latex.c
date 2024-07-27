#include <stdio.h>
#include <ctype.h>
#include <string.h>
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", 
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "inline", "int", "long", "register", "restrict", "return", "short", 
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", 
    "unsigned"
};
int is_keyword(const char* token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_operator(char ch) {
    char operators[] = "+-*/%=&|<>!~^";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}
int is_separator(char ch) {
    char separators[] = " ,;(){}[]";
    for (int i = 0; i < strlen(separators); i++) {
        if (ch == separators[i]) {
            return 1;
        }
    }
    return 0;
}
void count_tokens(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count = 0;
    char ch;
    char buffer[MAX_TOKEN_LENGTH];
    int buf_index = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || is_operator(ch) || is_separator(ch)) {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                strcpy(tokens[token_count++], buffer);
                buf_index = 0;
            }
            if (is_operator(ch) || is_separator(ch)) {
                tokens[token_count][0] = ch;
                tokens[token_count][1] = '\0';
                token_count++;
            }
        } else {
            buffer[buf_index++] = ch;
        }
    }
    fclose(file);
    int keyword_count = 0, identifier_count = 0, operator_count = 0, separator_count = 0, number_count = 0;
    for (int i = 0; i < token_count; i++) {
        if (is_keyword(tokens[i])) {
            keyword_count++;
        } else if (isalpha(tokens[i][0]) || tokens[i][0] == '_') {
            identifier_count++;
        } else if (isdigit(tokens[i][0])) {
            number_count++;
        } else if (is_operator(tokens[i][0])) {
            operator_count++;
        } else if (is_separator(tokens[i][0])) {
            separator_count++;
        }
    }
    printf("Keywords: %d\n", keyword_count);
    printf("Identifiers: %d\n", identifier_count);
    printf("Operators: %d\n", operator_count);
    printf("Separators: %d\n", separator_count);
    printf("Numbers: %d\n", number_count);
}
int main() {
    char filename[] = "ss.c";
    count_tokens(filename);
    return 0;
}
