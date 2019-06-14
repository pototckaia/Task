#lang racket
(require racket/stream)

; Наша реализация потоков основана на особой форме под названием delay. Выполне-
; ние (delay h) не вычисляет h, а вместо этого возвращает так
; называемый задержанный объект (delayed object). Мы можем считать, что это «обеща-
; ние» вычислить выражение когда-нибудь в будущем. В качестве пары к delay имеется
; процедура force, которая берет задержанный объект в качестве аргумента и вычисляет
; его — фактически, заставляя delay выполнить обещание

; ((cons-stream hai hbi) (cons hai (delay hbi))
; (define (stream-car stream) (car stream))
; (define (stream-cdr stream) (force (cdr stream)))

; (delay h) (lambda () (h))
; (define (force delayed-object) (delayed-object))
; Решение состоит в том, чтобы строить задержанные объекты так, чтобы при первом
; вынуждении они сохраняли вычисленное значение. Последующие обращения будут про-
; сто возвращать сохраненное значение без повторения вычислений.

; (define (memo-proc proc)
;   (let ((already-run? false) (result false))
;     (lambda ()
;       (if (not already-run?)
;           (begin (set! result (proc))
;                  (set! already-run? true)
;                  result)
;           result))))
; (delay h) (memo-proc (lambda () h))

(define (stream-enumerate-interval low high)
  (if (> low high)
      '()
      (stream-cons
       low
       (stream-enumerate-interval (+ low 1) high))))

(define (display-stream s)
  (stream-for-each (lambda (x) (display x) (display " ")) s)
  (newline))

(define sum 0)
(define (accum x)
  (set! sum (+ x sum))
  sum)

(define seq (stream-map accum (stream-enumerate-interval 1 20)))

(define y (stream-filter even? seq))

(define z (stream-filter (lambda (x) (= (remainder x 5) 0)) seq))

; 1) Что будет результатом последовательного оценивания 

(display-stream seq)
(stream-ref y 7)
(display-stream z)

; 2) Будет ли результат различаться для случаев если спецформа (delay <exp>) 
;    реализована как (lambda () <exp>)? 

; Если бы не запомнили результаты отложенных вычислений, нам
; нужно было бы пересчитать элементы, которые «stream-ref» создал, 
; когда мы оценивали «display-stream». 
; Таким образом, результаты будут другими, потому что аккумулятор суммирует их в сумме дважды.


; 3)Какое значение принимает sum после оценки каждого из этих выражений?

(display sum)