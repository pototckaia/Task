#lang racket

; same-parity

(define (same-parity? x y)
  (equal?  (even? x) (even? y)))

(define (eq-parity l)
  (filter-map (lambda (x) (and (same-parity? x (car l)) x)) l))


(eq-parity '(1 2 3 -2 8))
(eq-parity '(10 12 -2 333 76 12 74 75))
