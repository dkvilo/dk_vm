sys_add:
    sub     sp, sp, #16
    str     x0, [sp, 12]
    str     x1, [sp, 8]
    ldr     x1, [sp, 12]
    ldr     w0, [sp, 8]
    add     x0, x1, x0
    add     sp, sp, 16
    ret

sys_minus:
    sub     sp, sp, #16
    str     w0, [sp, 12]
    str     w1, [sp, 8]
    ldr     w1, [sp, 12]
    ldr     w0, [sp, 8]
    sub     w0, w1, w0
    add     sp, sp, 16
    ret

sys_div:
    sub     sp, sp, #16
    str     w0, [sp, 12]
    str     w1, [sp, 8]
    ldr     w1, [sp, 12]
    ldr     w0, [sp, 8]
    sdiv    w0, w1, w0
    add     sp, sp, 16
    ret

sys_mul:
    sub     sp, sp, #16
    str     w0, [sp, 12]
    str     w1, [sp, 8]
    ldr     w1, [sp, 12]
    ldr     w0, [sp, 8]
    mul     w0, w1, w0
    add     sp, sp, 16
    ret

