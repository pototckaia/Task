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
    three: dq 3.0
    two: dq 2.0
    four: dq 4.0
    N: dq 1
    
    tmp: dq 1

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

;call = [rbp + 16]
;a = [rbp + 24]
;b = [rbp + 32]
simpson:
    push rbp
    mov rbp, rsp
     
    finit
    
    fld qword [rbp + 32]
    fsub qword [rbp + 24]
    fild qword [N]
    fdivp st1, st0;  1 = (b - a)/N
        
    push qword 1; k
    push qword 0; k - 1
    
    .while:
    mov rax, [rsp + 8]
    mov rbx, [N]
    cmp rax, rbx; k > N
    jg .end_while
        
    
    fild qword [rsp]; k - 1
    fmul st0, st1; (k - 1) * (b-a)/N
    fadd qword [rbp + 24]; a + (k-1) * (b-a)/n = a1
    fstp qword [rsp]; a1
    call [rbp + 16]       
    
    push qword rax ; F(a1)
    fld qword [rsp]
    pop qword rax
    fadd qword [result] ; result += result + F(a1)
    fstp qword [result];
    
 
    fild qword [rsp + 8]; k
    fmul st0, st1; (k) * (b-a)/N
    
    fadd qword [rbp + 24]; a + (k) * (b-a)/n = b1
    push qword 0
    fstp qword [rsp]; b1
  
    call [rbp + 16]
 
    push qword rax; F(b1)
    fld qword [rsp]
    pop qword rax
    fadd qword [result]
    fstp qword [result]; result += result + F(b1)
      

                                 
    fld qword [rsp+8]; a1
    fadd qword [rsp]; b1
    fdiv qword [two]
    push 0
    fstp qword [rsp]; (a1 + b1 ) / 2 = x1
    call [rbp + 16]  
    pop qword rbx  
    
         
    push qword rax
    fld qword [rsp];  F((a1 + b1)/2)
    pop qword rax                                  
    fmul qword [four]; 4 * F((a1 + b1)/2)
    fadd qword [result]
    fstp qword [result]; result += result + 4 * F(x1)
    
    pop rax;
    pop rax;
    pop rax; k
    mov rbx, rax
    inc rax; k++
    
    push rax
    push rbx    
   
    jmp .while
     
    .end_while:
    
     
    fdiv qword [six] 
    fst qword [tmp]   
    fmul qword [result]; result * (b-a)/(3*N)
    fstp qword [result]
    

    mov rsp, rbp
    pop rbp
    ret

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
    
    push qword [b]
    push qword [a]
    push qword _F
    call simpson
    pop rax  
    pop rax
    pop rax  
    
          
    mov rdi, lf_format
    movq xmm0, [result]
    mov rax, 1
    call printf      
        
    pop rbx
    xor rax, rax
    ret