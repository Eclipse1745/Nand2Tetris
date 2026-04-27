#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "code.h"
#include "parser.h"
#include "symboltable.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./assembler <file.asm>\n");
        exit(1);
    }

    char *asm_filename = argv[1];
    int   len          = strlen(asm_filename);

    if (len < 4 || strcmp(asm_filename + len - 4, ".asm") != 0) {
        fprintf(stderr, "Error: File must have .asm extension\n");
        exit(1);
    }


    char hack_filename[256];
    strncpy(hack_filename, asm_filename, len - 4);
    hack_filename[len - 4] = '\0';
    strcat(hack_filename, ".hack");
    char label_buf[256] = {0};
    /* ── Open files ── */
    FILE *asm_file = fopen(asm_filename, "r");
    if (asm_file == NULL) {
        fprintf(stderr, "Error: Could not open asm file.\n");
        exit(1);
    }

    FILE *hack_file = fopen(hack_filename, "w");
    if (hack_file == NULL) {
        fprintf(stderr, "Error: Could not open/create hack file.\n");
        exit(1);
    }

    char buffer[1000];
    char cleanbuffer[1000];
    char dest[10], comp[10], jump[10];

    while (fgets(buffer, sizeof(buffer), asm_file)) {

        strip_comments_and_whitespace(buffer, cleanbuffer);
        cleanbuffer[strcspn(cleanbuffer, "\n")] = '\0';
        if (cleanbuffer[0] == '\0') continue;
        fill_tables(cleanbuffer, label_buf);
    }
    rewind(asm_file);


    while (fgets(buffer, sizeof(buffer), asm_file)) {
        strip_comments_and_whitespace(buffer, cleanbuffer);
        cleanbuffer[strcspn(cleanbuffer, "\n")] = '\0';
        if (cleanbuffer[0] == '\0') continue;

        char type = command_Type(cleanbuffer);

        if (type == 'L') continue;
        
        if (type == 'D') {
            dectobinary(get_decimal(cleanbuffer), hack_file);
        }

        if (type == 'A') {
          char sym[256];
          get_symbol(cleanbuffer, sym);
          dectobinary(fill_variable_tables(sym), hack_file);
        }

       if (type == 'C') {
            parse_C_instruction(cleanbuffer, dest, comp, jump);
            char *d = lookup(dest_table, dest);
            char *c = lookup(comp_table, comp);
            char *j = lookup(jump_table, jump);
            if (d && c && j) {
                assemble_bits(d, c, j, hack_file);
            } else {
                fprintf(stderr, "Error: unknown mnemonic\n");
                exit(1);
            }
        }
    }

    printf("%s -> %s\n", asm_filename, hack_filename);

    fclose(asm_file);
    fclose(hack_file);
    return 0;
}
