#lang racket
(require compatibility/mlist)

; make-deque, предикат empty-deque?, селекторы front-deque и rear-deque, и
; мутаторы frontinsertdeque!, rear-insert-deque!, front-delete-deque! и rear-delete-deque!.

; Все операции должны выполняться за Θ(1) шагов.

(define (deque-item prev x next)
	(mlist prev x next))

(define (prev-item i) (mcar i))
(define (set-prev-item! i new-prev) (set-mcar! i new-prev))
(define (data-item i) (mcar (mcdr i)))
(define (next-item i) (mcar (mcdr (mcdr i))))
(define (set-next-item! i new-next) (set-mcar! (mcdr (mcdr i)) new-next))

(define (make-deque)
	(mcons empty empty))


(define (empty-deque? d)
	(or (null? (mcar d)) (null? (mcdr d))))

(define (front-deque d)
	(if (empty-deque? d)
		(error "deque empty")
		(data-item (mcar d))))

(define (back-deque d)
	(if (empty-deque? d)
		(error "deque empty")
		(data-item (mcdr d))))

(define (front-insert-deque! d x)
	(define item (deque-item empty x empty))
	(cond
		[(empty-deque? d)
			(set-mcar! d item)
			(set-mcdr! d item)]
		[else 
			(set-next-item! item (mcar d))
			(set-prev-item! (mcar d) item)
			(set-mcar! d item)]))

(define (back-insert-deque! d x)
	(define item (deque-item empty x empty))
	(cond
		[(empty-deque? d)
			(set-mcar! d item)
			(set-mcdr! d item)]
		[else 
			(set-prev-item! item (mcdr d))
			(set-next-item! (mcdr d) item)
			(set-mcdr! d item)]))

(define (front-delete-deque! d)
	(define data empty)
        (define new-head empty)
	(cond
		[(empty-deque? d) (error "deque empty")]
		[else 
			(set! data (data-item (mcar d)))
                        (set! new-head (next-item (mcar d)))
			(set-next-item! (mcar d) empty)
                        (if (not (null? new-head))
                            (set-prev-item! new-head empty)
                            empty)  
                        (set-mcar! d new-head)
			data]))

(define (back-delete-deque! d)
	(define data empty)
        (define new-tail empty)
	(cond
		[(empty-deque? d) (error "deque empty")]
		[else 
			(set! data (data-item (mcdr d)))
                        (set! new-tail (prev-item (mcdr d)))
                        (set-prev-item! (mcdr d) empty)
                        (if (not (null? new-tail))
                            (set-next-item! new-tail empty)
                            empty)                      
                        (set-mcdr! d new-tail)

                        
			data]))

(define (print-deque d)
	(define (print-deque_ i) 
		(cond 
			[(null? i) empty]
			[else 
				(display (data-item i))
                                (display " ")
				(print-deque_ (next-item i))]))
        (if (empty-deque? d)
            empty
            (begin
              (print-deque_ (mcar d))
              (newline))))


(define mq (make-deque))
(back-insert-deque! mq 'a)
(print-deque mq)
(display "back deque\n")
(display (back-deque mq))
(newline)

(front-insert-deque! mq 'c)
(print-deque mq)
(display "front deque\n")
(display (front-deque mq))
(newline)


(back-insert-deque! mq 'b)
(print-deque mq)
(display "back deque\n")
(display (back-deque mq))
;(newline)


;(display "front delete\n")
(front-delete-deque! mq)
;(print-deque mq)

;(display "back delete\n")
(back-delete-deque! mq)
;(newline)
(print-deque mq)

(front-delete-deque! mq)
(empty-deque? mq)