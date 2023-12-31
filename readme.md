```
This is all that the VM and Compiler can handle at this moment. At this stage, the VM is not using any register allocation, and everything is pushed onto the stack (which is horrible). As for the compiler, things are working differently; most of the following expressions will be optimized at compile time (You can take a look at the generated assembly). For full disclosure, this is just me playing around with some ideas and killing my free time. So, you should not consider this project seriously because I do not have any intentions to make this programming language usable in production.
```

```rust
i32 x = 8;
i32 y = 16;
i32 z = x * y;

i32 result = z * 4;
i32 result_sqrt = result * result;

if result > 0 then print(result_sqrt)
if result > 0 then exit(0)
```

> Result 262144


Empty VM state

```
STACK:

 - []

Memory:

 - [0xff	0	0	0]		HALT		addr	0x000003fc

[ACC 0 | PC 1024 | SP 0]

Memory Footprint: 8192/4096000 Bytes

-----------------------
Symbol table (0):
```