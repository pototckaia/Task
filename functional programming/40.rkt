#lang racket


; 1 - дана функция в инфиксной форме, найти производную.
; Рассмотреть два варианта:
; 1) Все скобки расставлены '((x * y) * (x + 3)).
; 2) Скобки не все. Учитывать приоритет операций '(x * y * (x + 3)).
; Изменение предикатов, селекторов, конструкторов (car - cadr - cddr).
; Основная программа не меняется.
; + и * имеют произвольную арность 
; БЕЗ ЛИШНИХ СКОБОК В РЕЗУЛЬТАТЕ

(define (deriv e v)  ; de/dv
  (cond 
    [(number? e) 0]
    [(var? e) (if (same-vars? e v) 1 0)]
    [(sum? e) (make-sum 
               (deriv (addend e) v) 
               (deriv (augend e) v))]
    [(product? e) (make-sum
                   (make-product 
                    (deriv (multiplier e) v)
                    (multiplicant e))
                   (make-product
                    (deriv (multiplicant e) v)
                    (multiplier e))
                   )]
    [else (error "unknow expression " e)]))


; предикаты
; (var? e) - переменная
; (same-vars? e1 e2) - одинаковые переменные
; (sum? e) - выражение является суммой
; (product? e) - выражение является произведением
; (pow? e) -  выражение степень
; (expt? e) - выражение

; конструкторы
; (make-sum a1 a2)
; (make-product m1 m2)
; (make-pow b e)
; (make-ln b)

; селекторы
; (addend s) - первое слагаемре
; (augend s) - второе слагаемое
; (multiplier s) - первый сомножитель
; (multiplicant s) - второй сомножитель
; (base s) - основание степени
; (exponent s) - степень

(define (get-n-items lst num)
    (if (> num 0)
        (cons (car lst) (get-n-items (cdr lst) (- num 1)))
        empty))

(define (=number? exp num)
  (and (number? exp) (= exp num)))

(define (var? e) (symbol? e))

(define (same-vars? e1 e2)
	(and (var? e1) (var? e2) (eq? e1 e2)))

