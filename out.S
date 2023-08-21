.include "sys.S"

.macro EXIT exit_code
    mov x0, \exit_code
    mov x16, #0x1
    svc #0
.endm

.macro SYSCALL sys_code, value
    mov x0, \value
    mov x16, \sys_code
    svc #0
.endm

.macro WRITE_STDOUT_STR str, len
    mov x0, #1
    adr x1, \str
    mov x2, \len
    mov x16, 0x4 ; write
    svc 0
.endm

.macro SYS_DUMP val
    mov     x0, 0x1
    mov     x1, \val
    mov     x8, 0x4
    mov     x2, 4
    svc     0x0
.endm

.section __TEXT,__text,regular,pure_instructions
.align 4

.globl _main
_main:
    mov     w1, 2
    mov     x0, 10
    bl      sys_add
    SYS_DUMP 10

    WRITE_STDOUT_STR message, #14
    EXIT 0x0

message:      .ascii  "Hello Sailor!\n"
