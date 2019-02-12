extern printf
extern scanf

global main

section .data
    text_in db "%u", 0
    text_out db "%u ",0
    d dq 2
    
    q dq 1
    r dq 1
    
section .bss
    n resq 1    
    
section .code
main:
    push rbp
    
    mov rax, 0
    mov rdi, text_in
    mov rsi, n
    call scanf
    
    
    jmp check
    
start_loop:
    mov rdx, 0
    mov rax, [n]
    div qword [d]
    mov [q], rax
    mov [r], rdx
    
    test rdx, rdx   
    jne _else
    
    mov eax, 0
    mov rdi, text_out
    mov rsi, [d]
    call printf
    
    
    mov rax, [q]
    mov [n], rax
    jmp check

_else:
    inc qword [d]

check:
    mov rax, [d]
    mul qword rax
    cmp qword rax, [n]
    jna start_loop
    
    cmp qword [n], 1
    je end_
    
    mov rdi, text_out
    mov rsi, [n]
    call printf
    
    
end_:    

    pop	rbp
    mov	rax,0
    
    xor eax, eax
    ret
    
