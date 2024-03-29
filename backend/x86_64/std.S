%define SYS_READ  0
%define SYS_WRITE 1
%define SYS_EXIT  60

%macro assign 2
    mov ax, [%2]
    mov [%1], ax
%endmacro

.sys_dump:
  mov     r8, -3689348814741910323
  sub     rsp, 40
  mov     BYTE [rsp+31], 10
  lea     rcx, [rsp+30]

.L2:
  mov     rax, rdi
  mul     r8
  mov     rax, rdi
  shr     rdx, 3
  lea     rsi, [rdx+rdx*4]
  add     rsi, rsi
  sub     rax, rsi
  mov     rsi, rcx
  sub     rcx, 1
  add     eax, 48
  mov     BYTE [rcx+1], al
  mov     rax, rdi
  mov     rdi, rdx
  cmp     rax, 9
  ja      .L2
  lea     rdx, [rsp+32]
  mov     edi, 1
  xor     eax, eax
  sub     rdx, rsi
  mov     rax, 0x1
  syscall
  add     rsp, 40
  ret

.exit_with_value:
  mov rax, SYS_EXIT
  syscall
  ret

.exit_with_non_zero: 
  mov rax, SYS_EXIT
  mov rdi, 1
  syscall
  ret

.exit_with_zero: 
  mov rax, SYS_EXIT
  mov rdi, 0
  syscall
  ret
