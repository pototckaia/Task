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
; обратный порядок
(display w)

