#ifndef CODE_WRITER_H
#define CODE_WRITER_H

void write_arithmetic(char *command, FILE *asm_file);
void Write_push_pop(char *command, char *segment, char *index, FILE *asm_file, char *filname); 
void write_label(FILE *asm_file, char *label);
void write_call(FILE *asm_file, char *function_name , char *num_arg);
void write_goto(FILE *asm_file, char *label);
void write_ifgoto(FILE *asm_file, char *label);
void write_function(FILE *asm_file, char *function_name, char *num_locals);
void write_call(FILE *asm_file, char *function_name , char *num_arg); 
void write_return(FILE *asm_file);
void write_bootstrap(FILE *asm_file); 

#endif // !CODE_WRITER_H
