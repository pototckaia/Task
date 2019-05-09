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

; du^c/dt = c * u^(c - 1) * du/dt 

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

; селекторы
; (addend s) - первое слагаемре
; (augend s) - второе слагаемое
; (multiplier s) - первый сомножитель
; (multiplicant s) - второй сомножитель
; (base s) - основание степени
; (exponent s) - степень 

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
		[(pow? e) (make-product)]
		))



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

; (list ^ b e)
(define (pow? e)
	(and (pair? e) (eq? (car e) '^)))
(define (base e)
	(car (cdr e)))
(define (exponent e)
	(car (cdr (cdr e))))
(define (make-pow e1 e2)
	(list '^ e1 e2))


; (добавить возведение в степень)

; (+ (+ (* 1 y) (* 0 x)) 1) 
; (xy + x)' = y + 1 
(deriv '(+ (* x y) x) 'x)

; (x^3 + 1)' = 3x^2 
; (deriv '(+ (^ x 3) 1) 'x)

; (define test (make-product 12 'x))

; (display test)
; (multiplier test)
; (multiplicant test)	
