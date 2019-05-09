#lang racket

; (list +)
(define p (list list +))

; ('list '+) 
(define q '(list +))

; ('list '+)
(define r (list 'list '+))

((car p) 3 4); (list 3 4)
((cadr p) 3 4) ; (+ 3 4)

; not working -> 'list and '+ symbol
; ((car r) 3 4)
;((cadr r) 3 4)

; not working -> same
;((cadr q) 3 4)

