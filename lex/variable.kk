context :: make_program(
  arch:        "x86",
  os:          "linux",
  abi:         "sysv",
  cpu:         "core2",
  fpu:         "sse2",
  sse:         "sse2",
  avx:         "avx",

  stack_align: 16,       // 16-byte stack alignment (for SSE), 32-byte for AVX (avx: "avx")
  stack_size:  4096,     // 4KB stack
  heap_size:   4096,     // Initial heap size (4KB), resizeable
  entry:       "main",
)

context.heap.resize(8192) // Resize heap to 8KB (8192 bytes

load_program(context: context, onCompile: (program: Program) -> Fn :: (Program) => {
  pritnln("-- Program compiled")
  program
    .emit_asm("mov", "rax", "0x1234") // Move 0x1234 into rax
    .emit_asm("mov", "rbx", "0x5678") // Move 0x5678 into rbx
    .emit_asm("add", "rax", "rbx")    // Add rax and rbx, store result in rax
    .emit_asm("ret")                  // Return from function
    .compile()                        // Compile to machine code
    .run()                            // Run the program
  pritnln("-- Program finished")
  pritnln("-- Time: " + program.time + "ms")
})


import "backend/x86_64/std.S"

i32 x = 8
i32 y = 256
i32 z = x * y




