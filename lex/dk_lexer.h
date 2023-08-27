/**
 * @file dk_lexer.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief Lexer definition.
 * @date 2022-06-08
 *
 * This code is on PUBLIC DOMAIN to allow for any use.
 *
 */
#if !defined(DK_LEXER_H)
#define DK_LEXER_H

#include "dk_token.h"

typedef struct
{
  u8_t* p_data;
  u32_t size;
  u32_t cursor;
} dk_lexer_t;

dk_lexer_t*
dk_lexer_create(u8_t* p_data, u32_t size);

void
dk_lexer_destroy(dk_lexer_t* p_lexer);

u8_t
dk_lexer_peak(dk_lexer_t* p_lexer);

dk_token_t*
dk_lexer_next_token(dk_lexer_t* p_lexer);

void
dk_lexer_print(dk_lexer_t* p_lexer);

void
dk_lexer_print_token(dk_token_t* p_token);

#endif // DK_LEXER_H
