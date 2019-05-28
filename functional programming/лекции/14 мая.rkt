#lang racket

(define (make-account b)
	(define (withDraw a)
		(set! b (- b a))
                (display b)
                (newline))
	(define (deposit a) empty)
	(define (dispatch m)
		(cond [(eq? 'w m) withDraw]))
	dispatch)

(define a1 (make-account 100))
(define a2 (make-account 100))

((a1 'w) 25)

(define (withDraw acc a)
	((acc 'w) a))

(withDraw a2 25)

; Д.з 1
; (define a1 (make-account 100 'password))
; ((a1 'password 'w) 25)
; 75
; ((a1 'password 1 'w) 25);
; H/n
; ((a1 'password3 'w) 25)
; B/n

; ----------------------------
; среда - последовательность фреймов (список)
; фрейм - таблица назначения переменных - множество пары <пер>:<знач>
; у фрейма указатель на среду
;
; A={x:3,y:5}, B={x:7, z:6}, C={y:2, m:1}
; A<--- B, C; Среда - (A), (B, A), (C, A)
; EVAL(оценка)/APPLY
; f = описание + указатель на среду -> {x1:.., x2:..} параметры
; 1. set! <var> <exp>
; 2. define <var> <exp>

(define (make-withDraw b)
  (lambda (a)
    (if (>= b a)
        (begin (set! b (- b a)) b)
        'H/n )))

(define w1 (make-withDraw 100))
(define w2 (make-withDraw 100))

(w1 25)

; дз 2 - на листочки - диаграмма среды
(define a1_ (make-account 100))
(define a2_ (make-account 50))

((a1_ 'w) 25)
((a2_ 'w) 25)

; Модификаторы (!)
; set!
; set-car!
; set-cdr!
(set-car! x y)
(define a (cond y (cdr x)))