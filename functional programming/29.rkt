#lang racket

;deep-reverse	

; (define (custom-reverse l)
; 	(cond 
; 		[(null? l) l]
; 		[else (append (custom-reverse (cdr l)) (list (car l)))]))

(define (custom-reverse lst)
	(define (reverse-aux lst acc)
		(if (null? lst)
			acc
			(reverse-aux (cdr lst) (cons (car lst) acc))))
	(reverse-aux lst '()))


(define (deep-reverse lst)
	(define (get-reverse x)
		(if (pair? x)
			(iter-deep-reverse x empty)
			x))
	(define (iter-deep-reverse lst acc)
		(cond
			[(null? lst) acc]
			[else 
				(iter-deep-reverse 
					(cdr lst)
					(cons (get-reverse (car lst)) acc))]))
	(iter-deep-reverse lst empty))

(custom-reverse '(1 2 3 4 5 6 7))


;((((9) 8 7) (6 5) 4) (3 2) 1)
(deep-reverse '(1 (2 3) (4 (5 6) (7 8 (9)))) )
