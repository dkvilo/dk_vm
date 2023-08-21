#include "vm.h"

#include <stdlib.h> // exit, EXIT_FAILURE
#include <stdio.h> // fprintf, stderr
#include <string.h> // memset

void
vm_init(VM* vm)
{
  vm->pc = 0;
  vm->ACC = 0;
  vm->sp = 0;

  memset(vm->memory, 0, sizeof(vm->memory));
  memset(vm->stack, 0, sizeof(vm->stack));
}

void
vm_print_state(VM* vm)
{

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

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

  #undef RED
  #undef GREEN
  #undef YELLOW
  #undef BLUE
  #undef RESET
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


void
vm_exec(VM* vm, int64_t* code, size_t size)
{

  memcpy(vm->memory, code, size);
  int running = 1;

  while (running) {
    if (vm->pc < 0 || vm->pc >= size) {
        fprintf(stderr, "Error: program counter out of bounds\n");
        exit(EXIT_FAILURE);
    }

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