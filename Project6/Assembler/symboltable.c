#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symboltable.h"
#include "parser.h"

int label_count = 0;
int variable_count = 0;
int rom_address = 0;
int next_variable_address = 16;


SymbolTable predefined_symbol_table[] = {
    {"SP",     0},  {"LCL",    1},  {"ARG",  2},
    {"THIS",   3},  {"THAT",   4},
    {"R0",     0},  {"R1",     1},  {"R2",   2},
    {"R3",     3},  {"R4",     4},  {"R5",   5},
    {"R6",     6},  {"R7",     7},  {"R8",   8},
    {"R9",     9},  {"R10",   10},  {"R11", 11},
    {"R12",   12},  {"R13",   13},  {"R14", 14},
    {"R15",   15},
    {"SCREEN", 16384}, {"KBD", 24576},
    {NULL , -1}
};

SymbolTable labels_table[256];
SymbolTable variable_table[256];

void fill_tables(char *line, char *label_buffer) {
    if (command_Type(line) == 'L') {
        sscanf(line, "(%[^)])", label_buffer);
        labels_table[label_count].label = strdup(label_buffer);
        labels_table[label_count].address = rom_address;
        label_count++;
    } else {
        rom_address++;
    }
  
}

int fill_variable_tables(char *variable_symbol) {
    int addr = lookuptable(variable_symbol);
    if (addr == -1) {
        variable_table[variable_count].label = strdup(variable_symbol);
        variable_table[variable_count].address = next_variable_address;
        variable_count++;
        addr = next_variable_address++;
    }
    return addr;
}


int lookuptable(char *symbol_name) {
    for (int i = 0; predefined_symbol_table[i].label != NULL; i++)
        if (strcmp(predefined_symbol_table[i].label, symbol_name) == 0)
            return predefined_symbol_table[i].address;

    for (int i = 0; i < label_count; i++)
        if (strcmp(labels_table[i].label, symbol_name) == 0)
            return labels_table[i].address;

    for (int i = 0; i < variable_count; i++)
        if (strcmp(variable_table[i].label, symbol_name) == 0)
            return variable_table[i].address;

    return -1;  
}
