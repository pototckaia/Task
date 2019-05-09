#lang racket

; n, s -заданные натуральные числа.
; Сформировать последовательность 
; троек (i,j,k), 1<=k<j<i<=n, таких, что
; i+j+k=s. 

(define (accumulate op init l)
  (if (null? l)
    init
    (op (car l) (accumulate op init (cdr l)))))


(define (flat-map f l)
	(accumulate append null (map f l)))


(define (eq-sum? list s)
	(= (accumulate + 0 list) s))


; n = 4
; (3, 2, 1), 
; (4, 2, 1), (4, 3, 2), (4, 3, 1)
;in-range right bound is not included

(define (triplet-n n)
	(flat-map 
		(lambda (i) 
			(flat-map 
				(lambda (j) 
					(map
						(lambda (k) (list i j k))
						(sequence->list (in-range 1 j)))) 
				(sequence->list (in-range 2 i)))) 
		(sequence->list (in-range 3 (+ n 1)))))

(triplet-n 4)

(define (seq-s s n)
	(filter (lambda (x) (eq-sum? x s)) (triplet-n n)))

(seq-s 7 4)
