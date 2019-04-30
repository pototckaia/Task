#lang racket

; tree-map


(define (deep-map f l)
  (define (deep x)
    (cond 
    	[(null? x) x]
        [(pair? x) (map deep x)]
        [else (f x)]))
  (map deep l))

(deep-map (lambda (x) (+ 10 x)) (list 12 3 4 5 67))
(deep-map (lambda (x) (+ 10 x)) (list 12 (list 3 4 5 67)))
(deep-map (lambda (x) (+ 10 x)) (list (list 12 3) 4 5 67))