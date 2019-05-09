#lang racket
; 1 - дана функция в инфиксной форме, найти производную.
; Рассмотреть два варианта:
; 1) Все скобки расставлены '((x * y) * (x + 3)).
; 2) Скобки не все. Учитывать приоритет операций '(x * y * (x + 3)).
; Изменение предикатов, селекторов, конструкторов (car - cadr - cddr).
; Основная программа не меняется.


; '3 == 3
(define p (list list +))
(define q '(list +))
(define r (list 'list '+))

((car p) 3 4)
((cadr p) 3 4)
;((car r) 3 4)
;((cadr q) 3 4)

; (define p (list list +))
; (define q '(list +))
; (define r (list 'list '+))
; Объяснить результаты оценки
; ((car p) 3 4)
; ((cadr p) 3 4)
; ((car r) 3 4)
; ((cadr q) 3 4)

; 2 - (occurences 'a '((a b)((a a) c b (((a))))))


;(withdraw 25) - снять со счета 25 баксов.
; Если денег нет, то напишет, что средств недостаточно. Иначе - оставшуюся сумму.
; (define balance 100)
; (define (withdraw a)
;   (if (> balance a)
;       (begin (set! balance (- balance a))
;              balance)
;       "Н/с"))
; 
; (withdraw 25)
; (withdraw 75)


; begin <e1> <e2> ... (оценка по очереди)
; set! <v> <e> задать новое значение заранее созданной переменной
; 3 - создать банковский счёт с паролем, снятием и добавлением денег
; Генераторы объектов

(define simplified-withdraw
  (let ((balance 100))
    (lambda (a)(if (> balance a)
        (begin (set! balance (- balance a))
             balance)
        "Н/с"))))

(simplified-withdraw 25)
(simplified-withdraw 25)
(simplified-withdraw 75)

(define (make-account balance)
  (define (withdraw a)
    (if (> balance a)
      (begin (set! balance (- balance a))
             balance)
      "Н/с"))
  (define (deposit a)
    (begin (set! balance (+ balance a)) balance))
  (define (dispatch m)
    (cond [(eq? m 'w) withdraw]
          [(eq? m 'd) deposit]
          [else (error "Н/с" m)]))
  dispatch)

(define a1 (make-account 100))
(define a2 (make-account 100))
((a1 'w) 25)
((a2 'w) 25)
((a1 'w) 25)
((a1 'd) 100)