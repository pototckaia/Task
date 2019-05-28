#lang racket

; Добавить предикаты, селекторы и 
; конструкторы для возведения в степень к
; программе символьного дифференцирования. 

; символьное дифференцирование
; (ax^2 + bx + c) ->/x (2ax + b)

; (u + v)' = u' + v'
; (u * v)' = u' * v + u * v'

; x, c - atom
; dx/dx = 1
; dc/dx = 0 (not (eq? 'c 'x))

; d(u^v)/dt = v * u^(v - 1) * du/dt + u^v * ln u(x) * dv/dx 


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
    [(pow? e) 
                (make-product
                   (make-pow ; u^(v-1)
                      (base e)
                      (make-sum (exponent e) -1))
                   (make-product
                       (exponent e)
                       (deriv (base e) v)))]
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

(define (=number? exp num)
  (and (number? exp) (= exp num)))

; (list '+ e1 e2)
(define (sum? e)
	(and (pair? e) (eq? (car e) '+)))

(define (addend e)
	(car (cdr e))) ; (cadr 3)

(define (augend e)
	(car (cdr (cdr e)))) ; caddr e

(define (make-sum a1 a2)
  (cond 
    [(=number? a1 0) a2]
    [(=number? a2 0) a1]
    [(and (number? a1) (number? a2)) (+ a1 a2)]
    [else (list '+ a1 a2)]))

; (list '* e1 e2)
(define (product? e) 
	(and (pair? e) (eq? (car e) '*)))

(define (multiplier e) 
	(car (cdr e))) ; 1

(define (multiplicant e) 
	(car (cdr (cdr e)))) ; 2

(define (make-product e1 e2)
  (cond 
    [(or (=number? e1 0) (=number? e2 0)) 0]
    [(=number? e1 1) e2]
    [(=number? e2 1) e1]
    [(and (number? e1) (number? e2)) (* e1 e2)]
    [else (list '* e1 e2)]))

; (list '^ b e)
(define (pow? e)
	(and (pair? e) (eq? (car e) '^)))

(define (base e)
	(car (cdr e)))

(define (exponent e)
	(car (cdr (cdr e))))

(define (make-pow e1 e2)
  (cond 
    [(=number? e1 0) 0]
    [(=number? e2 0) 1]
    [(=number? e2 1) e1]
    [(and (number? e1) (number? e2)) (expt e1 e2)]
    [else (list '^ e1 e2)]))


; (добавить возведение в степень)

; (xy + x)' = y + 1 
(deriv '(+ (* x y) x) 'x)
; 1
(deriv '(+ x 3) 'x)
; (xy)'x = y
(deriv '(* x y) 'x)
; (xy(x+3))'x = y(x+3) + xy
(deriv '(* (* x y) (+ x 3)) 'x)
; (x^3 + 1)' = 3x^2 
(deriv '(+ (^ x 3) 1) 'x)

