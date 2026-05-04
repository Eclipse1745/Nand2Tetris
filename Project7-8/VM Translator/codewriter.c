#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void write_label(FILE *asm_file, char *label) {
  fprintf(asm_file, "(%s)\n", label);
}

void write_goto(FILE *asm_file, char *label) {
  fprintf(asm_file, "@%s\n", label);
  fprintf(asm_file, "0;JMP\n");
}

void write_ifgoto(FILE *asm_file, char *label) {
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=M-1\n");
  fprintf(asm_file, "A=M\n");
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@%s\n", label);
  fprintf(asm_file, "D;JNE\n");
}

void write_call(FILE *asm_file, char *function_name , char *num_arg) {
  fprintf(asm_file, "@%s$%d\n",function_name , label_count);// push return-address
  fprintf(asm_file, "D=A\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "A=M\n");
  fprintf(asm_file, "M=D\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=M+1\n");

  fprintf(asm_file, "@LCL\n"); // push LCL 
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "A=M\n");
  fprintf(asm_file, "M=D\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=M+1\n");

  fprintf(asm_file, "@ARG\n"); // push ARGS
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "A=M\n");
  fprintf(asm_file, "M=D\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=M+1\n");

  fprintf(asm_file, "@THIS\n"); // push THIS
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "A=M\n");
  fprintf(asm_file, "M=D\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=M+1\n");
  
  fprintf(asm_file, "@THAT\n"); // push THAT
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "A=M\n");
  fprintf(asm_file, "M=D\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=M+1\n");
  
  fprintf(asm_file, "@SP\n"); // reposition ARG to
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@%s\n", num_arg);
  fprintf(asm_file, "D=D-A\n");
  fprintf(asm_file, "@5\n");
  fprintf(asm_file, "D=D-A\n");
  fprintf(asm_file, "@ARG\n");
  fprintf(asm_file, "M=D\n");

  fprintf(asm_file, "@SP\n"); // reposition LCL
  fprintf(asm_file, "D=M\n");
  fprintf(asm_file, "@LCL\n");
  fprintf(asm_file, "M=D\n");

  fprintf(asm_file, "@%s\n", function_name); // transfer control
  fprintf(asm_file, "0;JMP\n");

  fprintf(asm_file, "(%s$%d)\n", function_name , label_count); // declare a label for the return-address
  label_count++;
}

void write_function(FILE *asm_file, char *function_name, char *num_locals) {
  fprintf(asm_file, "(%s)\n", function_name);

   int k = atoi(num_locals);
    for (int i = 0; i < k; i++) {
     fprintf(asm_file, "@SP\n");
     fprintf(asm_file, "A=M\n");
     fprintf(asm_file, "M=0\n");
     fprintf(asm_file, "@SP\n");
     fprintf(asm_file, "M=M+1\n");
}
}
void write_return(FILE *asm_file) {
   // FRAME = LCL
   fprintf(asm_file, "@LCL\n");
   fprintf(asm_file, "D=M\n"); 
   fprintf(asm_file, "@FRAME\n");
   fprintf(asm_file, "M=D\n");

   // RET = *(FRAME-5) 
   fprintf(asm_file, "@5\n");
   fprintf(asm_file, "D=D-A\n");
   fprintf(asm_file, "A=D\n");
   fprintf(asm_file, "D=M\n");
   fprintf(asm_file, "@return_address\n");
   fprintf(asm_file, "M=D\n");
    
   // *ARG = pop()
   fprintf(asm_file, "@SP\n");
   fprintf(asm_file, "M=M-1\n");
   fprintf(asm_file, "A=M\n");
   fprintf(asm_file, "D=M\n");
   fprintf(asm_file, "@ARG\n");
   fprintf(asm_file, "A=M\n");
   fprintf(asm_file, "M=D\n");
   
   // SP = ARG + 1
   fprintf(asm_file, "@ARG\n");
   fprintf(asm_file, "D=M+1\n");
   fprintf(asm_file, "@SP\n");
   fprintf(asm_file, "M=D\n");

   // THAT = *(FRAME-1)
   fprintf(asm_file, "@FRAME\n");
   fprintf(asm_file, "D=M-1\n");
   fprintf(asm_file, "A=D\n");
   fprintf(asm_file, "D=M\n");
   fprintf(asm_file, "@THAT\n");
   fprintf(asm_file, "M=D\n");

   // THIS = *(FRAME-2)
   fprintf(asm_file, "@2\n");
   fprintf(asm_file, "D=A\n");
   fprintf(asm_file, "@FRAME\n");
   fprintf(asm_file, "D=M-D\n");
   fprintf(asm_file, "A=D\n");
   fprintf(asm_file, "D=M\n");
   fprintf(asm_file, "@THIS\n");
   fprintf(asm_file, "M=D\n");
    
   // ARG = *(FRAME-3)
   fprintf(asm_file, "@3\n");
   fprintf(asm_file, "D=A\n");
   fprintf(asm_file, "@FRAME\n");
   fprintf(asm_file, "D=M-D\n");
   fprintf(asm_file, "A=D\n");
   fprintf(asm_file, "D=M\n");
   fprintf(asm_file, "@ARG\n");
   fprintf(asm_file, "M=D\n");

   // LCL = *(FRAME-4)
   fprintf(asm_file, "@4\n");
   fprintf(asm_file, "D=A\n");
   fprintf(asm_file, "@FRAME\n");
   fprintf(asm_file, "D=M-D\n");
   fprintf(asm_file, "A=D\n");
   fprintf(asm_file, "D=M\n");
   fprintf(asm_file, "@LCL\n");
   fprintf(asm_file, "M=D\n");

   // goto RET
   fprintf(asm_file, "@return_address\n");
   fprintf(asm_file, "A=M\n");
   fprintf(asm_file, "0;JMP\n");
   
}

void write_bootstrap(FILE *asm_file) {
  fprintf(asm_file, "@256\n");
  fprintf(asm_file, "D=A\n");
  fprintf(asm_file, "@SP\n");
  fprintf(asm_file, "M=D\n");
  write_call(asm_file, "Sys.init", "0");
}
