#include "symbol_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void symbol_table_add(symbol_hashmap_t *table, int8_t *name, int64_t value)
{
  symbol_t *symbol = (symbol_t *)malloc(sizeof(symbol_t));
  symbol->name = (int8_t *)malloc(sizeof(int8_t) * strlen((const char*)name));

  symbol->name = name;
  symbol->value = value;

  table->symbols[table->count] = *symbol;
  table->keys[table->count] = (char*)name;
  table->count++;
}

symbol_t symbol_table_get_by_index(symbol_hashmap_t *table, int index)
{
  return table->symbols[index];
}

bool symbol_table_contains(symbol_hashmap_t *table, int8_t *name)
{
  for (int i = 0; i < table->count; i++) {
    if (strcmp((const char*)table->keys[i], (const char*)name) == 0) {
      return true;
    }
  }
  return false;
}

symbol_t symbol_table_get(symbol_hashmap_t *table, int8_t *name)
{
  for (int i = 0; i < table->count; i++) {
    if (strcmp((const char*)table->keys[i], (const char*)name) == 0) {
      return table->symbols[i];
    }
  }
  return (symbol_t){0};
}

void symbol_table_remove(symbol_hashmap_t *table, int8_t *name)
{
  int i = 0;
  for (i = 0; i < table->count; i++) {
    if (strcmp((const char*)table->keys[i], (const char*)name) == 0) {
      table->symbols[i] = *&table->symbols[table->count - 1];
      table->keys[i] = table->keys[table->count - 1];
      table->count--;
      break;
    }
  }
}

void symbol_table_print(symbol_hashmap_t *table)
{
  for (int i = 0; i < table->count; i++) {
    symbol_t s = table->symbols[i];
    printf("\tSymbol: %s, value: %lld\n", s.name, s.value);
  }
}


