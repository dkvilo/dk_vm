#if !defined(ME_VM)
#define ME_VM

#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024 * 1000
#define STACK_SIZE 256

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
  DEC = 0x19, // Decrement ACC (parameter is ignored)
  INC = 0x1A, // Increment ACC (parameter is ignored)
  STORE = 0x1B, // Store ACC in memory (parameter is memory address)

  HALT = 0xFF
} OpCode;

typedef struct
{
  uint64_t pc;
  uint64_t sp;
  int64_t ACC;
  int64_t memory[MEMORY_SIZE];
  int64_t stack[STACK_SIZE];
} VM;

void
vm_init(VM* vm);

void
vm_exec(VM* vm, int64_t* code, size_t size);

char*
inst_to_str(OpCode opcode);

void
vm_print_state(VM* vm);

#endif // ME_VM
