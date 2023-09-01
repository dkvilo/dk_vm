#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "vm.h"
#include "bytecode_parser.h"
#include "symbol_table.h"
#include "code_gen.h"

#define BYTECODE_SIZE 1024
static int64_t *__bytecode = NULL;

static symbol_hashmap_t *symbol_table = NULL;

int
main(int argc, char** argv)
{

  if (argc < 2 || strcmp(argv[1], "emulate") != 0 && strcmp(argv[1], "compile") != 0) {
    printf("Unknown mode: %s\n", argv[1]);
    printf("Usage: %s <mode>\n", argv[0]);
    printf("Modes:\n");
    printf("  - emulate\n");
    printf("  - compile\n");
    return 1;
  }

  if (strcmp(argv[1], "emulate") != 0 && strcmp(argv[1], "compile") != 0 && argc < 3) {
    printf("Usage: %s %s <filename>\n", argv[0], argv[1]);
    return 1;
  }

  symbol_table = (symbol_hashmap_t *)malloc(sizeof(symbol_hashmap_t));
  symbol_table->symbols = (symbol_t *)malloc(sizeof(symbol_t) * BYTECODE_SIZE);
  symbol_table->keys = (char **)malloc(sizeof(char *) * BYTECODE_SIZE);

  __bytecode = (int64_t *)malloc(sizeof(int64_t) * BYTECODE_SIZE);
  memset(__bytecode, 0, sizeof(int64_t) * BYTECODE_SIZE);

  if (strcmp(argv[1], "compile") == 0) {
    parse_and_tokenize(argv[2], __bytecode, BYTECODE_SIZE, symbol_table);
    compile(__bytecode, sizeof(__bytecode) * BYTECODE_SIZE);
  }

  if (strcmp(argv[1], "emulate") == 0) {
    parse_and_tokenize(argv[2], __bytecode, BYTECODE_SIZE, symbol_table);

    VM vm;
    vm_init(&vm);
    vm_exec(&vm, __bytecode, sizeof(int64_t) * BYTECODE_SIZE);
    vm_print_state(&vm);

    printf("-----------------------\nSymbol table (%d):\n", symbol_table->count);
    symbol_table_print(symbol_table);
  }

  return 0;
}
