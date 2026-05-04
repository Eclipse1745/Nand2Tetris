#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "parser.h"
#include "codewriter.h"

void translate_file(char *vm_filepath, FILE *asm_file, char *filename) {
  char buffer[100];
  char cleanbuffer[100];

  FILE *vm_file = fopen(vm_filepath, "r");
  if (vm_file == NULL) {
    fprintf(stderr, "Error: Could not open %s\n", vm_filepath);
    exit(1);
  }

  while (fgets(buffer, sizeof(buffer), vm_file)) {
    strip_comments(buffer, cleanbuffer);
    cleanbuffer[strcspn(cleanbuffer, "\n")] = '\0';
    
    if (is_empty(cleanbuffer)) continue;

    char *type = command_type(cleanbuffer);
    char arg1[32];
    char arg2[32];

    if (strcmp(type, "C_push") == 0 || strcmp(type, "C_pop") == 0) {
      return_arg1(cleanbuffer, arg1);
      return_arg2(cleanbuffer, arg2);
      Write_push_pop(type, arg1, arg2, asm_file, filename);
    } else if (!strcmp(type, "C_label")) {
      return_arg1(cleanbuffer, arg1);
      write_label(asm_file, arg1);
    } else if (!strcmp(type, "C_goto")) {
      return_arg1(cleanbuffer, arg1);
      write_goto(asm_file, arg1);
    } else if (!strcmp(type, "C_if")) {
      return_arg1(cleanbuffer, arg1);
      write_ifgoto(asm_file, arg1);
    } else if (!strcmp(type, "C_function")) {
      return_arg1(cleanbuffer, arg1);
      return_arg2(cleanbuffer, arg2);
      write_function(asm_file, arg1, arg2);
    } else if (!strcmp(type, "C_call")) {
      return_arg1(cleanbuffer, arg1);
      return_arg2(cleanbuffer, arg2);
      write_call(asm_file, arg1, arg2);
    } else if (!strcmp(type, "C_return")) {
      write_return(asm_file);
    } else {
      write_arithmetic(type, asm_file);
    }
  }

  fclose(vm_file);

}

int main(int argc, char *argv[])
{
  if (argc != 2) {
      fprintf(stderr, "Usage: ./translator <file.vm or directory>\n");
      exit(1);
  }

  char *vm_filepath = argv[1];
  int len = strlen(vm_filepath);
  char asm_filepath[512];
  char filename[128];


  if (len >= 3 && strcmp(vm_filepath + len - 3, ".vm") == 0) {
     strncpy(asm_filepath, vm_filepath, len - 3);
     asm_filepath[len - 3] = '\0';
     strcat(asm_filepath, ".asm");

     char *slash = strrchr(asm_filepath, '/');
     if (slash) strncpy(filename, slash + 1, 64);
     else strncpy(filename, asm_filepath, 64);
     filename[strlen(filename) - 4] = '\0';

     FILE *asm_file = fopen(asm_filepath, "w");
     if (asm_file == NULL) {
         fprintf(stderr, "Error: could not open/create %s\n", asm_filepath);
         exit(1);
     }
    translate_file(vm_filepath, asm_file, filename);
    fclose(asm_file);
 } else {

    if (vm_filepath[len - 1] == '/') vm_filepath[len - 1] = '\0';

    char *slash = strrchr(vm_filepath, '/');

    char *dirname;
    if (slash != NULL) {
      dirname = slash + 1;      
    } else {
      dirname = vm_filepath;  
    }
    
    snprintf(asm_filepath, sizeof(asm_filepath), "%s/%s.asm", vm_filepath, dirname);
    
    FILE *asm_file = fopen(asm_filepath, "w");
    if (asm_file == NULL) {
        fprintf(stderr, "Error: could not open/create %s\n", asm_filepath);
        exit(1);
    }
    
    write_bootstrap(asm_file);
    
    DIR *dir = opendir(vm_filepath);
    if (dir == NULL) {
        perror("Unable to open directory");
        exit(1);
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        int namelen = strlen(entry->d_name);
        if (namelen >= 3 && strcmp(entry->d_name + namelen - 3, ".vm") == 0) {
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s/%s", vm_filepath, entry->d_name);
            strncpy(filename, entry->d_name, namelen - 3);
            filename[namelen - 3] = '\0';
            translate_file(filepath, asm_file, filename);
        }
    }
    
    closedir(dir);
    fclose(asm_file);
  }
}
