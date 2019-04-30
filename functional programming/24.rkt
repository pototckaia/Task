#lang racket
; (repeated f n): ((repeated square 2) 5)->625

; n = 1 -> \x.f
; n = 2 -> \x.f((\x.f) x) -> \x.f(f(x))
; n = 3 -> \x.f( (\x.f((\x.f)x)) x) -> \x.f( (\x.f(f(x))) x) -> \x. f(f(f(x)))
; ...
(define (repeated f n)
  (cond
    [(= n 1) (lambda (x) (f x))]
    [(> n 1) (compose (repeated f (- n 1)) f)]))

(define (square x)
  (* x x))

((repeated square 3) 5)

((repeated square 2) 10)

((repeated square 3) 4)