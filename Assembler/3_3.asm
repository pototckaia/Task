extern printf
extern scanf

section .bss
    a: resq 1
    b: resq 1

section .data
    text_in: db '%lf %lf', 10, 0
    lf_format: db '%lf', 10, 0
    ld_format: db '%ld', 10, 0
    result: dq 0.0
    
    six: dq 6.0 
    two: dq 2.0
    four: dq 4.0

section .text
        
;F(x) = x
_F:
    push	rbp		; save rbp
    mov	rbp, rsp         

    
    ; a = [rbp + 16] - double
    mov rax, [rbp + 16]  
        
    mov	rsp,rbp		; restore callers stack frame
    pop	rbp    
    ret			; return
    

global main
main:
    mov rbp, rsp; for correct debugging
    push rbx
    mov rbx, rcx
    
    mov rdi, text_in
    mov rsi, a
    mov rdx, b
    mov rax, 0
    call scanf
    
    finit
    
    fld qword [b]
    fsub qword [a]
    fdiv qword [six];  1 = (b - a)/2
    
    push qword [a]
    call _F
    pop qword rbx
    
    push qword rax ; F(a)
    fld qword [rsp]; 2 = F(a)
    pop qword rax
                   
    fld qword [a]
    fadd qword [b]
    fdiv qword [two]
    fstp qword [result]
    
    push qword [result]
    call _F
    pop rbx
    
    push qword rax
    fld qword [rsp]; 3 = 4 * F((a + b)/2)
    pop qword rax                                  
    fmul qword [four]
    faddp st1, st0; 2 = F(a) + 4 * F((a+b)/2)
    
    push qword [b]
    call _F
    pop rbx; F(b)
    
    push qword rax
    fld qword [rsp]
    pop qword rax
    faddp st1, st0; 2 = F(a)+4*F((a+b)/2)+F(b)
    fmulp st1, st0
    fstp qword [result]
          
    mov rdi, lf_format
    movq xmm0, [result]
    mov rax, 1
    call printf      
        
    pop rbx
    xor rax, rax
    ret