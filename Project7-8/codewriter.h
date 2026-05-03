#ifndef CODE_WRITER_H
#define CODE_WRITER_H

void write_arithmetic(char *command, FILE *asm_file);
void Write_push_pop(char *command, char *segment, char *index, FILE *asm_file, char *filname); 
void write_label(FILE *asm_file, char *label);

#endif // !CODE_WRITER_H
