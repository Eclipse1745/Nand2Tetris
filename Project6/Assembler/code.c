#include <stdio.h>
#include <string.h>



typedef struct {
    char *mnemonic;
    char *bits;
} Entry;


/* ── Comp table (a-bit + c1-c6) ── */
Entry comp_table[] = {
    {"0",   "0101010"},
    {"1",   "0111111"},
    {"-1",  "0111010"},
    {"D",   "0001100"},
    {"A",   "0110000"},
    {"!D",  "0001101"},
    {"!A",  "0110001"},
    {"-D",  "0001111"},
    {"-A",  "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},
    {"M",   "1110000"},
    {"!M",  "1110001"},
    {"-M",  "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"},
    {NULL,  NULL}
};


Entry dest_table[] = {
    {"",    "000"},
    {"M",   "001"},
    {"D",   "010"},
    {"MD",  "011"},
    {"A",   "100"},
    {"AM",  "101"},
    {"AD",  "110"},
    {"AMD", "111"},
    {NULL,  NULL}
};

Entry jump_table[] = {
    {"",    "000"},
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"},
    {NULL,  NULL}
};



char *lookup(Entry *table, char *mnemonic) {
    for (int i = 0; table[i].mnemonic != NULL; i++) {
        if (strcmp(table[i].mnemonic, mnemonic) == 0)
            return table[i].bits;
    }
    return NULL;
}


void dectobinary(int n, FILE *file) {
    char binaryArray[15] = {0};
    int i = 0;
    while (n > 0) {
        binaryArray[i++] = n % 2;
        n /= 2;
    }

    fprintf(file, "0");
    for (int j = 14; j >= 0; j--) {
        fprintf(file, "%d", binaryArray[j]);
    }
    fprintf(file, "\n");
}


/* Writes a fully assembled C-instruction to file.
   Format: 111 + comp(7) + dest(3) + jump(3) */
void assemble_bits(char *dest_bits, char *comp_bits, char *jump_bits, FILE *file) {
    fprintf(file, "111%s%s%s\n", comp_bits, dest_bits, jump_bits);
}
