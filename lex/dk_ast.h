/**
 * @file dk_ast.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief Abstract Syntax Tree
 * @date 2022-06-08
 *
 * This code is on PUBLIC DOMAIN to allow for any use.
 *
 */
#if !defined(__DK_AST_H__)
#define __DK_AST_H__

#include "dk.h"
#include "dk_token.h"

typedef struct dk_ast_node_t {
  u32_t type;
  u32_t size;
  u32_t capacity;
  dk_token_t* p_token;
  struct dk_ast_node_t** p_children;
} dk_ast_node_t;

typedef enum AST_NODE_TYPE {
  DK_AST_NODE_ROOT,
  DK_AST_NODE_IDENTIFIER,
  DK_AST_NODE_NUMBER,
  DK_AST_NODE_STRING,
  DK_AST_NODE_OPERATOR,
  DK_AST_NODE_KEYWORD,
  DK_AST_NODE_TYPE,
  DK_AST_NODE_EXPRESSION,
  DK_AST_NODE_STATEMENT,
  DK_AST_NODE_FUNCTION,
  DK_AST_NODE_FUNCTION_CALL,
  DK_AST_NODE_VARIABLE,
  DK_AST_NODE_VARIABLE_DECLARATION,
  DK_AST_NODE_VARIABLE_ASSIGNMENT,
  DK_AST_NODE_VARIABLE_DECLARATION_ASSIGNMENT,
  DK_AST_NODE_IF,
  DK_AST_NODE_WHILE,
  DK_AST_NODE_FOR,
  DK_AST_NODE_RETURN,
  DK_AST_NODE_BREAK,
  DK_AST_NODE_CONTINUE,
  DK_AST_NODE_BLOCK,
  DK_AST_NODE_PROGRAM,
  DK_AST_NODE_IMPORT,
  DK_AST_NODE_UNKNOWN,
} AST_NODE_TYPE;

dk_ast_node_t*
dk_ast_node_create(u32_t type);

void
dk_ast_node_destroy(dk_ast_node_t* p_node);

void
dk_ast_node_add_child(dk_ast_node_t* p_node, dk_ast_node_t* p_child);

void
dk_ast_node_print(dk_ast_node_t* p_node, u32_t depth);

i32_t
dk_ast_convert_token_to_ast_type(dk_token_t* p_token);



#endif // __DK_AST_H__
