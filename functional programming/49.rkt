#lang r5rs

; Одномерная таблица - список записей, 
; каждая из которых из которых представляет 
; пару состоящию из ключа и связанного с ним значения. 

; backbone - связующие пары
; headed list - хребтовая пара

 ; assoc не видит фиктивной записи
(define (assoc key records)
	(cond ((null? records) false)
		((equal? key (caar records)) (car records))
		(else (assoc key (cdr records)))))

(define (lookup key table)
	(let ((record (assoc key (cdr table))))
		(if record
			(cdr record)
			false)))

(define (insert! key value table)
	(let ((record (assoc key (cdr table))))
		(if record
			(set-cdr! record value)
			(set-cdr! table
					(cons (cons key value) (cdr table)))))
’ok)

(define (make-table)
	(list ’*table*))


; Мемоизация (memoization) 
; (называемая также табуляризация (tabulation)) 
; — прием, который позволяет процедуре записывать
; в локальной таблице единожды вычисленные значения.
; Такой прием может сильно повысить производительность программы. 
; Мемоизированная процедура поддерживает таблицу, 
; где сохраняются результаты предыдущих вызовов, 
; а в качестве ключей используются аргументы, относительно
; которых эти результаты были получены. 
; Когда от мемоизированной процедуры требуют вычислить значение, 
; сначала она проверят в таблице, нет ли там уже нужного
; значения, и если да, то она просто возвращает это значение. 
; Если нет, то она вычисляет значение обычным способом и заносит его в таблицу.

(define (memoize f)
	(let ((table (make-table)))
		(lambda (x)
			(let ((previously-computed-result (lookup x table)))
				(or previously-computed-result
					(let ((result (f x)))
						(insert! x result table)
						result))))))

(define (fib n)
	(cond ((= n 0) 0)
		((= n 1) 1)
		(else (+ (fib (- n 1))

(fib (- n 2))))))

; Мемоизированная версия той же самой процедуры выглядит так:
(define memo-fib (memoize fib))

(define memo-fib1 (memoize (lambda (n)
							(cond ((= n 0) 0)
								  ((= n 1) 1)
								  (else (+ (memo-fib1 (- n 1))
									       (memo-fib1 (- n 2))))))))

(memo-fib 3)
(memo-fib1 3)

; 1) почему (memoize fib)  не сокращает число шагов оценивания fib
; 2) показать, что число шагов вычислений с использованием memo-fib пропорционально n 
; (любые табличные операции выполняются за единицу времени) 

; Ответ

; 1. fin вызывает себя рекурсивно. Только последннее вычисленное значения добавляется в таблицу. 
; Все промежуточные вычисления не запоминаются и каждый раз ищутся заново. 

; Пример.
; (memo-fib 3) -> table - 3: 2
; (memo-fib1 3) -> table - 3: 2, 
; 						 2: 1, 
; 						 1: 1


; 2. Так как вычисленные значения никогда не пересчитываются. 
; Необоходимое число шагов для оценки (memo-fib1 n) пропорционально n. 