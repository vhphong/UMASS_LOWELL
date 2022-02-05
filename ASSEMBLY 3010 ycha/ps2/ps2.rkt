#lang racket

;;+++++++++++++++ Required for auto grading +++++++++++++
(define (square x) (* x x))
(define (identity x) x) 
(define (next x) (+ x 1)) 
(define (inc n) (+ n 1))

;;++++++++++++++++++++++++++++++++++++++++++++++++++


;; 1. exercise 1.9 (pp. 36). In this problem, you will study two implementations of addition in terms of 
;;    increment and decrement, and analyze whether the implementations are iterative or recursive.
;; Write the required steps for each procedure using comment line and then change #f to #t
(define add #t)
;; First, we check to see if a is equal to zero, if this is the case, we return b.  When a is not equal to zero,
;; the first procedure decrements a first, then it adds that value with b, then it increments the sum of
;; those two values.  This procedure is iterative.

;; We check to see if a is equal to zero and return b if the statement is true.  When a is not equal to zero,
;; the second procedure increments b first, then decrements a, and then sums the two returning values to
;; produce the output.  This procedure is iterative.

;;***************************************************************************************************

;; 2. exercise 1.11 (pp. 42). In this problem, you implement a recursive mathematical function using 
;;    both recursive and iterative processes.
;; fill in the below procedures

;f(n) as a recursive process
(define (f-recursive n)
     (cond ((< n 3) n)
           (else (+ (f-recursive (- n 1))
                    (* 2 (f-recursive (- n 2)))
                    (* 3 (f-recursive (- n 3)))))))

; f(n) as an iterative process
(define (f-iterative n)
    (define (iter a b sum count)
      (if (< count 3)
          sum
          (iter b sum (+ sum (* 2 b) (* 3 a)) (- count 1))))
  (iter 0 1 2 n))

;;***************************************************************************************************

;; 3. When implementing an iterative process in Scheme, the Scheme interpreter uses tail-recursion. 
;;    Explain what this means.
;; Answer this question using comment line and change #f to #t
(define tail-recursion #t)
;; Tail recursion is when we start from the base case first and keep calling the procedure iteratively 
;; until we have called the procedure n number of times.  Each time we call the procedure, we keep a 
;; running sum and return that sum once we have called the procedure n times.  The iterative process
;; is executed in constant space even if the iterative process is described by a recursive procedure.

;;***************************************************************************************************

;; 4. SICP exercise 1.16 (pp. 46).
;; fill in the below procedures

(define (fast-expt b n) 
   (define (iter a b n)
     (cond ((= n 0) a)
           ((even? n) (iter a (square b) (/ n 2)))
           (else (iter (* a b) b (- n 1)))))
  (iter 1 b n))

;;***************************************************************************************************

;; 5. More iteration: SICP exercise 1.30 (pp. 60).
;; Un-comment and fill in the below procedure

(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a) (+ result (term a)))))
  (iter a 0))


;;***************************************************************************************************

;; 6. Working towards higher-order procedures: Do SICP exercise 1.31 (a) and (b) (pp. 60–61).
;; fill in the below procedures

;a)Recursive product procedure
(define (product1 term a next b) 
     (if (> a b) 
         1
         (* (term a) (product1 term (next a) next b))))

; factorial procedure in terms of product
(define (factorial n) 
   (product1 identity 1 next n)) 

;Approximations to pi using john wallis' formula
(define (pi-term n) 
  (if (even? n)
      (/ (+ n 2) (+ n 1))
      (/ (+ n 1) (+ n 2))))

;b) Iterative product procedure
(define (product2 term a next b)
  (define (iter a res)
    (if (> a b) 
        res
        (iter (next a) (* (term a) res))))
  (iter a 1))

;;*****************************************************************