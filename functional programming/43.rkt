#lang racket

; .make-account с паролем и подсчетом числа неправильных вводов пароля

(define (make-account balance password)
	(define countPassword 0)
	(define (withDraw a)
	    (if (>= balance a)
	        (begin (set! balance (- balance a))
	               balance)
	        (error "Insufficient funds\nBalance: " balance)))
	(define (deposit a)
            (set! balance (+ balance a))
    	    balance)
	(define (dispatch m)
		(cond 
			[(eq? m 'w) withDraw]
			[(eq? m 'd) deposit]
			[else "Unknown request"]
		))
	(define (withPassword m p)
          (cond
            [(= countPassword 3)
               "B/n"]
            [(eq? p password)
                  (set! countPassword 0)
                  (dispatch m)]
	    [else
               (set! countPassword (+ 1 countPassword))
               "H/n"])
          		)
	withPassword)

(define a1 (make-account 100 ""))
(define a2 (make-account 100 "password"))

(define (withDraw acc p a)
  (let ([fun (acc 'w p)])
    (if (string? fun)
        fun
        (fun a))))

(withDraw a1 "" 25)

(withDraw a2 "" 25)
(withDraw a2 "" 25)
(withDraw a2 "password" 25)

(withDraw a2 "" 25)
(withDraw a2 "" 25)
(withDraw a2 "password" 25)

(withDraw a2 "" 25)
(withDraw a2 "" 25)
(withDraw a2 "" 25)
(withDraw a2 "password" 25)
(withDraw a2 "password" 25)
(withDraw a2 "password" 25)


