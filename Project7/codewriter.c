#include <stdio.h>
#include <string.h>


int label_count = 0;

void write_arithmetic(char *command, FILE *asm_file) {
  if (!strcmp(command, "C_add")) {
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "M=M-1\n");
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "D=D+M\n");
        fprintf(asm_file, "M=D\n");
    }
  if (!strcmp(command, "C_sub")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "M=M-1\n"); 
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "D=M-D\n");
        fprintf(asm_file, "M=D\n");

  }
  if (!strcmp(command, "C_neg")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=-M\n");
  }
  if (!strcmp(command, "C_eq")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "M=M-1\n");
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "D=M-D\n");
        fprintf(asm_file, "@EQ_TRUE_%d\n", label_count);
        fprintf(asm_file, "D;JEQ\n");
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=0\n");
        fprintf(asm_file, "@EQ_END_%d\n", label_count);
        fprintf(asm_file, "0;JMP\n");
        fprintf(asm_file, "(EQ_TRUE_%d)\n", label_count);
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=-1\n");
        fprintf(asm_file, "(EQ_END_%d)\n", label_count);
        label_count++;
  }
  if (!strcmp(command, "C_gt")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "M=M-1\n");
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "D=M-D\n");
        fprintf(asm_file, "@GT_TRUE_%d\n", label_count);
        fprintf(asm_file, "D;JGT\n");
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=0\n");
        fprintf(asm_file, "@GT_END_%d\n", label_count);
        fprintf(asm_file, "0;JMP\n");
        fprintf(asm_file, "(GT_TRUE_%d)\n", label_count);
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=-1\n");
        fprintf(asm_file, "(GT_END_%d)\n", label_count);
        label_count++;

  }
  if (!strcmp(command, "C_lt")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "M=M-1\n");
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "D=M-D\n");
        fprintf(asm_file, "@LT_TRUE_%d\n", label_count);
        fprintf(asm_file, "D;JLT\n");
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=0\n");
        fprintf(asm_file, "@LT_END_%d\n", label_count);
        fprintf(asm_file, "0;JMP\n");
        fprintf(asm_file, "(LT_TRUE_%d)\n", label_count);
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "A=M-1\n");
        fprintf(asm_file, "M=-1\n");
        fprintf(asm_file, "(LT_END_%d)\n", label_count);
        label_count++;

  }
  if (!strcmp(command, "C_and")) {
        fprintf(asm_file, "@SP\n");
        fprintf(asm_file, "M=M-1\n");
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "M=D&M\n");  
  }
  if (!strcmp(command, "C_or")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "M=M-1\n"); 
        fprintf(asm_file, "A=M\n");
        fprintf(asm_file, "D=M\n");
        fprintf(asm_file, "A=A-1\n");
        fprintf(asm_file, "M=D|M\n");

  }
  if (!strcmp(command, "C_not")) {
        fprintf(asm_file, "@SP\n"); 
        fprintf(asm_file, "A=M-1\n"); 
        fprintf(asm_file, "M=!M\n");

  }



}

void Write_push_pop(char *command, char *segment, char *index, FILE *asm_file, char *filename) {
  if (!strcmp(command, "C_push")) {
   if (!strcmp(segment, "constant")) {
       fprintf(asm_file, "@%s\n", index);
       fprintf(asm_file, "D=A\n");
       fprintf(asm_file, "@SP\n");
       fprintf(asm_file, "A=M\n");
       fprintf(asm_file, "M=D\n");
       fprintf(asm_file, "@SP\n");
       fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "local")) {
      fprintf(asm_file, "@LCL\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@%s\n", index);
      fprintf(asm_file, "D=D+A\n");
      fprintf(asm_file, "A=D\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "argument")) {
      fprintf(asm_file, "@ARG\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@%s\n", index);
      fprintf(asm_file, "D=D+A\n");
      fprintf(asm_file, "A=D\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "this")) {
      fprintf(asm_file, "@THIS\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@%s\n", index);
      fprintf(asm_file, "D=D+A\n");
      fprintf(asm_file, "A=D\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "that")) {
      fprintf(asm_file, "@THAT\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@%s\n", index);
      fprintf(asm_file, "D=D+A\n");
      fprintf(asm_file, "A=D\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "pointer")) {
      fprintf(asm_file, "@3\n");
      fprintf(asm_file, "D=A\n");
      fprintf(asm_file, "@%s\n", index);
      fprintf(asm_file, "D=D+A\n");
      fprintf(asm_file, "A=D\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "temp")) {
      fprintf(asm_file, "@5\n");
      fprintf(asm_file, "D=A\n");
      fprintf(asm_file, "@%s\n", index);
      fprintf(asm_file, "D=D+A\n");
      fprintf(asm_file, "A=D\n");
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }
   if (!strcmp(segment, "static")) {
      fprintf(asm_file, "@%s.%s\n", filename, index);
      fprintf(asm_file, "D=M\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "A=M\n");
      fprintf(asm_file, "M=D\n");
      fprintf(asm_file, "@SP\n");
      fprintf(asm_file, "M=M+1\n");
   }

  }

  if (!strcmp(command, "C_pop")) {
      if (!strcmp(segment, "local")) {  
          fprintf(asm_file, "@LCL\n"); 
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@%s\n", index);
          fprintf(asm_file, "D=D+A\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "M=D\n");
          fprintf(asm_file, "@SP\n");
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "M=D\n");
      }
      if (!strcmp(segment, "argument")) {  
          fprintf(asm_file, "@ARG\n"); 
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@%s\n", index);
          fprintf(asm_file, "D=D+A\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "M=D\n");
          fprintf(asm_file, "@SP\n");
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "M=D\n");
      }
      if (!strcmp(segment, "this")) {  
          fprintf(asm_file, "@THIS\n"); 
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@%s\n", index);
          fprintf(asm_file, "D=D+A\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "M=D\n");
          fprintf(asm_file, "@SP\n");
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "M=D\n");
      }
      if (!strcmp(segment, "that")) {  
          fprintf(asm_file, "@THAT\n"); 
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@%s\n", index);
          fprintf(asm_file, "D=D+A\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "M=D\n");
          fprintf(asm_file, "@SP\n");
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "M=D\n");
      }
      if (!strcmp(segment, "pointer")) {  
          fprintf(asm_file, "@3\n"); 
          fprintf(asm_file, "D=A\n");
          fprintf(asm_file, "@%s\n", index);
          fprintf(asm_file, "D=D+A\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "M=D\n");
          fprintf(asm_file, "@SP\n");
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "M=D\n");
      }
      if (!strcmp(segment, "temp")) {  
          fprintf(asm_file, "@5\n"); 
          fprintf(asm_file, "D=A\n");
          fprintf(asm_file, "@%s\n", index);
          fprintf(asm_file, "D=D+A\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "M=D\n");
          fprintf(asm_file, "@SP\n");
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@R13\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "M=D\n");
      }
      if (!strcmp(segment, "static")) {  
          fprintf(asm_file, "@SP\n"); 
          fprintf(asm_file, "M=M-1\n");
          fprintf(asm_file, "A=M\n");
          fprintf(asm_file, "D=M\n");
          fprintf(asm_file, "@%s.%s\n", filename, index);
          fprintf(asm_file, "M=D\n");
      }




  }
}
