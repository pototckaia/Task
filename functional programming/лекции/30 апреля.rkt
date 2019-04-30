#lang racket
(require math/number-theory)

; Дано n, 1 <= j < i <= n
; (i + j) - простое, добавить в выходной список
; enumerate [1, n],

; map (lamdba (i) 
; 	(map (lamdba (j)
; 		(list  i j)
; 		(enumerate 1 (- i 1))))
; 		(enumerate 2 n))

; i = 2 ((2 1))
; i = 3 ((3 1)(3 2))

; нужно сделать плоским (accumulate append nill)

(define (accumulate op init l)
  (if (null? l)
    init
    (op (car l) (accumulate op init (cdr l)))))


(define (flat-map f l)
	(accumulate append null (map f l)))

;in-range right bound is not included
(define (d-pairs n)
	(flat-map 
		(lambda (i) 
			(map 
				(lambda (j) (list i j)) 
				(sequence->list (in-range 1 i)))) 
		(sequence->list (in-range 2 (+ n 1)))))

; n = 6
; (2, 1)
; (3, 1), (3, 2)
; (4, 1), (4, 2), (4, 3)
; (5, 1), (5, 2), (5, 3), (5, 4)
; (6, 1), (6, 2), (6, 3), (6, 4), (6, 5)

(d-pairs 6)

(define (prime-pair? p)
	(prime?
		(+ (car p) (car (cdr p)) )))

(define (make-triple p)
	(list (car p) (car (cdr p)) (+ (car p) (car (cdr p)))))


(filter prime-pair? (d-pairs 6))
(map make-triple (filter prime-pair? (d-pairs 6)))


; DZ 1
; n, s - natural 
; все тройки различный чисел - 1 <= k < j < i <=n
; такие что i + j +k = s

; quote - defer evealuting
; (quote a) -> 'a
; (quote (a b c)) -> '(a b c)

;___________________________________________

(car ''a)
; = (car (quote (quote a))) = 


(eq? #f #t)

; подсписок с первого вхождения и до конца списка
(define (memq e l)
	(cond 
		[(null? l) #f]
		[(eq? e (car l)) l]
		[else (memq e (cdr l))]))

(memq 4 '(1 2 3 4 5 6))
(memq 'r '((r s) (b s)))
(memq 'r '(r s b s))


; символьное дифференцирование
; (ax^2 + bx + c) ->/x (2ax + b)

; (u + v)' = u' + v'
; (u * v)' = u' * v + u * v'

; x, c - atom
; dx/dx = 1
; dc/dx = 0 (not (eq? 'c 'x))

; du^c/dt = ... 

; предикаты
; (var? e) - переменная
; (same-vars? e1 e2) - одинаковые переменные
; (sum? e) - выражение является суммой
; (product? e) - выражение является произведением
; (expt? e) - выражение

; конструкторы
; (make-sum a1 a2)
; (make-product m1 m2)

; селекторы
; (addend s) - первое слагаемре
; (augend s) - второе слагаемое
; (multiplier s) - первый сомножитель
; (multiplicant s) - второй сомножитель

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
								)]))



(define (var? e) (symbol? e))
(define (same-vars? e1 e2) 
	(and (var? e1) (var? e2) (eq? e1 e2)))

; (list '+ e1 e2)
(define (sum? e)
	(and (pair? e) (eq? (car e) '+)))
(define (addend e)
	(cdr (car e))) ; (cadr 3)
(define (augend e)
	(car (cdr (cdr e)))) ; caddr e

(define (make-sum a1 a2)
	(list '+ a1 a2))

; добавить возведение в степень

(deriv '(* x y) 'x)
(deriv '(+ (^ x 3) 1) 'x)