; l1 + l2 + .. ln
(define (sum? e)
	(cond
		[(not (pair? e)) #f]
		[(or  (null? e) (null? (cdr e))) #f]
		[(eq? (cadr e) '+) #t]
		[else (sum? (cddr e))]))

(define (addend list)
	(define (addend_ cur item)
		(cond
			[(or
				(null? cur) 
				(null? (cdr cur))) null]
			[(eq? (cadr cur) '+) 
				(if (= item 1)
					(car cur)
					(get-n-items list item))]
			[else 
				(addend_ 
					(cddr cur) 
					(+ item 2))]))
	(if (pair? list) 
		(addend_ list 1)
		null))

; (display "addend\n")
; (addend '(x * y * (x + 3) ^ 3))
; (addend '(x + y + z))
; (addend '(x * y * z * y + z))
; (addend '((x * y + 122 * 1222) + z))
; (addend '(x * y * 122 * 1222 + z ^ 4))
; (addend '(y ^ 4 * 122 ^ 7 + z ^ 4))

(define (augend e)
	(cond
		[(not (pair? e)) null]
		[(or  (null? e) (null? (cdr e))) null]
		[(eq? (cadr e) '+) 
			(if (null? (cdddr e))
				(caddr e)
				(cddr e))]
		[else (augend (cddr e))]))

; (display "augend\n")
; (augend '(x + y))
; (augend '(x * y * (x + 3)))
; (augend '(x + y + z))
; (augend '(x * y * z * y + z))
; (augend '((x * y + 122 * 1222) + z))
; (augend '(x * y + 122 * 1222 + z + x + y))
; (augend '(y ^ 4 * 122 ^ 7 + z ^ 4))

(define (make-sum . l)
	(define (make-sum-l a l)
		(if (null? l)
			a
			(let ([f (car l)]
				  [r (cdr l)]
				  [sf? (pair? (car l))]
				  [sa? (pair? a)]
				  [lp (list '+ )])
				(cond
				  	[(=number? a 0) 
		  				(make-sum-l f r)]
		    		[(=number? f 0) 
		    			(make-sum-l a r)]
		  			[(and (number? f) (number? a)) 
		  				(make-sum-l (+ f a) r)]
		    		[sa? 
		    			(if sf?
		    				(make-sum-l (append (append a lp) f) r)
		    				(make-sum-l (append a (list '+ f)) r))]
		  			[sf? 
		  				(make-sum-l (append (list a '+) f) r)]
		    		[else 
		    			(make-sum-l (list a '+ (car l)) r)]))
			))
	(make-sum-l (car l) (cdr l)))

; (display "make-sum\n")
; (make-sum 123 '(x + 1) 23 33 'x 100 '(x * y) '(x + 2) '(z ^ 3))


(define (product? e (find #f))
	(cond
		[(or (not (pair? e)) (null? e)) #f]
		[(null? (cdr e)) find]
		[(eq? (cadr e) '+) #f]
		[(eq? (cadr e) '*) (product? (cddr e) #t)]
		[else (product? (cddr e) find)]))

; (display "product\n")
; (product? '(x ^ 4 * y))
; (product? '(x * y * (x + 3)))
; (product? '(x + y))
; (product? '(x * y ^ 4))
; (product? '(x * y + 122 * 1222 + z))

(define (multiplier l) 
	(define (m_ cur item)
		(cond
			[(or
				(null? cur) 
				(null? (cdr cur))) null]
			[(eq? (cadr cur) '*) 
				(if (= item 1)
					(car cur)
					(get-n-items l item))]
			[else 
				(m_ 
					(cddr cur) 
					(+ item 2))]))
	(if (pair? l) 
		(m_ l 1)
		null))

; (display "multiplier\n")
; (multiplier '(x ^ 4 * y))
; (multiplier '((x + 3) * y))
; (multiplier '(x * y ^ 4))

(define (multiplicant e) 
	(cond
		[(not (pair? e)) null]
		[(or  (null? e) (null? (cdr e))) null]
		[(eq? (cadr e) '*) 
			(if (null? (cdddr e))
				(caddr e)
				(cddr e))]
		[else (multiplicant (cddr e))]))

; (display "multiplicant\n")
; (multiplicant '(x ^ 4 * y))
; (multiplicant '((x + 3) * y * (x + 1 + 2)))
; (multiplicant '(x * y ^ 4))

; (define (make-product e1 e2) 
(define (make-product . l)
	(define (make-product-l a l)
		(if (null? l)
			a
			(let ([f (car l)]
				  [r (cdr l)]
				  [pf? (product? (car l))]
				  [pa? (product? a)]
				  [lm (list '*)])
				(cond
					[(or (=number? a 0) (=number? f 0)) 0]
				  	[(=number? a 1) 
		  				(make-product-l f r)]
		    		[(=number? f 1) 
		    			(make-product-l a r)]
		  			[(and (number? f) (number? a)) 
		  				(make-product-l (* f a) r)]
		    		[pa? 
		    			(if pf?
		    				(make-product-l (append (append a lm) f) r)
		    				(make-product-l (append a (list '* f)) r))]
		  			[pf? 
		  				(make-product-l (append (list a '*) f) r)]
		    		[else 
		    			(make-product-l (list a '* (car l)) r)]))
			))
	(make-product-l (car l) (cdr l)))

; (make-product 123 'x '(x + 10) '(x ^ 4) '(x * y * z) 'z)

; y * (x + 3) + x * y
(deriv '(x * y * (x + 3)) 'x)
; (x * (x + 3))
(deriv '(x * y * (x + 3)) 'y)
; 1 + y
(deriv '(x + y * (x + 3 + 2 * x)) 'x)
; 4 * z * (x + 3)
(deriv '(x + 4 * (x + 3) * z * y) 'y)