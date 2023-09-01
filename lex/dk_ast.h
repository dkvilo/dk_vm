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

typedef struct dk_ast_t
{
  dk_token_t* p_token;
  struct dk_ast_t* p_left;
  struct dk_ast_t* p_right;
} dk_ast_t;

dk_ast_t*
dk_ast_create();

void
dk_ast_add_child(dk_ast_t* p_ast, dk_ast_t* p_child);

void
dk_ast_set_token(dk_ast_t* p_ast, dk_token_t* p_token);

void
dk_ast_print(dk_ast_t* p_ast);

#endif // __DK_AST_H__
