#lang racket

; разработать occurances, которая определяет число 
; вхождений элемента e (число, символ, список) в список l. 
; Использовать предикат equal? для проверки равенства чисел (=), 
; символов (eq?) и структур, образованных с помощью cons.

; = numericall equal
;> (= 1 1.0)
;#t
;> (= 1 2)
;#f
;> (= 2+3i 2+3i 2+3i)
;#t

; eq to the same object
;> (eq? 'yes 'yes)
;#t
;> (eq? 'yes 'no)
;#f
;> (eq? (expt 2 100) (expt 2 100))
;#f
;> (eq? 2 2.0)
;#f
;> (let ([v (mcons 1 2)]) (eq? v v))
;#t
;> (eq? (mcons 1 2) (mcons 1 2))
;#f
;> (eq? (integer->char 955) (integer->char 955))
;#f
;> (eq? (make-string 3 #\z) (make-string 3 #\z))
;#f


(define (c-equal? v1 v2)
  (cond
    [(and (number? v1) (number? v2)) (= v1 v2)]
    [(and (symbol? v1) (symbol? v2)) (eq? v1 v2)]
    [(and (pair? v1) (pair? v2))
         (and
          (c-equal? (car v1) (car v2))
          (c-equal? (cdr v1) (cdr v2)))]
    [else (eq? v1 v2)]))

(define (occurences-acc acc s l)
  (cond
    [(null? l) acc]
    [(c-equal? s (car l)) (occurences-acc (+ acc 1) s (cdr l))]
    [else (occurences-acc acc s (cdr l))] ))

(define (occurences a list)
  (occurences-acc 0 a list))

(occurences 'a '((a b)((a a) c b (((a))))))
(occurences '(a b) '((a b)((a a) c b (((a))))))
