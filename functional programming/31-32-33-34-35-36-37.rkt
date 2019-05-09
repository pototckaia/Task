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

(display "\nnumber 32\n")
(acc-length '(1 2 3 4 5))
 

;  33    

(define (acc-map f l)
  (custom-accumulate 
    (lambda (x y) (cons (f x) y)) empty l))

(define (squre x) (* x x))

(display "\nnumber 33\n")
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

(display "\nnumber 34\n")
(custom-accumulate-n + 0 (list (list 1 2 3) (list 4 5 6) (list 7 8 9) (list 10 11 12)))

; 35     

; (append (list 1 2) (list 3 4 5) (list 6 7 8 9)) -> плоский список

(define (acc-append-n acc ll)
  (cond
    [(null? ll) null]
    [(null? (cdr ll)) 
      (acc-append acc (car ll))] ; last
    [else 
      (acc-append-n (append acc (car ll)) (cdr ll))]))

(define (append-n . ll)
  (acc-append-n empty ll))

; Реализовать так, чтобы append не переписывал последний спосок
(define l-last '(6 7 8 9) )

(display "\nnumber 35\n")
(append-n (list 1 2) (list 3 4 5) l-last)
(display l-last)
(newline)

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
(define (matrix-*-matrix m n)
    (let ([cols (transpose n)])
        (map 
            (lambda (x) (matrix-*-vector cols x)) 
            m)))



(define m (list (list 1 2 3 4) (list 4 5 6 6) (list 6 7 8 9)))
(define v (list 1 2 3 4))
(define a (list (list 8 7) (list 6 5) (list 4 3) (list 2 1)))
(define v2 (list (list 1 2 3 4)))

(display "\nnumber 36\n")
(dot-product v v) ; 30
(matrix-*-vector m v) ; 30 56 80
(transpose m)
(matrix-*-matrix v2 a)

; 37

; The accumulate procedure is also known as fold-right, because it combines the first
; element of the sequence with the result of combining all the elements to the right.

; fold-right=accumulate 
;  для x=(x1,x2,...,xn) формируется и 
; затем оценивается выражение
; (op x1 (op x2 (op ...(op xn init)...)))

(define (fold-right op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (fold-right op initial (cdr sequence)))))

; There is also a fold-left, which is similar to fold-right, except that it combines elements
; working in the opposite direction:

;  для x=(x1,x2,...,xn) формируется и 
; затем оценивается выражение
; (op (...  (op (op init x1) x2)...) xn)

(define (fold-left op initial sequence)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter initial sequence))


; Объяснить результаты оценок выражений3
(display "\nnumber 37\n")
; (/ 1 (/ 2 (/ 3 1))) 
(fold-right / 1 (list 1 2 3))
;  (/ (/ (/ 1 1) 2) 3)
(fold-left / 1 (list 1 2 3))
;  (1 (2 (3 '())))
(fold-right list '() (list 1 2 3))
; ((('() 1) 2) 3)
(fold-left list '() (list 1 2 3))


; Какими свойствами должна обладать бинарная операция op, 
; чтобы результаты fold-right и fold-left для нее совпадали 
; для всех начальных значений и списков 
; (с доказательством, начиная 1, 2 и т.д. элементов в списке)?   

; Функция op должна быть коммутативной и ассоциативной
; 1. Ассоциативность
;  x1 op x2 ... op xn op init 
;  init op x1 op x2 op ... op xn 

;  Раставим скобки
;  (x1 op x2 ... op xn) op init 
;  init op (x1 op x2 op ...op xn)
; 2. Коммутативность 
;  init op (x1 op x2 ... op xn) 
;  init op (x1 op x2 op ...op xn)