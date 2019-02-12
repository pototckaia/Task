section .text

extern printf
extern scanf

global main
main:
    mov rbp, rsp; for correct debugging
    push rbx
    
    mov rdi, text_in
    mov rsi, eps
    mov rax, 0
    call scanf
    
    finit
    
    fld qword [e]
loop:
    
    fld qword [acc_sum]
    fadd st1, st0
    
    fld qword [eps]
    fcompp
    
    fstsw ax
    sahf
    
    jae _end
    
    fld qword [x]
    fld qword [x]
    fmulp st1, st0
    fst qword [x]
    
    fld qword [i]
    fld qword [one]
    faddp st1, st0
    fst qword [i]    
    
    fld qword [fac]
    fmulp st1, st0
    fst qword [fac]
    
    fdivp st1, st0
    fstp qword [acc_sum]
    
    
    jmp loop
    
 
_end:
    fstp qword [e]
      
    mov rdi, text_out
    movq xmm0, qword [e]
    mov rax, 1
    call printf
        
    pop rbx
    mov rax, 0
    
    xor rax, rax
    ret


section .bss
    eps: resq 1
    
section .data
    text_in: db "%lf",10, 0
    text_out: db "%.10lf", 10, 0
    e: dq 1.0
    
    x: dq 1.0
    fac: dq 1.0
section .data    
    i: dq 1.0
    one: dq 1.0
    
    n: dq 10.0
    
    acc_sum: dq 1.0