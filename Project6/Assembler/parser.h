#ifndef PARSER_H
#define PARSER_H

void strip_comments_and_whitespace(char *input, char *output);

char command_Type(char *line);


const char* get_symbol(char *line, char *variable_symbol);


int get_decimal(char *line);

void parse_C_instruction(char *line, char *dest, char *comp, char *jump);


#endif 
