#lang racket

;fringe

(define (flatten lst)
	(cond
		[(null? lst) lst]
		[(pair? (car lst)) (append (flatten (car lst)) (flatten (cdr lst)))]
		[else (cons (car lst) (flatten (cdr lst)))]))


(flatten '(1 (2 3) (4 (5 6) (7 8 (9)))))

; Write a procedure fringe that taeks as argument a tree (represented as a list) and returns a list
; whose elements are all the leaves of the tree arranged in left-to-right order. For example,