#lang racket
(require compatibility/mlist)

; подсчет количества пар в структуре - count-pairs.

(define (mmemq? x l)
	(not (eq? (mmemq x l) #f)))

(define (count-pairs l)
	(define (iter-count-pair x pairs-pass)
		(define new-pair-pass (mcons x pairs-pass))
		(if (or (not (mpair? x)) (mmemq? x pairs-pass))
      		0
      		(+ (iter-count-pair (mcar x) new-pair-pass)
         	   (iter-count-pair (mcdr x) new-pair-pass)
               1)))
	
	(iter-count-pair l empty))


(define test1 (mlist 1 2 3))
(bad-count-pairs test1)

; (list 'foo) -> 1
; (cons .. ..) +1 -> 3
; (list ..) +1 ->  4
(define test2 (mlist (mcons (mlist 2) (mlist 1))))
(count-pairs test2)

(define test3 (mlist 1 2))
(set-mcdr! (mcdr test3) test3)
(count-pairs test3)
