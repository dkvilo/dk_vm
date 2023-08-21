; $FILE out.S
; Author David Kviloria

%define SYS_READ  0
%define SYS_WRITE 1
%define SYS_EXIT  60

segment .text
global _start

_start:
  push 10
  push 20
  
  pop rdi
  pop rdx

  add rdx, rdi
  push rdx

  cmp rdx, 30
  je  .exit_with_value      ; if rdx == 30
  call .exit_with_non_zero  ; otherwise
  ret

.exit_with_value:
  mov rax, SYS_EXIT
  mov rdi, rdx
  syscall
  ret

.exit_with_zero: 
  mov rax, SYS_EXIT
  mov rdi, 0
  syscall
  ret

.exit_with_non_zero: 
  mov rax, SYS_EXIT
  mov rdi, 1
  syscall
  ret
