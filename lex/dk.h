/**
 * @file dk.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief Helper functions and macros.
 * @date 2022-06-08
 *
 * This code is on PUBLIC DOMAIN to allow for any use.
 *
 */
#if !defined(__DK_H__)
#define __DK_H__

#if !defined(__STDBOOL_H)
#include <stdbool.h> // bool :)
#endif               // !defined(__STDBOOL_H)

#if !defined(__STRING_H)
#include <string.h> // memset
#endif              // !defined(__STRING_H)

#if !defined(_STDIO_H)
#include <stdio.h> // printf
#endif             // !defined(_STDIO_H)

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;
typedef short i16_t;
typedef int i32_t;
typedef long long i64_t;
typedef signed char s8_t;
typedef signed short s16_t;
typedef signed int s32_t;
typedef signed long long s64_t;
typedef float f32_t;
typedef double f64_t;
typedef char c_t;
typedef char b_t;
typedef const char cc_t;
typedef size_t sz_t;
typedef intptr_t iptr_t;
typedef uintptr_t uptr_t;

#define internal static
#define inlined __attribute__((always_inline)) inline
#define external extern
#define global_variable static
#define compile_time const

#define dk_malloc(size) malloc(size)
#define dk_realloc(ptr, size) realloc(ptr, size)
#define dk_free(ptr) free(ptr)

#define dk_ptr_swap(a, b)                                                      \
  do {                                                                         \
    char tmp__[sizeof(a)];                                                     \
    void* va__ = &(a);                                                         \
    void* vb__ = &(b);                                                         \
    (void)sizeof(&(a) - &(b));                                                 \
    memcpy(tmp__, va__, sizeof tmp__);                                         \
    memcpy(va__, vb__, sizeof tmp__);                                          \
    memcpy(vb__, tmp__, sizeof tmp__);                                         \
  } while (0)

#if !defined(_TIME_H_)
#include <time.h>
#endif // !defined(_TIME_H_)
#define DK_BENCHMARK_START(name) clock_t bench_##name##_start = clock();
#define DK_BENCHMARK_END(name)                                                 \
  clock_t bench_##name##_end = clock();                                        \
  printf(" - %s Time: %f\n",                                                   \
         #name,                                                                \
         (double)(bench_##name##_end - bench_##name##_start) /                 \
           CLOCKS_PER_SEC);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, min, max) (MIN(MAX(x, min), max))
#define LERP(a, b, t) ((a) + (t) * ((b) - (a)))
#define MAP(x, in_min, in_max, out_min, out_max)                               \
  ((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min)
#define IF_ELSE(cond, if_true, if_false) ((cond) ? (if_true) : (if_false))
#define IF(cond, if_true) IF_ELSE(cond, if_true, 0)
#define ASSERT_LOG(cond, ...)                                                  \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fprintf(stderr, "Assertion failed: %s\n", #cond);                        \
      fprintf(stderr, "File: %s\n", __FILE__);                                 \
      fprintf(stderr, "Line: %d\n", __LINE__);                                 \
      fprintf(stderr, "Function: %s\n", __FUNCTION__);                         \
      fprintf(stderr, __VA_ARGS__);                                            \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)
#define ASSERT_EQ(a, b)                                                        \
  ASSERT_LOG((a) == (b), "Expected %d, got %d\n", (a), (b))
#define ASSERT_NE(a, b)                                                        \
  ASSERT_LOG((a) != (b), "Expected %d, got %d\n", (a), (b))
