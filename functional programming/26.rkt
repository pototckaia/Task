#lang racket

; same-parity

(define (same-parity? x y)
  (eq?  (even? x) (even? y)))

(define (eq-parity a . l)
  (filter-map (lambda (x) (and (same-parity? x a) x)) l))


(eq-parity 1 2 3 2 8)
(eq-parity 10 12 2 333 76 12 74 75)

(eq? #f null)
(eq? #f #t)
(eq? #f #f)
