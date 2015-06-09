GLOBAL cpuVendor

section .text

cpuVendor:
  push rbp
  mov  rbp, rsp

  mov  rax, 0
  cpuid

  mov rax, rdi

  mov [rax], ebx
  mov [rax+4], edx
  mov [rax+8], ecx

  mov rsp, rbp
  pop rbp
  ret