#lang racket
(define a (read))
(define i (list 1 5 10 25 50))

(define (call nm ls)
  (cond
    [(empty? ls) 0]
    [(= nm 0)    1]
    [(< nm 0)    0]
    [else (+ (call nm (rest ls)) (call (- nm (first ls)) ls))]))

(call a i)