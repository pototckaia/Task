#lang racket

; Сформировать структуры с помощью cons, которые приводят 
; к печати 
; (1 . 2 3)
; (1 2 . 3)
; (1 . 2 . 3)


(define (print-list-structure x)
  (define (print-contents y)
    (print-list-structure (car y))
    (cond
      ((null? (cdr y)) '())
      ((not (pair? (cdr y)))
          (display " . ")
          (print-list-structure (cdr y)))
      (else
          (display " ")
          (print-contents (cdr y)))))
  (cond
    ((null? x)
        (display "()"))
    ((not (pair? x))
        (display x))
    (else
        (display "(")
        (print-contents x)
        (display ")"))))


; (1 2 3)
(print-list-structure (cons 1 (cons 2 (cons 3 '()))))
(display "\n")

; нельзя (1 . 2 3)
(print-list-structure (cons (cons 1 2) (cons 3 '()) ))
(display "\n")

; (1 2 . 3)
(print-list-structure (cons 1 (cons 2 3)))
(display "\n")

; нельзя (1 . 2 . 3)
(print-list-structure (cons (cons 1 2)  3) )
(display "\n")

