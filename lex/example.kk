import "gl";

mod ogl {
  get_opengl_version :: () str;
  get_opengl_vendor :: () str;
  get_opengl_renderer :: () str;
  get_opengl_shading_language_version :: () str;
  get_opengl_extensions :: () str;
}

mod testing {
  assert :: (bool condition, str message) i32;
}

mod math {
  add             :: (i32 x, i32 y) i32;
  sub             :: (i32 x, i32 y) i32;
  mul             :: (i32 x, i32 y) i32;
  div             :: (i32 x, i32 y) i32;
  pow             :: (i32 x, i32 y) i32;
  sqrt            :: (i32 x) i32;
}

x :: i32 = 1; // this is constant
y :: i32 = 2; // this is constant

for i32 i = 0; i < 10; i = i + 1 {
  use std;
  use math;
  println("Hello, World!");
  printf("Hello, World 10 times");
}

use testing;
assert(x == 1, "x is not 1");

struct system_ctx_t;

x :: i32 = 1; // this is constant
y :: i32 = 2; // this is constant

for i32 i = 0; i < 10; i = i + 1 {
  use std;
  use math;
  println("Hello, World!");
  printf("Hello, World 10 times");
}

struct person_t {
  str name;
  i32 age;
}

enum MY_ENUMS : i32 {
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
}

str name = "David";
i32 age = 23;
str occupation = "Programmer";
str address = "Tbilisi, Georgia"import "gl";

mod ogl {
  get_opengl_version :: () str;
  get_opengl_vendor :: () str;
  get_opengl_renderer :: () str;
  get_opengl_shading_language_version :: () str;
  get_opengl_extensions :: () str;
}

mod testing {
  assert :: (bool condition, str message) i32;
}

mod math {
  add             :: (i32 x, i32 y) i32;
  sub             :: (i32 x, i32 y) i32;
  mul             :: (i32 x, i32 y) i32;
  div             :: (i32 x, i32 y) i32;
  pow             :: (i32 x, i32 y) i32;
  sqrt            :: (i32 x) i32;
}

x :: i32 = 1; // this is constant
y :: i32 = 2; // this is constant

for i32 i = 0; i < 10; i = i + 1 {
  use std;
  use math;
  println("Hello, World!");
  printf("Hello, World 10 times");
}

use testing;
assert(x == 1, "x is not 1");

struct system_ctx_t;

x :: i32 = 1; // this is constant
y :: i32 = 2; // this is constant

for i32 i = 0; i < 10; i = i + 1 {
  use std;
  use math;
  println("Hello, World!");
  printf("Hello, World 10 times");
}

struct person_t {
  str name;
  i32 age;
}

enum MY_ENUMS : i32 {
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
}

str name = "David";
i32 age = 23;
str occupation = "Programmer";
str address = "Tbilisi, Georgia";
bool is_available = false;
i32 result = age + 2;

str color = "darkgreen";
if is_available {
  str hello = "world";
}

if is_available {
  str my_string = "This is a relatively long string";
  if some_condition < 0 {
    i32 x = 1;
  }
}

i32 main() {
  use std;
  use math;
  use testing;
  use ogl;
  use gl;

  str version = get_opengl_version();
  str vendor = get_opengl_vendor();
  str renderer = get_opengl_renderer();
  str shading_language_version = get_opengl_shading_language_version();
  str extensions = get_opengl_extensions();

  println("OpenGL Version: " + version);
  println("OpenGL Vendor: " + vendor);
  println("OpenGL Renderer: " + renderer);
  println("OpenGL Shading Language Version: " + shading_language_version);
  println("OpenGL Extensions: " + extensions);

  i32 x = 1;
  i32 y = 2;
  i32 z = add(x, y);
  println("x + y = " + z);

  i32 a = 1;
  i32 b = 2;
  i32 c = sub(a, b);
  println("a - b = " + c);

  i32 d = 1;
  i32 e = 2;
  i32 f = mul(d, e);
  println("d * e = " + f);

  i32 g = 1;
  i32 h = 2;
  i32 i = div(g, h);
  println("g / h = " + i);

  i32 j = 1;
  i32 k = 2;
  i32 l = pow(j, k);
  println("j ^ k = " + l);

  i32 m = 1;
  i32 n = sqrt(m);
  println("sqrt(m) = " + n);

  return 0;
}
if is_available {
  str my_string = "This is a relatively long string";
  if some_condition < 0 {
    i32 x = 1;
  }
}

i32 main() {
  use std;
  use math;
  use testing;
  use ogl;
  use gl;

  str version = get_opengl_version();
  str vendor = get_opengl_vendor();
  str renderer = get_opengl_renderer();
  str shading_language_version = get_opengl_shading_language_version();
  str extensions = get_opengl_extensions();

  println("OpenGL Version: " + version);
  println("OpenGL Vendor: " + vendor);
  println("OpenGL Renderer: " + renderer);
  println("OpenGL Shading Language Version: " + shading_language_version);
  println("OpenGL Extensions: " + extensions);

  i32 x = 1;
  i32 y = 2;
  i32 z = add(x, y);
  println("x + y = " + z);

  i32 a = 1;
  i32 b = 2;
  i32 c = sub(a, b);
  println("a - b = " + c);

  i32 d = 1;
  i32 e = 2;
  i32 f = mul(d, e);
  println("d * e = " + f);

  i32 g = 1;
  i32 h = 2;
  i32 i = div(g, h);
  println("g / h = " + i);

  i32 j = 1;
  i32 k = 2;
  i32 l = pow(j, k);
  println("j ^ k = " + l);

  i32 m = 1;
  i32 n = sqrt(m);
  println("sqrt(m) = " + n);

  return 0;
}
