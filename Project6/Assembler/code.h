#ifndef CODE_H
#define CODE_H

typedef struct {
    char *mnemonic;
    char *bits;
} Entry;

char *lookup(Entry *table, char *mnemonic);
void dectobinary(int n, FILE *file);
char assemble_bits (char *dest_bits , char *comp_bits , char *jump_bits, FILE *file );

extern Entry comp_table[];
extern Entry dest_table[];
extern Entry jump_table[];

#endif
