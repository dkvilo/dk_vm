#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "vm.h"

#include "dk.h"
#include "dk_token.h"
#include "dk_lexer.h"

void
save_bytecode_to_file(int64_t* bytecode, size_t size, const char* filename);

void
compile(int64_t bytecode[], size_t size)
{
  const int8_t* include = "%include \"backend/x86_64/std.S\"\n";
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


int8_t* ext__dk_token_type_to_str(dk_token_type_t type)
{
  if (type == DK_TOKEN_IDENTIFIER) {
    return "identifier";
  }

  if (type == DK_TOKEN_NUMBER) {
    return "number";
  }

  if (type == DK_TOKEN_STRING) {
    return "string";
  }

  if (type == DK_TOKEN_OPERATOR) {
    return "operator";
  }

  if (type == DK_TOKEN_KEYWORD) {
    return "keyword";
  }

  if (type == DK_TOKEN_END_OF_FILE) {
    return "end of file";
  }

  if (type == DK_TOKEN_END_OF_STATEMENT) {
    return "end of statement";
  }

  if (type == DK_TOKEN_WHITESPACE) {
    return "whitespace";
  }

  if (type == DK_TOKEN_COMMENT) {
    return "comment";
  }

  return "unknown";
}

#define BYTECODE_SIZE 256

static int64_t *__bytecode = NULL;

bool parse_variable_declaration(dk_lexer_t lexer, int itteration)
{ 

  bool is_variable_declaration_valid = true;

  lexer.cursor++;
  dk_token_t *token  = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_IDENTIFIER) {
    printf("Error: expected identifier, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  lexer.cursor++;
  token = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_OPERATOR) {
    printf("Error: expected operator, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  lexer.cursor++;
  if (strcmp(token->p_data, "=") != 0) {
    printf("Error: expected assigment operator '=', but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  token = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_NUMBER) {
    printf("Error: expected number, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  /* Generate bytecode */

  // calculate offset for bytecode array
  int64_t offset = 0;
  if (itteration > 0) {
    offset = itteration * 4;
  }

  __bytecode[offset + 4] = LOAD;
  __bytecode[offset + 5] = atoi(token->p_data);
  __bytecode[offset + 6] = 0;
  __bytecode[offset + 7] = 0;

  __bytecode[offset + 8] = PUSH;
  __bytecode[offset + 9] = 0;
  __bytecode[offset + 10] = 0;
  __bytecode[offset + 11] = 0;

  /* END */

  if (token->type == DK_TOKEN_END_OF_FILE) {
    exit(1);
  }

  return is_variable_declaration_valid;
}

// TODO (David) complete this function, now we don't do anything with vaalues just push them to stack

bool parse_addition(dk_lexer_t lexer, int itteration)
{
  bool is_addition_valid = true;

  lexer.cursor++;
  dk_token_t *token = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_NUMBER) {
    printf("Error: expected number, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_addition_valid = false;
    exit(1);
  }

  int64_t a = atoi(token->p_data);

  lexer.cursor++;
  token = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_OPERATOR) {
    printf("Error: expected operator, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_addition_valid = false;
    exit(1);
  }

  lexer.cursor++;
  token = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_NUMBER) {
    printf("Error: expected number, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_addition_valid = false;
    exit(1);
  }

  int b = atoi(token->p_data);


  int64_t offset = 0;
  if (itteration > 0) {
    offset = itteration * 4;
  }

  /* Generate bytecode */
  __bytecode[offset + 4] = LOAD;
  __bytecode[offset + 5] = a;
  __bytecode[offset + 6] = 0;
  __bytecode[offset + 7] = 0;

  __bytecode[offset + 8] = PUSH;
  __bytecode[offset + 9] = 0;
  __bytecode[offset + 10] = 0;
  __bytecode[offset + 11] = 0;

  __bytecode[offset + 12] = LOAD;
  __bytecode[offset + 13] = b;
  __bytecode[offset + 14] = 0;
  __bytecode[offset + 15] = 0;

  __bytecode[offset + 16] = PUSH;
  __bytecode[offset + 17] = 0;
  __bytecode[offset + 18] = 0;
  __bytecode[offset + 19] = 0;

  /* END */

  return is_addition_valid;
}

void parse_and_tokenize(const char* filename)
{
  u32_t p_size = 0;
  u8_t *p_data = dk_read_file("./lex/variable.kk", &p_size);
  dk_lexer_t *lex = dk_lexer_create(p_data, p_size * sizeof(u8_t));

  int variable_itteration = 0;

  while (true) {

    dk_token_t *token = dk_lexer_next_token(lex);

    if (token->type == DK_TOKEN_WHITESPACE || token->type == DK_TOKEN_COMMENT) {
      continue;
    }

#if 0
    dk_lexer_print_token(token);
#endif

    if (token->type == DK_TOKEN_KEYWORD) {
      if (strcmp(token->p_data, "i32") == 0) {
        if (!parse_variable_declaration(*lex, variable_itteration)) {
          printf("Illegal Variable declaration\n");
        }
      }
    }

    if (token->type == DK_TOKEN_IDENTIFIER) {
      if (strcmp(token->p_data, "add") == 0) {
        if (!parse_addition(*lex, variable_itteration)) {
          printf("Illegal addition\n");
        }
      }
    }

    if (token->type == DK_TOKEN_UNKNOWN) {
      printf("Error: unknown token\n");
      exit(1);
    }

    if (token->type == DK_TOKEN_END_OF_FILE || token->type == DK_TOKEN_UNKNOWN) {
      break;
    }

    variable_itteration++;

    lex->cursor++;
  }

  dk_lexer_destroy(lex);
  free(p_data);

  // We are done with parsing, so we can add HALT instruction to the end of bytecode
  __bytecode[BYTECODE_SIZE - 4] = HALT;
  __bytecode[BYTECODE_SIZE - 3] = 0;
  __bytecode[BYTECODE_SIZE - 2] = 0;
  __bytecode[BYTECODE_SIZE - 1] = 0;

  VM vm;
  vm_init(&vm);
  vm_exec(&vm, __bytecode, sizeof(i64_t) * BYTECODE_SIZE);
  vm_print_state(&vm);
}

int
main(int argc, char** argv)
{

  __bytecode = (int64_t *)malloc(sizeof(int64_t) * BYTECODE_SIZE);
  memset(__bytecode, 0, sizeof(int64_t) * BYTECODE_SIZE);

  parse_and_tokenize("./lex/variable.kk");

 return 0;

  if (argc < 2) {
    printf("Usage: %s <mode>\n", argv[0]);
    printf("Modes:\n");
    printf("  - emulate\n");
    printf("  - compile\n");
    return 1;
  }

  if (strcmp(argv[1], "emulate") == 0) {
    printf("Emulating...\n");

    /*
     * NOTE (David) this is the old architecture for VM
     * */
    uintptr_t mul_ptr = 0x00000018;
    intptr_t div_ptr = 0x00000020;

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
   
    // memcpy(__bytecode, bytecode, sizeof(bytecode));

    VM vm;
    vm_init(&vm);
    vm_exec(&vm, bytecode, sizeof(bytecode));

    vm_print_state(&vm);

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
