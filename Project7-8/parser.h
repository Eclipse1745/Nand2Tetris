#ifndef PARSER_H
#define PARSER_H

void strip_comments(char *input , char *output);


char *command_type(char *line);


void return_arg1(char *line , char *arg1_buf);


void return_arg2(char *line , char *arg2_buf);

#endif 
