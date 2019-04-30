#lang racket
; 22

(define (nth-deriv f x n)
  (define dx 0.001)
  (cond
    [(= n 1) (/ (- (f (+ x dx)) (f x)) dx)]
    [(> n 1) (/ (- (nth-deriv f (+ x dx) (- n 1)) (nth-deriv f x (- n 1))) dx)]))

(define (x x) x)
(define (xx x) (* x x))
(define (xxx x) (* x x x))

(display "deriv(x^2) = 2x\n")
(nth-deriv xx 1 1)
(nth-deriv xx 2 1)
(nth-deriv xx 3 1)

(display "deriv(x) = 1\n")
(nth-deriv x 1 1)
(nth-deriv x 2 1)
(nth-deriv x 3 1)

(display "deriv(x^3) = 3x^2\n")
(nth-deriv xxx 1 1)
(nth-deriv xxx 2 1)
(nth-deriv xxx 3 1)

(display "deriv(deriv(x^3)) = 6x\n")
(nth-deriv xxx 1 2)
(nth-deriv xxx 2 2)
(nth-deriv xxx 3 2)

(display "deriv(x^2) = 2x\n")
(nth-deriv xx 1 1)
(nth-deriv xx 2 1)
(nth-deriv xx 3 1)