#lang r5rs
; s-,ap, s-filter, s-for-each, display-s, s-enumerate-interval, s-ref

(define (prime? x)
  #t)

(define (sum-primes a b)
  (define (iter count acc)
    (cond ((> count b) acc)
          ((prime? count) (iter (+ count 1) (+ count acc)))
          (else (iter (+ count 1) acc))))
  (iter a 0))

(enumerate-interval a b)

; [10 000, 1000 000] 10 007, 10 009
(enumerate-interval 1000 1000000)

(cadr (filter prime? (enumerate-interval 1000 1000000)))
(cons-s <a> <b>) == (cons <a> (delay <b>))
; delay -- специальная форма

(s-car <s>) == (car s)
(s-car s) == (force (cdr s))

(define (s-enumerate-interval a b)
  (if (> a b)
      the-e-s
      (cons-s a (s-enumerate-interval (+ a 1) b))))

(cons 1000 (delay (s-enumerate-interval 1000 1000000)))

(define (s-filter p s)
  (cond ((s-null? s) the-e-s)
        ((p (s-car s)) (cond-s (s-car s) (s-filter p (s-cdr s))))
        (else (s-filter p (s-cdr s)))))

(s-filter prime? (force (delay (s-enumerate-interval 1001 1000000))))

(delay e) == (lambda() e)
(define (force delayed-exp)
  (delayed-exp))

(delay e) == (memo-proc (lambda() e))
(define (memo-proc f)
  (let ((run? #f) (result #f))
    (lambda ()
    (if (not run?)
        (begin (set! run? #t) (set! result (f)) result)
        result))))

;  (define sum 0)
;  (define (accum x)
;  (set! sum (+ sum x))
;  sum)
; (define req (s-map accum (s-enumerate-interval 1 20)))
; (define y (s-filter ))
; (define z (s-filter (lambda (z) (= (reminder z 5) 0))))
; (stream-ref y 7)
; sum == ?
; (display-stream z)
; sum == ?