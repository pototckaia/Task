#lang racket

(require compatibility/mlist)

(define (last-pair l)
  (if (null? (mcdr l))
      l
      (last-pair (mcdr l))))

(define (append! x y)
  (set-mcdr! (last-pair x) y) x)

(append! (mlist 1 2 3) (mlist 3 4 5))

(define (make-cycle? x)
   (set-mcdr! (last-pair x) x) x)

(define lst (mlist 1 2 3))
(display (make-cycle? lst))

; (define (mystery x)
;   (define (loop x y)
;     (if (null? x)
;         y
;         (let ((temp (cdr x)))
;           (set-cdr! x y)
;           (loop temp x))))
;   loop x 1)

; ; Разобраться, что происходит
; (define v '(a b c d))
; (define w (mystery v))
; (display w)

; ;(define q (make-queue))
; (insert-q! q 'a)
; ;(front q) -> a
; (delete-q! q)

; (define (make-queue)
;   (cons '() '()))

; (define (insert-q! q e)
;   (let ((new-pair)(cons e '()))
;     (cond ((empty-queue? q) (set-front-ptr! q new-pair) (set-rear-ptr! q new-pair) q)
;           (else (set-cdr! (rear-ptr q) new-pair) (set-rear-ptr! q new-pair) q))))

; (define (delete-q! q)
;   (cond ((empty-queue? q) (error "Удаление из пустой очереди" q))
;         (else (set-front-ptr! q (cdr (front-ptr q))) q)))

; (define (empty-queue? q)
;   (if (null? (front-ptr q))
;       true
;       false))

; (define (front q)
;   (cond ((empty-queue? q) (error "Пустая очередь" q))
;         (else (car (front-ptr q)))))

;Реализовать дек
; deq, make-deq, empty-d?, front-d, rear-d, front-insert-d!, rear-insert-d!, front-delete-d!, rear-delete-d!  
