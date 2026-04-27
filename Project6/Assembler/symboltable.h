#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct {
    char *label;
    int address;
} SymbolTable;

extern int label_count;
extern int variable_count;
extern int rom_address;
extern int next_variable_address;

extern SymbolTable predefined_symbol_table[];
extern SymbolTable labels_table[256];
extern SymbolTable variable_table[256];

void fill_tables(char *line, char *label_buffer);
int lookuptable(char *symbol_name);
int fill_variable_tables(char *variable_symbol);
#endif
