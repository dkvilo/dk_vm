#if !defined(ME_SYMBOL_TABLE_)
#define ME_SYMBOL_TABLE_

#include <stdint.h>
#include <stdbool.h>

typedef struct symbol_t {
  char *name;
  union
  {
    int64_t value;
    int64_t *address; // address in memory
  };
} symbol_t;

typedef struct symbol_hashmap_t {
  symbol_t *symbols; // symbol
  char **keys; // symbol name
  int count;
} symbol_hashmap_t;

void symbol_table_add(symbol_hashmap_t *table, char *name, int64_t value);

symbol_t symbol_table_get_by_index(symbol_hashmap_t *table, int index);

bool symbol_table_contains(symbol_hashmap_t *table, char *name);

symbol_t symbol_table_get(symbol_hashmap_t *table, char *name);

void symbol_table_remove(symbol_hashmap_t *table, char *name);

void symbol_table_print(symbol_hashmap_t *table);

#endif // ME_SYMBOL_TABLE_