#lang racket
(define (my_compose f g)
  (lambda (x)
    (f (g x))))

((my_compose - sqrt) 10)

((my_compose sqrt -) 10)