#define ASSERT_LT(a, b) ASSERT_LOG((a) < (b), "Expected %d < %d\n", (a), (b))
#define ASSERT_LE(a, b) ASSERT_LOG((a) <= (b), "Expected %d <= %d\n", (a), (b))
#define ASSERT_GT(a, b) ASSERT_LOG((a) > (b), "Expected %d > %d\n", (a), (b))
#define ASSERT_GE(a, b) ASSERT_LOG((a) >= (b), "Expected %d >= %d\n", (a), (b))
#define TEST_ASSERT_EQ(a, b)                                                   \
  do {                                                                         \
    if ((a) != (b)) {                                                          \
      fprintf(stderr, "Expected %d, got %d\n", (a), (b));                      \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)
#define TEST_ASSERT_NE(a, b)                                                   \
  do {                                                                         \
    if ((a) == (b)) {                                                          \
      fprintf(stderr, "Expected %d, got %d\n", (a), (b));                      \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)
#define TEST_ASSERT_LT(a, b)                                                   \
  do {                                                                         \
    if ((a) >= (b)) {                                                          \
      fprintf(stderr, "Expected %d < %d\n", (a), (b));                         \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)
#define TEST_ASSERT_LE(a, b)                                                   \
  do {                                                                         \
    if ((a) > (b)) {                                                           \
      fprintf(stderr, "Expected %d <= %d\n", (a), (b));                        \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)
#define TEST_ASSERT_GT(a, b)                                                   \
  do {                                                                         \
    if ((a) <= (b)) {                                                          \
      fprintf(stderr, "Expected %d > %d\n", (a), (b));                         \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)
#define TEST_ASSERT_GE(a, b)                                                   \
  do {                                                                         \
    if ((a) < (b)) {                                                           \
      fprintf(stderr, "Expected %d >= %d\n", (a), (b));                        \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

#define dk_defer(...)                                                          \
  for (int var_line(cond) = 0; var_line(cond) == 0;)                           \
    for (FIRST_ARG(__VA_ARGS__); var_line(cond) == 0;)                         \
      for (SKIP_LAST_ARG(SKIP_FIRST_ARG(__VA_ARGS__)); var_line(cond) == 0;    \
           var_line(cond) += 1)                                                \
        for (int var_line(cond_int) = 0; var_line(cond_int) <= 1;              \
             var_line(cond_int) += 1)                                          \
          if (var_line(cond_int) == 1) {                                       \
            LAST_ARG(__VA_ARGS__);                                             \
          } else if (var_line(cond_int) == 0)

#if defined(_WIN32)
#define dk_pause() system("pause")
#else
#define dk_pause()                                                             \
  do {                                                                         \
    printf("Press any key to continue...\n");                                  \
    getchar();                                                                 \
  } while (0)
#endif

#if defined(_WIN32)
#define dk_pause_and_notify(callback)                                          \
  do {                                                                         \
    system("pause");                                                           \
    callback();                                                                \
  } while (0)
#else
#define dk_pause_and_notify(callback)                                          \
  do {                                                                         \
    printf("Press any key to continue...\n");                                  \
    getchar();                                                                 \
    callback();                                                                \
  } while (0)
#endif

#define dk_exit(CODE) exit(CODE);
#define dk_exit_success() dk_exit(EXIT_SUCCESS);
#define dk_exit_failure() dk_exit(EXIT_FAILURE);

internal i32_t
dk_atoi(char* str)
{
  i32_t result = 0;
  i32_t i = 0;
  for (; str[i] != '\0'; i++) {
    result = result * 10 + (str[i] - '0');
  }
  return result;
}

internal f32_t
dk_atof(char* str)
{
  f32_t result = 0.0f;
  i32_t i = 0;
  for (; str[i] != '\0'; i++) {
    result = result * 10 + (str[i] - '0');
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// HashMap implementation
//

#define dk_empty_VALUE 0x00

typedef struct
{
  i32_t key;
  void* value;
} dk_hashmap_pair_t;

typedef struct
{
  dk_hashmap_pair_t* pairs;
  i32_t capacity;
  i32_t size;
} dk_hashmap_t;

internal dk_hashmap_t*
dk_hashmap_create(i32_t capacity)
{
  dk_hashmap_t* map = (dk_hashmap_t*)dk_malloc(sizeof(dk_hashmap_t));
  map->capacity = capacity;
  map->size = 0;
  map->pairs =
    (dk_hashmap_pair_t*)dk_malloc(sizeof(dk_hashmap_pair_t) * capacity);
	memset(map->pairs, dk_empty_VALUE, sizeof(dk_hashmap_pair_t) * capacity);
  return map;
}

internal i32_t
dk_hashmap_hash(dk_hashmap_t* map, i32_t key)
{
  i32_t hash = 5381;
  i32_t i = 0;
  for (; i < sizeof(key); i++) {
    hash = (hash << 5) + hash + key + (key >> (i * 8));
  }
  return hash % map->capacity;
}

internal void*
dk_hashmap_get(dk_hashmap_t* map, i32_t key)
{
  i32_t hash = dk_hashmap_hash(map, key);
  i32_t index = hash;
  return map->pairs[index].value;
}

internal void
dk_hashmap_put(dk_hashmap_t* map, i32_t key, void* value)
{
  i32_t hash = dk_hashmap_hash(map, key);
  i32_t index = hash;
  map->pairs[index].key = key;
  map->pairs[index].value = value;
  map->size++;
}

internal void
dk_hashmap_remove(dk_hashmap_t* map, i32_t key)
{
  i32_t hash = dk_hashmap_hash(map, key);
  i32_t index = hash;
  while (map->pairs[index].key != key &&
         map->pairs[index].key != dk_empty_VALUE) {
    index++;
    if (index == map->capacity) {
      index = 0;
    }
  }
  map->pairs[index].key = dk_empty_VALUE;
  map->pairs[index].value = dk_empty_VALUE;
  map->size--;
}

internal void
dk_hashmap_print(dk_hashmap_t* map)
{
  i32_t i = 0;
  for (i = 0; i < map->capacity; i++) {
    printf("%d) KEY=%d, VALUE=%s\n", i, map->pairs[i].key, map->pairs[i].value);
  }
}

internal dk_hashmap_t*
dk_hashmap_from_array(dk_hashmap_pair_t* pairs, i32_t size)
{
  dk_hashmap_t* map = dk_hashmap_create(size);
  i32_t i = 0;
  for (i = 0; i < size; i++) {
    dk_hashmap_put(map, pairs[i].key, pairs[i].value);
  }
  return map;
}

internal void
dk_hashmap_free(dk_hashmap_t* map)
{
  free(map->pairs);
  free(map);
}

internal void
dk_hashmap_resize(dk_hashmap_t* map, i32_t new_capacity)
{
  dk_hashmap_t* temp_map = dk_hashmap_create(new_capacity);
  i32_t i = 0;
  for (i = 0; i < map->capacity; i++) {
    if (map->pairs[i].key != dk_empty_VALUE) {
      dk_hashmap_put(temp_map, map->pairs[i].key, map->pairs[i].value);
    }
  }
  *map = *temp_map;
  dk_hashmap_free(temp_map);
}

#if 0
internal i32_t
dk_hashmap_resolve_collision(dk_hashmap_t* map, i32_t key)
{
  i32_t hash = dk_hashmap_hash(map, key);
  i32_t index = hash;
  while (map->pairs[index].key != key &&
         map->pairs[index].key != dk_empty_VALUE) {
    index++;
    if (index == map->capacity) {
      index = 0;
    }
  }
  return index;
}

internal void
dk_hashmap_put_with_collision(dk_hashmap_t* map, i32_t key, i32_t value)
{
  i32_t index = dk_hashmap_resolve_collision(map, key);
  map->pairs[index].key = key;
  map->pairs[index].value = value;
  map->size++;
}
#endif // 0

///////////////////////////////////////////////////////////////////////////////
// STACK IMPLEMENTATION
// Stack is implemented using a HashMap. The HashMap is used to store the data
//
typedef struct
{
  dk_hashmap_t* map;
  i32_t capacity;
  i32_t size;
} dk_stack_t;

internal dk_stack_t*
dk_stack_create(i32_t capacity)
{
  dk_stack_t* stack = (dk_stack_t*)dk_malloc(sizeof(dk_stack_t));
  stack->capacity = capacity;
  stack->size = 0;
  stack->map = dk_hashmap_create(capacity);
  return stack;
}

internal void*
dk_stack_pop(dk_stack_t* stack)
{
  i32_t value = dk_hashmap_get(stack->map, stack->size - 1);
  dk_hashmap_remove(stack->map, stack->size - 1);
  stack->size--;
  return value;
}

internal void
dk_stack_push(dk_stack_t* stack, void* value)
{
  dk_hashmap_put(stack->map, stack->size, value);
  stack->size++;
}

// shifts the stack by the given amount
internal void
dk_stack_shift(dk_stack_t* stack, i32_t amount)
{
  i32_t i = 0;
  for (i = 0; i < amount; i++) {
    dk_stack_pop(stack);
  }
}

internal bool
dk_stack_is_empty(dk_stack_t* stack)
{
  return stack->size == 0;
}

internal void
dk_stack_print(dk_stack_t* stack)
{
  dk_hashmap_print(stack->map);
}

internal void
dk_stack_resize(dk_stack_t* stack, i32_t new_capacity)
{
  dk_hashmap_resize(stack->map, new_capacity);
  stack->capacity = new_capacity;
}

///////////////////////////////////////////////////////////////////////////////
// MEMORY ARENA IMPLEMENTATION
//

typedef struct
{
  i32_t* data;
  i32_t capacity;
  i32_t size;
} dk_memory_arena_t;

internal dk_memory_arena_t*
dk_memory_arena_create(i32_t capacity)
{
  dk_memory_arena_t* arena =
    (dk_memory_arena_t*)dk_malloc(sizeof(dk_memory_arena_t));
  arena->capacity = capacity;
  arena->size = 0;
  arena->data = (i32_t*)dk_malloc(sizeof(i32_t) * capacity);
  return arena;
}

internal i32_t*
dk_memory_arena_next_ptr(dk_memory_arena_t* arena, i32_t size)
{
  i32_t* ptr = arena->data + arena->size;
  arena->size += size;
  return ptr;
}

internal void
dk_memory_arena_reset(dk_memory_arena_t* arena)
{
  arena->size = 0;
}

internal void
dk_memory_arena_free(dk_memory_arena_t* arena)
{
  free(arena->data);
  free(arena);
}

internal void
dk_memory_arena_resize(dk_memory_arena_t* arena, i32_t new_capacity)
{
  arena->data = (i32_t*)dk_realloc(arena->data, new_capacity);
  arena->capacity = new_capacity;
}

internal void
dk_write_to_buffer(u8_t* buffer,
                   u32_t size,
                   u32_t* offset,
                   u8_t* data,
                   u32_t data_size)
{
  u32_t i;
  for (i = 0; i < data_size; ++i) {
    buffer[(*offset)++] = data[i];
  }
}

#if 0
internal void
pause_callback()
{
  printf("Exiting...\n");
  dk_exit_success();
}
#endif

///////////////////////////////////////////////////////////////////////////////
// File Utility Functions
//

internal void
dk_write_to_file_bin(const char* filename, u8_t* data, u32_t size)
{
  FILE* file = fopen(filename, "wb");
  if (file) {
    fwrite(data, sizeof(u8_t), size, file);
    fclose(file);
  }
}

internal void
dk_read_from_file_bin(const char* filename, u8_t* data, u32_t size)
{
  FILE* file = fopen(filename, "rb");
  if (file) {
    fread(data, sizeof(u8_t), size, file);
    fclose(file);
  }
}

internal u8_t*
dk_read_file(cc_t* p_filename, u32_t* p_size)
{
  FILE* p_file = fopen(p_filename, "r");
  if (!p_file)
    return NULL;
  fseek(p_file, 0, SEEK_END);
  u32_t size = ftell(p_file);
  fseek(p_file, 0, SEEK_SET);
  u8_t* p_data = (u8_t*)dk_malloc(sizeof(u8_t) * size);
  fread(p_data, sizeof(u8_t), size, p_file);
  fclose(p_file);
  *p_size = size;
  return p_data;
}

#endif __DK_H__
