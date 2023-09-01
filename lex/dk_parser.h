/**
 * @file dk_parser.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief  Parser definition.
 * @date 2022-06-08
 *
 * This code is on PUBLIC DOMAIN to allow for any use.
 *
 */
#if !defined(DK_PARSER_H)
#define DK_PARSER_H

#include "dk.h"
#include "dk_ast.h"
#include "dk_token.h"

typedef struct
{
  dk_token_t* p_token;
  dk_token_t* p_next_token;
} dk_parser_t;

dk_parser_t*
dk_parser_create(dk_token_t* p_token);

dk_ast_t*
dk_parser_parse(dk_parser_t* p_parser);

void
dk_parser_destroy(dk_parser_t* p_parser);

dk_token_t*
dk_parser_next_token(dk_parser_t* p_parser);

dk_token_t*
dk_parser_current_token(dk_parser_t* p_parser);

dk_token_t*
dk_parser_next_token_and_move(dk_parser_t* p_parser);

#endif // DK_PARSER_H
