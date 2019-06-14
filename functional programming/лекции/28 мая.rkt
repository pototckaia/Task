#lang r5rs
; records "name" -> (a, 1)
(define (assoc key records)
  (cond((null? records) #f)
       ((equal? key (caar records)) (car records))
       (else (assoc key (cdr records)))))

(define (lookup key table)
  (let ((record (assoc key (cdr table))))
    (if record
        (cdr record)
        #f)))

(define (insert! key value table)
  (let ((record (assoc key (cdr table))))
    (if record
       (set-cdr! record value)
       (set-cdr! table (cons (cons key value) (cdr table))))
    'done))

(define (memoize f)
  (let ((t (make-table)))
    (lambda (x)
      (let ((already-computed-result (lookup x t)))
        (or already-computed-result
            (let ((result (f x)))
              (insert! x result t)
              result))))))

(define memo-fib (memoize fib))
(define memo-fib1 (memoize (lambda (x)
                             (cond ((= n 0) 1)
                                   ((= n 1) 1)
                                   (else (+ (memo-fib (- n 1) (memo-fib (- n 2)))))))))

; # более приятные технологии
; последовательности как стандартные интерфейсы
; эффективная реализация

; stream-car
; stream-cdr
; cons-stream
; empty-stream?
; the-empty-stream
; stream-map
; stream-filter
; stream-for-each

(define (stream-for-each f s)
  (if (stream-empty? s)
      'done
      (begin (f (stream-car s)) (stream-for-each f (stream-cdr s)))))