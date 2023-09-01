#include "code_gen.h"
#include "vm.h"

#include <stdio.h>

void
compile(int64_t bytecode[], size_t size)
{
  printf("%s", "%include \"backend/x86_64/std.S\"\n");
  printf("section .text\n");
  printf("global _start\n");
  printf("_start:\n");

  for (int i = 0; i < size / sizeof(int64_t); i += 4) {

    OpCode opcode = bytecode[i];
    if (opcode == LOAD) {
      int64_t value = bytecode[i + 1];
      printf(";; --- LOAD %lld\n", value);
      printf("  push %lld\n", value);
    }

    else if (opcode == ADD) {
      printf(";; --- ADD\n");
      printf("  pop rax\n");
      printf("  pop rbx\n");
      printf("  add rax, rbx\n");
      printf("  push rax\n");
    }

    else if (opcode == SUB) {
      printf(";; --- SUB\n");
      printf("  pop rax\n");
      printf("  pop rbx\n");
      printf("  sub rax, rbx\n");
      printf("  push rax\n");
    }

    else if (opcode == MUL) {
      printf(";; --- MUL\n");
      printf("  pop rax\n");
      printf("  pop rbx\n");
      printf("  mul rbx\n");
      printf("  push rax\n");
    }

    else if (opcode == DIV) {
      printf(";; --- DIV\n");
      printf("  pop rbx\n");
      printf("  pop rax\n");
      printf("  div rbx\n");
      printf("  push rax\n");
    }

    else {
      continue;
    }
  }

  printf("  pop rdi\n");
  printf("  call .sys_dump\n");

  /* pop return value from stack to  `rdi` */
  printf("  mov rdi, 0\n");
  printf("  call .exit_with_value\n");
}