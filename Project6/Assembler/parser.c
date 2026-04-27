#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



void strip_comments_and_whitespace(char *input, char *output) {
    char *read  = input;
    char *write = output;

    while (*read) {

        if (*read == '/' && *(read + 1) == '/') {
            /* Skip everything until end of line */
            while (*read && *read != '\n') read++;

        } else if (*read == ' ' || *read == '\t' || *read == '\n') {
            /* Skip whitespace */
            read++;

        } else {
            *write++ = *read++;
        }
    }

    *write = '\0';
}



char command_Type(char *line) {
    if (line[0] == '@') {
        if (isalpha(line[1])) {
          return 'A'; // For Variable Symbol
        }   else {
            return 'D'; // For Integers
          }
        
    }
      else if (line[0] == '(') {
      return 'L'; // For Label Symbols

    } else {
      return 'C'; // C instructions
    }
}

int get_decimal(char *line) {
    int decimal = 0;
    if (command_Type(line) == 'D') { 
    sscanf(line, "@%d", &decimal);
    return decimal;
   }
}

const char* get_symbol(char *line ,char *variable_symbol) {
    
    if (command_Type(line) == 'A') {
      sscanf(line, "@%s", variable_symbol);
      return variable_symbol;
    } 
  
    return NULL;
}


void parse_C_instruction(char *line, char *dest, char *comp, char *jump) {
    dest[0] = '\0';
    comp[0] = '\0';
    jump[0] = '\0';

    char *eq    = strchr(line, '=');
    char *start = line;

    /* Extract dest if '=' present */
    if (eq) {
        size_t len = eq - line;
        memcpy(dest, line, len);
        dest[len] = '\0';
        start = eq + 1;
    }

    /* Split comp and jump on ';' */
    char *sc = strchr(start, ';');

    if (sc) {
        size_t len = sc - start;
        memcpy(comp, start, len);
        comp[len] = '\0';
        strcpy(jump, sc + 1);
    } else {
        strcpy(comp, start);
    }
}
