#lang racket


; accumuled - 
; на вход подается список -> 
; перезаписать cons заменить на op, а nill на init

(define (custom-accumulate op init l)
  (if (null? l)
    init
    (op (car l) (custom-accumulate op init (cdr l)))))

;  31  
(define (acc-append l1 l2)
  (custom-accumulate cons l2 l1))

(display "number 31\n")
(acc-append '(1 2 3 4) '(5 6 7 8))
 
;  32    

(define (acc-length l)
  (custom-accumulate (lambda (x y) (+ 1 y)) 0 l))

(display "number 32\n")
(acc-length '(1 2 3 4 5))
 

;  33    

(define (acc-map f l)
  (custom-accumulate 
    (lambda (x y) (cons (f x) y)) empty l))

(define (squre x) (* x x))

(display "number 33\n")
(acc-map squre '(1 2 3 4 5))

; 34 

; The procedure accumulate-n is similar to accumulate except that it takes as its
; third argument a sequence of sequences, which are all assumed to have the same
; number of elements. It applies the designated accumulation procedure to combine
; all the first elements of the sequences, all the second elements of the results. 
; For instance, if s is a sequence containing four sequences, 
;
; ((1 2 3) (4 5 6) (7 8 9) (10 11 12))
;
; then the value of (accumulate-n + 0 s) should be (22 26 30). Fill in the missing
; expressions in the following definition of accumlate-n:


(define (custom-accumulate-n op init seqs)
	(if (null? (car seqs))
		'()
		(cons (custom-accumulate op init (map car seqs))
			(custom-accumulate-n op init (map cdr seqs)))))	 

(display "number 34\n")
(custom-accumulate-n + 0 (list (list 1 2 3) (list 4 5 6) (list 7 8 9) (list 10 11 12)))

; 35     

; (define (append .  ll)
;(последний список не должен переписываться)  

; (define (append <> . <> l1))

; (append (list 1 2) (list 3 4 5) (list 6 7 8 9)) -> плоский список

; (define (append_ ll)
;   (if (null? ll)
;     null
;     (append (car ll) (append_ (cdr ll)))))
; Реализовать так, чтобы append не переписывал последний спосок


; 36

; Suppose we represent vectors v = (v1) as sequences of numbers, and matrices m = (mij) as sequences
; of vectors (the rows of the matrix). For example, the matrix

; (( 1 2 3 4 )
;  ( 4 5 6 6 )
;  ( 6 7 8 9 ))

 
(define (dot-product v w)
    (custom-accumulate + 0 (custom-accumulate-n * 1 (list v w))))

(define (matrix-*-vector m v)
  (map (lambda (x) (dot-product x v)) m))

(define (transpose mat)
  (custom-accumulate-n cons '() mat))

; строку на столбец
; (define (matrix-*-matrix m n)
;     (let ((cols (transpose n)))
;         (map <??> m)))



(define m (list (list 1 2 3 4) (list 4 5 6 6) (list 6 7 8 9)))
(define v (list 1 2 3 4))
(define a (list (list 8 7) (list 6 5) (list 4 3) (list 2 1)))
(define v2 (list (list 1 2 3 4)))

(display "number 36\n")
(dot-product v v) ; 30
(matrix-*-vector m v) ; 30 56 80
(transpose m)
; (matrix-*-matrix v2 a)

; 37

; The accumulate procedure is also known as fold-right, because it combines the first
; element of the sequence with the result of combining all the elements to the right.
; There is also a fold-left, which is similar to fold-right, except that it combines elements
; working in the opposite direction:

; (define (fold-left op initial sequence)
;   (define (iter result rest)
;     (if (null? rest)
;         result
;         (iter (op result (car rest))
;               (cdr rest))))
;   (iter initial sequence))

; (define (fold-right op initial sequence)
;   (if (null? sequence)
;       initial
;       (op (car sequence)
;           (fold-right op initial (cdr sequence)))))

; (fold-right / 1 (list 1 2 3))
; (fold-left / 1 (list 1 2 3))
; (fold-right list '() (list 1 2 3))
; (fold-left list '() (list 1 2 3))

; Give a property that op should satisfy to guarantee that fold-right and fold-left will
; produce the same values for any sequence.

; op needs to obey the commutativity property. This means that the function is the same 
; in one direction as it is in the other.