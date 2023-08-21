#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "vm.h"

void
save_bytecode_to_file(int64_t* bytecode, size_t size, const char* filename);

void
emulate(int64_t bytecode[], size_t size)
{
  VM vm;
  vm_init(&vm);
  vm_exec(&vm, bytecode, size);
  vm_print_state(&vm);
}

void
compile(int64_t bytecode[], size_t size)
{
  const char* include = "%include \"backend/x86_64/std.S\"\n";
  printf("%s", include);
  printf("section .text\n");
  printf("global _start\n");
  printf("_start:\n");

  for (int i = 0; i < size / sizeof(int64_t); i += 4) {

    OpCode opcode = bytecode[i];
    printf(";; %d\n", (uint8_t)opcode);

    if (opcode == PUSH) {
      int64_t value = bytecode[i + 1];
      printf(";; --- PUSH %ld\n", value);
      printf("  push %ld\n", value);
    }

    else if (opcode == LOAD) {
      int64_t value = bytecode[i + 1];
      printf(";; --- LOAD %ld\n", value);
      printf("  push %ld\n", value);
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

int
main(int argc, char** argv)
{

  if (argc < 2) {
    printf("Usage: %s <mode>\n", argv[0]);
    printf("Modes:\n");
    printf("  - emulate\n");
    printf("  - compile\n");
    return 1;
  }

  if (strcmp(argv[1], "emulate") == 0) {
    printf("Emulating...\n");

    int mul_ptr = 0x00000018;
    int div_ptr = 0x00000020;
  
    int64_t bytecode[] = {
      LOAD, 20, 0, 0, // address 0
      PUSH, 0, 0, 0, // address 4

      LOAD, 10, 0, 0, // address 8 
      NOP, 0, 0, 0, // address 12 

      CALL, mul_ptr, 0, 0,  // address 16
      HALT, 0, 0, 0, // address 20

      // Subroutine (function) multiply
      MUL, 2, 0, 0,  // address 24
      CALL, div_ptr, 0, 0, // address 28

      // Subroutine (function) divide
      DIV, 10, 0, 0, // address 32
      RET, 0, 0, 0, // address 36
    };

    emulate(bytecode, sizeof(bytecode));
  } else if (strcmp(argv[1], "compile") == 0) {

    int64_t bytecode[] = {

      LOAD, 10, 0, 0, // rax = 10
      LOAD, 20, 0, 0, // rbx = 20

      ADD,  0,  0, 0, // rax = rax + rbx

      PUSH, 2,  0, 0, // push 2
      MUL,  0,  0, 0, // rax = rax * rbx

      PUSH, 10,  0, 0, // push 10
      DIV,  0,  0, 0, // rax = rax / rbx

      RET,  0,  0, 0, // return rax
    };

    compile(bytecode, sizeof(bytecode));
  } else {
    printf("Unknown mode: %s\n", argv[1]);
    return 1;
  }

  return 0;
}

void
save_bytecode_to_file(int64_t* bytecode, size_t size, const char* filename)
{
  FILE* file = fopen(filename, "wb");
  fwrite(bytecode, 1, size, file);
  fclose(file);
}

void
read_bytecode_from_file(int64_t* bytecode, size_t size, const char* filename)
{
  FILE* file = fopen(filename, "rb");
  fread(bytecode, 1, size, file);
  fclose(file);
}

void
read_file_contents(const char* filename, char* buffer, size_t size)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error: could not open file %s for reading contents\n", filename);
    exit(1);
  }

  fread(buffer, 1, size, file);
  fclose(file);
}
