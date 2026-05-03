#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codewriter.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
      fprintf(stderr, "Usage: ./translator <file.vm>\n");
      exit(1);
  }

  char *vm_filepath = argv[1];
  int len = strlen(vm_filepath);

  if (len < 3 || strcmp(vm_filepath + len - 3, ".vm") != 0) {
    fprintf(stderr, "Error: File must have .vm extension\n");
    exit(1);
  }

  char asm_filepath[64];
  char filename[64];
  strncpy(asm_filepath, vm_filepath, len - 3);
  asm_filepath[len - 3] = '\0';
  strcat(asm_filepath, ".asm");

  char *slash = strrchr(asm_filepath, '/');
  if (slash) strncpy(filename, slash + 1, 64);
  else strncpy(filename, asm_filepath, 64);
  filename[strlen(filename) - 4] = '\0';
  char buffer[100];
  char cleanbuffer[100];

  FILE *vm_file = fopen(vm_filepath, "r");
  if (vm_file == NULL) {
    fprintf(stderr, "Error: Could not open %s\n", vm_filepath);
    exit(1);
  }

  FILE *asm_file = fopen(asm_filepath, "w");
  if (asm_file == NULL) {
    fprintf(stderr, "Error: could not open/create %s\n", asm_filepath);
  }
 
  
  while (fgets(buffer, sizeof(buffer), vm_file)) {
    strip_comments(buffer, cleanbuffer);
    char *type = command_type(cleanbuffer);
    char arg1[32];
    char arg2[32];
    if (strcmp(type, "C_push") == 0 || strcmp(type, "C_pop") == 0) {
      return_arg1(cleanbuffer, arg1);
      return_arg2(cleanbuffer, arg2);
      Write_push_pop(type, arg1, arg2, asm_file, filename);
  } else if (!strcmp(type, "C_label")) {
    return_arg1(cleanbuffer,arg1);
    write_label(asm_file,arg1);
  } else {
      write_arithmetic(type, asm_file);
}
  }
  fclose(vm_file);
  fclose(asm_file);

  
  
}


