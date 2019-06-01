#lang racket
(require compatibility/mlist)

(define (last-pair l)
  (if (null? (mcdr l))
      l
      (last-pair (mcdr l))))

(define (make-cycle x)
   (set-mcdr! (last-pair x) x) x)
; проверка наличия цикла в структуре


(define (mmemq? x l)
  (not (eq? (mmemq x l) #f)))

(define (loop? l)
  (define (iter-loop? x pairs-pass)
    (define new-pair-pass (mcons x pairs-pass))
    (cond
      [(not (mpair? x)) #f]
      [(mmemq? x pairs-pass) #t]
      [else (or
              (iter-loop? (mcar x) new-pair-pass)
              (iter-loop? (mcdr x) new-pair-pass))]))
  (iter-loop? l empty))


(loop? (mcons 1 2))
(loop? (mlist 'a 'c 'b))
(loop? (make-cycle (mlist 1 2 3)))