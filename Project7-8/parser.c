#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strip_comments(char *input , char *output) {
  char *read = input;
  char *write = output;

  while (*read) {
    if (*read == '/' && *(read + 1) == '/') {
      while(*read && *read != '\n') read++;
    }  else {
       *write++ = *read++;
    }
  }
  *write = '\0';
}



char *command_type(char *line) {
  char command[32];
  sscanf(line, "%s", command);
  
  // Arithmetic/Logical Commands
  if (strcmp(command, "add") == 0) return "C_add";
  if (strcmp(command, "sub") == 0) return "C_sub"; 
  if (strcmp(command, "neg") == 0) return "C_neg";
  if (strcmp(command, "eq") == 0) return "C_eq"; 
  if (strcmp(command, "gt") == 0) return "C_gt"; 
  if (strcmp(command, "lt") == 0) return "C_lt";
  if (strcmp(command, "and") == 0) return "C_and"; 
  if (strcmp(command, "or") == 0) return "C_or"; 
  if (strcmp(command, "not") == 0) return "C_not";

  
  if (strcmp(command, "push") == 0) return "C_push";
  if (strcmp(command, "pop") == 0) return "C_pop"; 

  // Branching commands
  if (strcmp(command, "if") == 0) return "C_if";
  if (strcmp(command, "goto") == 0) return "C_goto";
  if (strcmp(command, "label") == 0) return "C_label";


  // Function Commands
  if (strcmp(command, "function") == 0) return "C_function";
  if (strcmp(command, "call") == 0) return "C_call";
  if (strcmp(command, "return")  == 0) return "C_return";

  return "unknown";
}

void return_arg1(char *line , char *arg1_buf) {
 
  if (strcmp(command_type(line), "C_return") == 0) return;

  char *type = command_type(line);
    
    if (strcmp(type, "C_add") == 0 ||
        strcmp(type, "C_sub") == 0 ||
        strcmp(type, "C_neg") == 0 ||
        strcmp(type, "C_eq")  == 0 ||
        strcmp(type, "C_gt")  == 0 ||
        strcmp(type, "C_lt")  == 0 ||
        strcmp(type, "C_and") == 0 ||
        strcmp(type, "C_or")  == 0 ||
        strcmp(type, "C_not") == 0) {
        sscanf(line, "%s", arg1_buf); 
    } else {
        char command[32];
        sscanf(line, "%s %s", command, arg1_buf); // skip command get arg1 
    }
}

void return_arg2(char *line , char *arg2_buf) {

  char *type = command_type(line);

  if (strcmp(type, "C_push")     == 0 ||
      strcmp(type, "C_pop")      == 0 ||
      strcmp(type, "C_call")     == 0 ||
      strcmp(type, "C_function") == 0 ) {
      
      char command[32], arg1[32];
      sscanf(line, "%s %s %s", command , arg1 , arg2_buf); // skip command and arg1 get arg2
  }
}


