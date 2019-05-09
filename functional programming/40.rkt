#lang racket
; Модифицировать только предикаты, селекторы и
; конструкторы в программе символьного дифференцирования
; для того, чтобы проводить дифференцирование выражений,
; в которых  + и * имеют произвольную арность и * имеет более
; высокий приоритет, чем +, например,
; (x+3*x*(x+y)+z ).
; БЕЗ ЛИШНИХ СКОБОК В РЕЗУЛЬТАТЕ

; 1 - дана функция в инфиксной форме, найти производную.
; Рассмотреть два варианта:
; 1) Все скобки расставлены '((x * y) * (x + 3)).
; 2) Скобки не все. Учитывать приоритет операций '(x * y * (x + 3)).
; Изменение предикатов, селекторов, конструкторов (car - cadr - cddr).
; Основная программа не меняется.


(define (deriv e v)  ; de/dv
  (cond 
    [(number? e) 0]
    [(var? e) (if (same-vars? e v) 1 0)]
    [(sum? e) (make-sum 
               (deriv (addend e) v) 
               (deriv (augend e) v))]
    [(product? e) (make-sum
                   (make-product 
                    (deriv (multiplier e) v)
                    (multiplicant e))
                   (make-product
                    (deriv (multiplicant e) v)
                    (multiplier e))
                   )]
   ; [(pow? e) 
   ;             (make-product
   ;                (make-pow ; u^(v-1)
   ;                   (base e)
   ;                   (make-sum (exponent e) -1))
   ;                (make-product
   ;                    (exponent e)
   ;                    (deriv (base e) v)))]
    ))


; предикаты
; (var? e) - переменная
; (same-vars? e1 e2) - одинаковые переменные
; (sum? e) - выражение является суммой
; (product? e) - выражение является произведением
; (pow? e) -  выражение степень
; (expt? e) - выражение

; конструкторы
; (make-sum a1 a2)
; (make-product m1 m2)
; (make-pow b e)
; (make-ln b)

; селекторы
; (addend s) - первое слагаемре
; (augend s) - второе слагаемое
; (multiplier s) - первый сомножитель
; (multiplicant s) - второй сомножитель
; (base s) - основание степени
; (exponent s) - степень


(define (var? e) (symbol? e))
(define (same-vars? e1 e2) 
	(and (var? e1) (var? e2) (eq? e1 e2)))

; (list '+ e1 e2)
(define (sum? e)
	(and (pair? e) (eq? (car e) '+)))
(define (addend e)
	(car (cdr e))) ; (cadr 3)
(define (augend e)
	(car (cdr (cdr e)))) ; caddr e
(define (make-sum a1 a2)
	(list '+ a1 a2))

; (list '* e1 e2)
(define (product? e) 
	(and (pair? e) (eq? (car e) '*)))
(define (multiplier e) 
	(car (cdr e))) ; 1
(define (multiplicant e) 
	(car (cdr (cdr e)))) ; 2
(define (make-product e1 e2) 
	(list '* e1 e2))
