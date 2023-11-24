#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_CHUNK 20

int main() {
    printf("Hello, World!\n");
    return 0;
}



char* get_text_input(const char* end_symbol) {
    unsigned int size = 0, capacity = MEMORY_CHUNK;
    char ch;
    char *text = malloc(sizeof(char *));
    while ((ch = getchar()) != *end_symbol) {
        if (ch != '\n') {
            if (size >= capacity - 1) {
                capacity += MEMORY_CHUNK;
                text = realloc(text, capacity * sizeof(char));
            }
            text[size++] = ch;
        }
    }
    text = realloc(text, (size + 2) * sizeof(char));
    text[size++] = *end_symbol;
    text[size] = '\0';
//    printf("Инпут текст попало\n");
    return text;

}