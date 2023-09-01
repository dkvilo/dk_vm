/**
 * @file dk_token.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief Token implementation.
 * @date 2022-06-08
 *
 * This code is on PUBLIC DOMAIN to allow for any use.
 *
 */
#if !defined(DK_TOKEN_H)
#define DK_TOKEN_H

#if !defined(__DK_H__)
#include "dk.h"
#endif

// #define IsComment(c) (c == '#')

// #define IsNumber(c) (c >= '0' && c <= '9')

// #define IsAlpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

// #define IsAlphaNum(c) (IsAlpha(c) || IsNumber(c))

// #define IsAlphaNumUnderScore(c) (IsAlphaNum(c) || c == '_')

// #define IsAlphaUnderScore(c) (IsAlpha(c) || c == '_')

// #define IsString(c) (c == '"')

// #define IsSemiColon(c) (c == ';')

// #define IsWhiteSpace(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')

// #define IsOperator(c)                                                          \
//   (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' ||     \
//    c == '<' || c == '>' || c == '!' || c == '&' || c == '|' || c == '^' ||     \
//    c == '~')

// #define IsDelimiter(c)                                                         \
//   (c == '(' || c == ')' || c == '[' || c == ']' || c == ',' || c == ':' ||     \
//    c == c == '.' || c == '?' || c == '!' || c == '@' || c == '#' ||            \
//    c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '-' ||     \
//    c == '_' || c == '+' || c == '<')

// #define IsDelimiterOrOperator(c) (IsDelimiter(c) || IsOperator(c))

// #define IsIdentifierStart(c) (IsAlpha(c) || c == '_')

// #define IsIdentifierPart(c) (IsAlphaNum(c) || c == '_')

// #define IsIdentifier(c) (IsIdentifierStart(c) || IsNumber(c))


typedef enum
{
  DK_TOKEN_NONE = -1,
  DK_TOKEN_IDENTIFIER,
  DK_TOKEN_NUMBER,
  DK_TOKEN_STRING,
  DK_TOKEN_OPERATOR,
  DK_TOKEN_KEYWORD,
  DK_TOKEN_END_OF_FILE,
  DK_TOKEN_ERROR,
  DK_TOKEN_COMMENT,
  DK_TOKEN_WHITESPACE,
  DK_TOKEN_END_OF_LINE,
  DK_TOKEN_END_OF_STATEMENT,
  DK_TOKEN_COLON,
  DK_TOKEN_DOT,
  DK_TOKEN_COMMA,
  DK_TOKEN_SEMICOLON,
  DK_TOKEN_QUESTION,
  DK_TOKEN_EXCLAMATION,
  DK_TOKEN_AMPERSAND,
  DK_TOKEN_OPEN_BRACE,
  DK_TOKEN_CLOSE_BRACE,
  DK_TOKEN_UNKNOWN,
  DK_TOKEN_DELIMITER,
  DK_TOKEN_DATA_TYPE,
  DK_TOKEN_IF,
  DK_TOKEN_ELSE,
  DK_TOKEN_FOR,
  DK_TOKEN_RETURN,
  DK_TOKEN_INT,
  DK_TOKEN_FLOAT,
  DK_TOKEN_DOUBLE,
  DK_TOKEN_CHAR,
  DK_TOKEN_STR,
  DK_TOKEN_BOOL,
  DK_TOKEN_TRUE,
  DK_TOKEN_FALSE,
  DK_TOKEN_STRUCT,
  DK_TOKEN_ENUM,
  DK_TOKEN_IMPORT,
  DK_TOKEN_MODULE,
  DK_TOKEN_USE,
  DK_TOKEN_TYPE_REFRENCE,
} dk_token_type_t;

global_variable const struct
{
  const char* keyword;
  dk_token_type_t type;
} keywords[] = {
  { "if", DK_TOKEN_IF },         { "else", DK_TOKEN_ELSE },
  { "for", DK_TOKEN_FOR },       { "return", DK_TOKEN_RETURN },
  { "i32", DK_TOKEN_INT },       { "f32", DK_TOKEN_FLOAT },
  { "f64", DK_TOKEN_DOUBLE },    { "char", DK_TOKEN_CHAR },
  { "str", DK_TOKEN_STR },       { "bool", DK_TOKEN_BOOL },
  { "true", DK_TOKEN_TRUE },     { "false", DK_TOKEN_FALSE },
  { "struct", DK_TOKEN_STRUCT }, { "enum", DK_TOKEN_ENUM },
  { "import", DK_TOKEN_IMPORT }, { "mod", DK_TOKEN_MODULE },
  { "use", DK_TOKEN_USE },
  { "@", DK_TOKEN_TYPE_REFRENCE },
};

typedef struct
{
  dk_token_type_t type;
  u8_t* p_data;
  u32_t size;
} dk_token_t;

dk_token_t*
dk_token_create(dk_token_type_t type, u8_t* p_data, u32_t size);

void
dk_token_destroy(dk_token_t* p_token);

dk_token_t*
dk_token_next(dk_token_t* p_token);

#endif // DK_TOKEN_H
