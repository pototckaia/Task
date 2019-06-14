#lang racket
(require compatibility/mlist)

(define (mystery x)
  (define (loop x y)
    (if (null? x)
        y
        (let ((cdrx (mcdr x))) ; сохранения старого значения cdr пары x
          (set-mcdr! x y) ; x -> y
          (loop cdrx x)))); cdrx x
  (loop x '()))

; Объясните, что за задачу выполняет mystery
(define v (mlist 'a 'b 'c))
(define w (mystery v))
(display w)

; 1. 
; x = ('a 'b 'c)
; y = ()
; cdrx := 'b 'c
; x := 'a

; 2. 
; x = 'b 'c
; y = 'a 
; cdrx := 'c
; x := 'b 'a

; 3. 
; x = 'c 
; y = 'b 'a
; cdrx := ()
; x := 'c 'b 'a