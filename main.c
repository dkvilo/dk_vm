/**
 * @file main.c
 * @author David Kviloria (dkviloria at gmail dot com)
 * @brief 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>

// Instruction set
typedef enum
{
  NOP = 0x0,
  LOAD = 0x1,
  ADD = 0x2,
  DIV = 0x3,
  MUL = 0x4,
  SUB = 0x5,
  JMP = 0x6,
  CALL = 0x7,
  JZ = 0x8,
  JNZ = 0x9,
  PUSH = 0xA,
  POP = 0xB,
  RET = 0xE,
  LOADS = 0x10,
  
  CALL_IFGT = 0x11, // call if greater than (if ACC > operand1)
  CALL_IFLT = 0x12, // call if less than (if ACC < operand1)
  CALL_IFEQ = 0x13, // call if equal (if ACC == operand1)
  CALL_IFNEQ = 0x14, // call if not equal (if ACC != operand1)

  HALT_IFEQ = 0x15, // halt if equal (if ACC == operand1)
  HALT_IFNEQ = 0x16, // halt if not equal (if ACC != operand1)
  HALT_IFGT = 0x17, // halt if greater than (if ACC > operand1)
  HALT_IFLT = 0x18, // halt if less than (if ACC < operand1)

  DEC = 0x19, // Decrement ACC (parameter is ignored)
  INC = 0x1A, // Increment ACC (parameter is ignored)

  HALT = 0xFF
} OpCode;

#define MEMORY_SIZE 1024
#define STACK_SIZE 256  

// VM structure
typedef struct
{
  uint64_t pc;
  uint64_t sp;
  int64_t ACC;
  int64_t memory[MEMORY_SIZE];
  int64_t stack[STACK_SIZE];
} VM;

// VM functions
void
vm_init(VM* vm)
{
  vm->pc = 0;
  vm->ACC = 0;
  vm->sp = 0;

  memset(vm->memory, 0, sizeof(vm->memory));
  memset(vm->stack, 0, sizeof(vm->stack));
}
char*
inst_to_str(OpCode opcode);

void
vm_exec(VM* vm, int64_t* code, size_t size)
{
  memcpy(vm->memory, code, size);

  int running = 1;

  while (running) {

    // if (vm->pc < 0 || vm->pc >= size) {
    //     fprintf(stderr, "Error: program counter out of bounds\n");
    //     exit(EXIT_FAILURE);
    // }


    OpCode instruction = vm->memory[vm->pc++];
    
    int64_t operand1 = vm->memory[vm->pc++];
    int64_t operand2 = vm->memory[vm->pc++];
    int64_t operand3 = vm->memory[vm->pc++];

    switch (instruction) {
      case NOP: // no operation
        break;

      case LOAD:
        vm->ACC = operand1;
        break;

      case PUSH:
        if (vm->sp >= STACK_SIZE) {
          printf("Stack overflow error!\n");
          return;
        }
        vm->stack[vm->sp++] = vm->ACC;
        break;

      case LOADS:
        if (operand1 >= STACK_SIZE) {
          printf("Stack underflow error!\n");
          return;
        }
        vm->ACC = vm->stack[operand1];
        break;

      case POP:
        if (vm->sp <= 0) {
          printf("Stack underflow error!\n");
          return;
        }
        vm->ACC = vm->stack[--vm->sp];
        break;

      case ADD:
        vm->ACC += operand1;
        break;

      case SUB:
        vm->ACC -= operand1;
        break;

      case MUL:
        vm->ACC *= operand1;
        break;

      case DIV:
        vm->ACC /= operand1;
        break;

      case JMP:
        vm->pc = operand1;
        break;

      case DEC:
        vm->ACC--;
        break;

      case JZ:
        if (vm->ACC == 0) {
          vm->pc = operand1;
        }
        break;

      case CALL:
        if (vm->sp >= STACK_SIZE) {
          printf("Stack overflow error!\n");
          return;
        }
        // push the address of the next instruction onto the stack
        vm->stack[vm->sp++] = vm->pc;
        // jump to the address specified by the operand
        vm->pc = operand1;
        break;
      
      case CALL_IFEQ:{
        if (vm->ACC == operand2) {
          if (vm->sp >= STACK_SIZE) {
            printf("Stack overflow error!\n");
            return;
          }
          // push the address of the next instruction onto the stack
          vm->stack[vm->sp++] = vm->pc;
          // jump to the address specified by the operand
          vm->pc = operand1;
        }
      }
        break;

      case CALL_IFNEQ:{
        if (vm->ACC != operand2) {
          if (vm->sp >= STACK_SIZE) {
            printf("Stack overflow error!\n");
            return;
          }
          // push the address of the next instruction onto the stack
          vm->stack[vm->sp++] = vm->pc;
          // jump to the address specified by the operand
          vm->pc = operand1;
        }
      }
        break;

      case CALL_IFGT:{
        if (vm->ACC > operand2) {
          if (vm->sp >= STACK_SIZE) {
            printf("Stack overflow error!\n");
            return;
          }
          // push the address of the next instruction onto the stack
          vm->stack[vm->sp++] = vm->pc;
          // jump to the address specified by the operand
          vm->pc = operand1;
        }
      }
        break;

      case CALL_IFLT:{
        if (vm->ACC < operand2) {
          if (vm->sp >= STACK_SIZE) {
            printf("Stack overflow error!\n");
            return;
          }
          // push the address of the next instruction onto the stack
          vm->stack[vm->sp++] = vm->pc;
          // jump to the address specified by the operand
          vm->pc = operand1;
        }
      }
        break;

      case RET:
        if (vm->sp <= 0) {
          printf("Stack underflow error!\n");
          return;
        }
        // pop the return address from the stack and jump to it
        vm->pc = vm->stack[--vm->sp];
        break;

      case HALT_IFEQ:
        if (vm->ACC == operand1) {
          running = 0; // stop the program
        }
        break;

      case HALT_IFNEQ:
        if (vm->ACC != operand1) {
          running = 0; // stop the program
        }
        break;

      case HALT_IFGT:
        if (vm->ACC > operand1) {
          running = 0; // stop the program
        }
        break;

      case HALT_IFLT:
        if (vm->ACC < operand1) {
          running = 0; // stop the program
        }
        break;



      case HALT:
        running = 0; // stop the program
        break;
    }
  }
}

char*
inst_to_str(OpCode opcode)
{
  switch (opcode) {
    case NOP:
      return "NOP";
      break;

    case LOAD:
      return "LOAD";
      break;

    case ADD:
      return "ADD";
      break;

    case DIV:
      return "DIV";
      break;

    case MUL:
      return "MUL";
      break;

    case SUB:
      return "SUB";
      break;

    case JMP:
      return "JMP";
      break;

    case CALL_IFEQ:
    case CALL_IFNEQ:
    case CALL_IFGT:
    case CALL_IFLT:
    case CALL:
      return "CALL";
      break;

    case JZ:
      return "JZ";
      break;

    case JNZ:
      return "JNZ";
      break;

    case PUSH:
      return "PUSH";
      break;

    case POP:
      return "POP";
      break;

    case DEC:
      return "DEC";
      break;

    case INC:
      return "INC";
      break;

    case LOADS:
      return "LOADS";
      break;

    case HALT_IFEQ:
    case HALT_IFNEQ:
    case HALT_IFGT:
    case HALT_IFLT:
    case HALT:
      return "HALT";
      break;

    case RET:
      return "RET";
      break;

    default:
      return "UNKNOWN";
      break;
  }
}

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

void
print_state(VM* vm)
{
  printf("\nSTACK: \n\n");
  printf(" - [");
  for (int i = 0; i < vm->sp; i++) {
    printf(YELLOW"%ld"RESET, vm->stack[i]);
    if (i < vm->sp - 1) {
      printf(", ");
    }
  }
  printf("]\n\n");

  printf("Memory:\n\n");
  for (int32_t i = 0; i < MEMORY_SIZE; i += 4) {
    if (vm->memory[i] == 0 && vm->memory[i + 1] == 0 &&
        vm->memory[i + 2] == 0 && vm->memory[i + 3] == 0) {
      continue;
    }
    if ((OpCode)vm->memory[i] == CALL || 
      (OpCode)vm->memory[i] == CALL_IFEQ ||
      (OpCode)vm->memory[i] == CALL_IFNEQ ||
      (OpCode)vm->memory[i] == CALL_IFLT ||
      (OpCode)vm->memory[i] == CALL_IFGT ||
      (OpCode)vm->memory[i] == RET
    ) {
    printf(YELLOW" - [0x%02lx\t%ld\t%ld\t%ld]\t\t%s\t\taddr\t0x%08x\n"RESET,
           vm->memory[i],
           vm->memory[i + 1],
           vm->memory[i + 2],
           vm->memory[i + 3],
           inst_to_str((OpCode)vm->memory[i]),
           i);
    } else {
    printf(" - [0x%02lx\t%ld\t%ld\t%ld]\t\t%s\t\taddr\t0x%08x\n",
           vm->memory[i],
           vm->memory[i + 1],
           vm->memory[i + 2],
           vm->memory[i + 3],
           inst_to_str((OpCode)vm->memory[i]),
           i);
           }
  }
  printf("\n");
  printf("[ACC %ld | ", vm->ACC);
  printf("PC %ld | ", vm->pc);
  printf("SP %ld]\n\n", vm->sp);

  printf("Memory Footprint: %ld/%ld Bytes\n\n", vm->pc * sizeof(uint64_t), sizeof(int32_t) * MEMORY_SIZE);
}

char*
generate_checksum(const char* filename)
{
  char* command = (char*)malloc(sizeof(char) * 256);
  sprintf(command, "md5sum %s", filename);
  FILE* file = popen(command, "r");
  char* checksum = (char*)malloc(sizeof(char) * 256);
  fread(checksum, 1, 256, file);
  pclose(file);
  return checksum;
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

bool
cache_exists(const char* filename)
{
  if (access(filename, F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}


#define MAX_INSTRUCTION_SIZE 100

typedef enum {
    OP_HLT = 0,
    OP_ADD = 1,
    OP_SUB = 2,
    OP_MUL = 3,
    OP_DIV = 4,
    OP_LOAD = 5,
    OP_PUSH = 6,
} LexOpCode;

int64_t parse_operand(char* str) {
    char* endptr;
    int64_t operand = strtoll(str, &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Error: invalid operand\n");
        exit(EXIT_FAILURE);
    }
    return operand;
}

int64_t* parse_program(char* program, size_t* size) {
    int64_t* code = malloc(MAX_INSTRUCTION_SIZE * sizeof(int64_t));
    *size = 0;

    char* token = strtok(program, " \n");
    while (token != NULL) {
        if (strcmp(token, "HALT") == 0) {
            code[(*size)++] = OP_HLT;
        } else if (strcmp(token, "ADD") == 0) {
            code[(*size)++] = OP_ADD;
            token = strtok(NULL, " \n");
            if (token == NULL) {
                fprintf(stderr, "Error: missing operand\n");
                exit(EXIT_FAILURE);
            }
            code[(*size)++] = parse_operand(token);
        } 
        else if (strcmp(token, "LOAD") == 0) {
            code[(*size)++] = OP_LOAD;
            token = strtok(NULL, " \n");
            if (token == NULL) {
                fprintf(stderr, "Error: missing operand\n");
                exit(EXIT_FAILURE);
            }
            code[(*size)++] = parse_operand(token);
        } 
        else if (strcmp(token, "PUSH") == 0) {
            code[(*size)++] = OP_PUSH;
            token = strtok(NULL, " \n");
            if (token == NULL) {
                fprintf(stderr, "Error: missing operand\n");
                exit(EXIT_FAILURE);
            }
            code[(*size)++] = parse_operand(token);
        }
        else if (strcmp(token, "SUB") == 0) {
            code[(*size)++] = OP_SUB;
            token = strtok(NULL, " \n");
            if (token == NULL) {
                fprintf(stderr, "Error: missing operand\n");
                exit(EXIT_FAILURE);
            }
            code[(*size)++] = parse_operand(token);
        } else if (strcmp(token, "MUL") == 0) {
            code[(*size)++] = OP_MUL;
            token = strtok(NULL, " \n");
            if (token == NULL) {
                fprintf(stderr, "Error: missing operand\n");
                exit(EXIT_FAILURE);
            }
            code[(*size)++] = parse_operand(token);
        } else if (strcmp(token, "DIV") == 0) {
            code[(*size)++] = OP_DIV;
            token = strtok(NULL, " \n");
            if (token == NULL) {
                fprintf(stderr, "Error: missing operand\n");
                exit(EXIT_FAILURE);
            }
            code[(*size)++] = parse_operand(token);
        } else {
            fprintf(stderr, "Error: unknown instruction %s\n", token);
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " \n");
    }

    return code;
}


int
main(int argc, char** argv)
{

#if 0

  bool is_cache_enabled = false;
  
  is_cache_enabled =
  (argc > 1 && strcmp(argv[1], "--cache") == 0 ? true : false);

  char* file_contents = (char*)malloc(sizeof(char) * 256);
  int file_size = 256;

  read_file_contents("source.as", file_contents, file_size);

  printf("%s\n", file_contents);

  unsigned char _bytecode[256];
  assemble(file_contents, _bytecode);

  if (is_cache_enabled) {
    char* check_sum = generate_checksum("source.as");
    if (cache_exists(check_sum)) {
      printf("Read from cache\n");
      read_bytecode_from_file(bytecode, sizeof(bytecode), check_sum);
    } else {
      save_bytecode_to_file(bytecode, sizeof(bytecode), check_sum);
    }
  } else {
    assemble(file_contents, bytecode);
  }
#endif

  int function_ptr = 0x00000018;
  
  int64_t bytecode[] = {
    LOAD, -1123, 0, 0, // address 0
    PUSH, 0, 0, 0, // address 4
    LOAD, -10, 0, 0, // address 8
    NOP, 0, 0, 0, // address 12
    CALL, function_ptr, 0, 0,  // address 16
    HALT, 0, 0, 0, // address 20

    // Subroutine
    MUL, -2, 0, 0, // address 24
    RET, 0, 0, 0,

    MUL, 2, 0, 0,
    RET, 0, 0, 0,

    SUB, 1, 0, 0,
    RET, 0, 0, 0,

    DIV, 2, 0, 0,
    RET, 0, 0, 0,
  };


  VM vm;
  vm_init(&vm);
  vm_exec(&vm, bytecode, sizeof(bytecode));

  save_bytecode_to_file(bytecode, sizeof(bytecode), "test.bin");

  print_state(&vm);

  return 0;
}
