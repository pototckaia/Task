extern printf
extern scanf

section .bss
    n: resq 1
    a: resq 1
    eps: resq 1
    
section .data
    one: dq 1.0
    two: dq 2.0
    
    l: dq 0
    r: dq 0
    m: dq 0
    p: dq 0
      
    text_in: db '%lf %d %lf', 10, 0
    lf_format: db '%lf', 10, 0
    ld_format: db '%ld', 10, 0

section .text

;First - a - fload
; Second - n - int
_pow:
    push	rbp		; save rbp
    
    mov	rbp, rsp         
    push rdx		; save registers
    push rdi
    push	 rsi
    
    ; n = [rbp + 24] - int
    ; a = [rbp + 16] - double
    

    fld1 ; res = 1 double   
    
    ._while: ; n != 0    
    mov rax, [rbp + 24]
    cmp rax, 0 

    je ._return ; n == 0
    
   ._check_for_oddity:   
    mov rax, [rbp + 24]
    and rax, 1    
    cmp rax, 0 ; n & 1 == 1
    
    je ._end_check
    
    fld qword [rbp + 16]; a
    fmulp st1, st0; res = res * a
    
    ._end_check:          
    fld qword [rbp + 16]
    fld qword [rbp + 16]
    fmulp st1, st0; a = a * a
    fstp qword [rbp + 16]
 
    sar qword [rbp + 24], 1; n >>= 1
    
    jmp ._while      
    
    
    ._return:
    ; return res - xmm0
    sub rsp, 8
    fstp qword [rsp]
    mov rax, [rsp]
    
    pop	rsi		; restore registers
    pop	rdi		; in reverse order
    pop	rdx   
    
    mov	rsp,rbp		; restore callers stack frame
    pop	rbp    
    ret			; return
    


global main
main:
    mov rbp, rsp; for correct debugging
    push rbx
    
    mov rdi, text_in
    mov rsi, a
    mov rdx, n
    mov rcx, eps
    mov rax, 0
    call scanf
    
    
    finit    

    fld qword [a]; r = a + 1; l = -a - 1
    fld1
    faddp st1, st0

    fldz
    fsub st0, st1
    fcomi st0, st1; l r
    ja ._else__   ; l > r
    
    ._if__:
    fstp qword [l]
    fstp qword [r]
    jmp ._end__if
    ._else__:
    fstp qword [r]
    fstp qword [l]

    
    ._end__if:
    mov rdi, lf_format
    movq xmm0, [l]
    mov rax, 1
    call printf
    
    mov rdi, lf_format
    movq xmm0, [r]
    mov rax, 1
    call printf
      
    ._while:
    fld qword [r]
    fld qword [l]
    fsubp st1, st0 
    fld qword [eps]
    fcomip st0, st1
    jae .end_while
    
    fadd qword [l]
    fadd qword [l]
    fdiv qword [two]
    fstp qword [m]

    push qword [n]
    push qword [m]
    call _pow
    add rsp, 16
    mov [p], rax
    
    fld qword [a]
    fld qword [p]
    fcompp
    
    fstsw ax
    sahf
    jbe ._else
    
    mov rax, [m]
    mov [r], rax
    jmp ._while
    
    ._else:
    
    mov rax, [m]
    mov [l], rax
    jmp ._while
    
    .end_while:
    mov rdi, lf_format
    movq xmm0, [l]
    mov rax, 1
    call printf

    pop rbx
    mov rax, 0

    xor rax, rax
    ret