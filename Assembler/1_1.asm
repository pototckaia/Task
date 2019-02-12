extern printf 
extern scanf                 

global main

SECTION .data 
    text_out: db " %u ",0
    text_zero: db " 0 ", 0
    text_inp: db "n and q: ", 10,0
    text_val: db "%u %u",10, 0
    
    count: dq 1
    arr: times 64 dq 0
    tmp: dq 0
   
SECTION .bss    
    n: resq 1
    q: resq 1

section .text
main:
    push rbp 
    mov rbp, rsp
    
    mov rax, 0 ; no xmm registers
    mov rdi, text_inp
    call printf
    
    mov rax, 0
    mov rdi, text_val
    mov rsi, n
    mov rdx, q
    call scanf      
    
    mov rax, [n]
    mov rbx, [tmp]
    mov rbx, rax
    mov [tmp], rbx
    
    jmp check
    
loop_start: 
    mov rdx, 0
    mov rax, [n]
    div qword [q]
    mov [n], rax
    
    mov rax, arr
    mov rbx, [count]
    mov [rax + 4*rbx], rdx
    inc qword [count]
       
check:
    mov rax, [n]
    test rax, rax
    jne loop_start
    
    
    dec qword [count]
    jmp check_print

loop_print:
    mov rax, arr
    mov rcx, [count]
    mov rbx, 0
    mov rbx, [rax + 4*rcx] 
    
    mov rax, 0  
    mov rdi, text_out
    mov rsi, rbx
    call printf      
    
    dec qword [count]
       
check_print:
    cmp qword [count], 0
    jg loop_print
    
    cmp dword [tmp], 0
    jne _end
    
    mov rax, 0
    mov rdi, text_zero
    xor rax, rax
    xor rbx, rbx
    call printf
    
_end: 
    pop	rbp ; restore stack
    mov	rax,0 ; normal, no error, return value
    
    xor rax, rax
    ret
    
