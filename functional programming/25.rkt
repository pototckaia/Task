#lang racket
; (2.5): (a,b)-> 2^a3^b=(cons a b): разработать car,cdr

(define (my-cons a b)
  (* (expt 2 a) (expt 3 b))) 

(define (find-degree number ex)
  (cond
   [(= (modulo number ex) 0) (+ 1 (find-degree (truncate (/ number ex)) ex))]
   [else 0]))

(define (my-car p)
  (find-degree p 2))

(define (my-cdr p)
  (find-degree p 3))

(my-car (my-cons 2 2))
(my-cdr (my-cons 2 2))

(my-car (my-cons 15 3))
(my-cdr (my-cons 15 3))

(my-car (my-cons 20 6))
(my-cdr (my-cons 20 6))

