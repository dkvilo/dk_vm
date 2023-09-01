#if !defined(_ME_BYTECODE_PARSER_)
#define _ME_BYTECODE_PARSER_

#include "dk_token.h"
#include "dk_lexer.h"
#include "symbol_table.h"

#include <stdint.h>
#include <stdlib.h>

int8_t*
ext__dk_token_type_to_str(dk_token_type_t type);

bool
parse_variable_declaration(dk_lexer_t lexer, int64_t *__bytecode, symbol_hashmap_t *symbol_table, int32_t itteration);

bool
parse_addition(dk_lexer_t lexer, int64_t *__bytecode, int64_t itteration);

void
parse_and_tokenize(const char* filename, int64_t *__bytecode, size_t byte_code_count, symbol_hashmap_t *symbol_table);



#endif // _ME_BYTECODE_PARSER_
