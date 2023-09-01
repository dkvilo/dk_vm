#include "bytecode_parser.h"
#include "vm.h"

char*
ext__dk_token_type_to_str(dk_token_type_t type)
{
  switch (type)
  {
  case DK_TOKEN_IDENTIFIER: return "Identifier";
  case DK_TOKEN_NUMBER: return "Number";
  case DK_TOKEN_STRING: return "String";
  case DK_TOKEN_OPERATOR: return "Operator";
  case DK_TOKEN_KEYWORD: return "Keyword";
  case DK_TOKEN_END_OF_FILE: return "Eof";
  case DK_TOKEN_END_OF_STATEMENT: return "Eos";
  case DK_TOKEN_WHITESPACE: return "Whitespace";
  case DK_TOKEN_COMMENT: return "Commnet";
  default: return "Unknown";
  }
}

#define HANDLE_OPERATOR(OPERATOR, A, B)              \
    ({                                               \
        strcmp(OPERATOR, "+") == 0 ? (A += B) :      \
        strcmp(OPERATOR, "-") == 0 ? (A -= B) :      \
        strcmp(OPERATOR, "*") == 0 ? (A *= B) :      \
        strcmp(OPERATOR, "/") == 0 ? (A /= B) :      \
        0;                                           \
    })

bool
parse_variable_declaration(dk_lexer_t lexer, int64_t *__bytecode, symbol_hashmap_t *symbol_table, int32_t itteration)
{

  bool is_variable_declaration_valid = true;

  int8_t *variable_name = NULL;
  int64_t variable_value = 0;

  lexer.cursor++;
  dk_token_t *token  = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_IDENTIFIER) {
    printf("Error: expected identifier, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  variable_name = token->p_data;

  lexer.cursor++;
  token = dk_lexer_next_token(&lexer);
  if (token->type != DK_TOKEN_OPERATOR) {
    printf("Error: expected operator, but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  lexer.cursor++;
  if (strcmp((const char*)token->p_data, "=") != 0) {
    printf("Error: expected assigment operator '=', but got %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
    is_variable_declaration_valid = false;
    exit(1);
  }

  token = dk_lexer_next_token(&lexer);
  if (token->type == DK_TOKEN_NUMBER) {
    variable_value = atoi((const char*)token->p_data);
  } else if (token->type == DK_TOKEN_IDENTIFIER) {
    char* v_name = token->p_data;
    bool is_valid_var_reference = symbol_table_contains(symbol_table, v_name);
    if (!is_valid_var_reference) {
      is_variable_declaration_valid = false;
      printf("Error: undefined variable was referenced %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
      exit(1);
    }

    /* get variable value from symbols table */
    symbol_t symbol = symbol_table_get(symbol_table, v_name);
    variable_value = symbol.value;
  }
  lexer.cursor++;

  token = dk_lexer_next_token(&lexer);
  if (token->type == DK_TOKEN_OPERATOR) {
    bool is_math_expr =
      strcmp((const char*)token->p_data, "+") == 0 ||
      strcmp((const char*)token->p_data, "-") == 0 ||
      strcmp((const char*)token->p_data, "*") == 0 ||
      strcmp((const char*)token->p_data, "/") == 0;
    
    const char* expr = (const char*)token->p_data;
    if (is_math_expr) {
      // now we are looking for either lvalue or lvalue, if not we are erroring out
      lexer.cursor++;
      token = dk_lexer_next_token(&lexer);
      if (token->type == DK_TOKEN_NUMBER) {
        HANDLE_OPERATOR(expr, variable_value, atoi((const char*)token->p_data));
      } else if (token->type == DK_TOKEN_IDENTIFIER) {
        char* v_name = token->p_data;
        bool is_valid_var_reference = symbol_table_contains(symbol_table, v_name);
        if (!is_valid_var_reference) {
          is_variable_declaration_valid = false;
          printf("Error: undefined variable was referenced %s(%s)\n", ext__dk_token_type_to_str(token->type), token->p_data);
          exit(1);
        }

        /* get variable value from symbols table */
        symbol_t symbol = symbol_table_get(symbol_table, v_name);

        HANDLE_OPERATOR(expr, variable_value, symbol.value);
      } else {
        printf("\nError: incomplete variable declaration, math expretion was not finalized.\n", variable_name);
        is_variable_declaration_valid = false;
        exit(1); 
      }
    }
  }

  lexer.cursor++;

  if (symbol_table_contains(symbol_table, variable_name)) {
    printf("\nError: variable %s already was defined in the scope\n", variable_name);
    is_variable_declaration_valid = false;
    exit(1);
  }

  symbol_table_add(symbol_table, variable_name, variable_value);

  /* Generate bytecode */

  // calculate offset for bytecode array
  int64_t offset = 0;
  if (itteration > 0) {
    offset = itteration * 4;
  }

  __bytecode[offset + 4] = LOAD;
  __bytecode[offset + 5] = variable_value;
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

bool
parse_addition(dk_lexer_t lexer, int64_t *__bytecode, int64_t itteration)
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
  __bytecode[offset + 0] = NOP;
  __bytecode[offset + 1] = 0;
  __bytecode[offset + 2] = 0;
  __bytecode[offset + 3] = 0;

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

  __bytecode[offset + 20] = ADD;
  __bytecode[offset + 21] = 0;
  __bytecode[offset + 22] = 0;
  __bytecode[offset + 23] = 0;

  __bytecode[offset + 24] = PUSH;
  __bytecode[offset + 25] = 0;
  __bytecode[offset + 26] = 0;
  __bytecode[offset + 27] = 0;

  /* END */

  return is_addition_valid;
}

void
parse_and_tokenize(const char* filename, int64_t *__bytecode, size_t byte_code_count, symbol_hashmap_t *symbol_table)
{
  u32_t p_size = 0;
  u8_t *p_data = dk_read_file(filename, &p_size);
  dk_lexer_t *lex = dk_lexer_create(p_data, p_size * sizeof(u8_t));
  
  int64_t variable_itteration = 0;
  dk_token_t *token = NULL;

  while (token != NULL, token = dk_lexer_next_token(lex)) {
    if (token->type == DK_TOKEN_WHITESPACE || token->type == DK_TOKEN_COMMENT) {
      continue;
    }

    if (token->type == DK_TOKEN_KEYWORD) {
      if (strcmp(token->p_data, "i32") == 0) {
        if (!parse_variable_declaration(*lex, __bytecode, symbol_table, variable_itteration)) {
          printf("Illegal Variable declaration\n");
        }
      }
    }

    // if (token->type == DK_TOKEN_IDENTIFIER) {
    //   if (strcmp(token->p_data, "add") == 0) {
    //     if (!parse_addition(*lex, __bytecode, variable_itteration)) {
    //       printf("Illegal addition\n");
    //     }
    //   }
    // }

    if (token->type == DK_TOKEN_UNKNOWN) {
      printf("Error: unknown token\n");
      exit(1);
    }

    if (token->type == DK_TOKEN_END_OF_FILE || token->type == DK_TOKEN_UNKNOWN || token->type == DK_TOKEN_SEMICOLON) {
      break;
    }

    variable_itteration++;

    lex->cursor++;
  }

  dk_lexer_destroy(lex);
  free(p_data);

  // We are done with parsing, so we can add HALT instruction to the end of bytecode
  __bytecode[byte_code_count - 4] = HALT;
  __bytecode[byte_code_count - 3] = 0;
  __bytecode[byte_code_count - 2] = 0;
  __bytecode[byte_code_count - 1] = 0;
}

