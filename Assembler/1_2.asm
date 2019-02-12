extern printf
extern scanf

global main

section .bss
    a: resq 1
    b: resq 1

section .data
    text_buf: db "a, b", 10, 0
    text_out: db "Коэффициент при наибольшем значении %d,",10, "Коэффициент при наименьшем значении %d", 10, "gcd(a, b) = %d", 10, 0
    text_inp: db "%d %d", 10, 0
    test_: db "%d %d %d %d", 10, 0
      
    a1: dq 1
    a2: dq 0
    
    b1: dq 0
    b2: dq 1
    
    q: dq 0
    r: dq 0
    
    tmp: dq 0

section .text
main:  
    push rbp
    
    mov rax, 0
    mov rdi, text_inp
    mov rsi, a
    mov rdx, b
    call scanf
    
    mov rax, [a]
    cmp rax, [b]
    jg check
    
    mov rax, [a]
    mov rbx, [b]
    mov [b], rax
    mov [a], rbx
    
    jmp check
    
start_loop: 
    mov rax, [a]
    cdq
    idiv qword [b]
    mov [q], rax
    mov [r], rdx
        
    ; (a, b) = (b, r)
    mov rbx, [b]
    mov [a], rbx
    mov rbx, [r]
    mov [b], rbx
    
    ; (a1, a2) = (a2, a1 - a2 * q)
    mov rbx, [a1]
    mov [tmp], rbx
    mov rbx, [a2]
    mov [a1], rbx
    
    mov rax, [q]
    imul qword [a2]
    mov rbx, [tmp]
    sub rbx, rax
    mov [a2], rbx
    
    ; (b1, b2) = (b2, b1 - b2 * q)
    mov rbx, [b1]
    mov [tmp], rbx
    mov rbx, [b2]
    mov [b1], rbx
    
    mov rax, [q]
    imul qword [b2]
    mov rbx, [tmp]
    sub rbx, rax 
    mov [b2], rbx
   
    
check:
    mov rax, [b]
    test rax, rax
    jne start_loop       

end_:
    mov rax, 0
    mov rdi, text_buf
    call printf

    mov rax, 0
    mov rdi, text_out
    mov rsi, [a1]
    mov rdx, [b1]
    mov rcx, [a] 
    call printf
    
    
    pop	rbp
    mov	rax,0
    
    xor rax, rax
    ret
