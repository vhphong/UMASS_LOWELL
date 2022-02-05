#lang racket

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++
(define (square x) (* x x))
 
(define (scale-list items factor)
  (if (null? items)
      '()
      (cons (* (car items) factor)
            (scale-list (cdr items) factor))))

(define (accumulate op initial sequence)
 (if (null? sequence)
     initial
     (op (car sequence)
         (accumulate op initial (cdr sequence)))))

(define x (list (list 1 2) (list 3 (list 4 5)))) 

;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


;; **********************************************************************

;; 1. For each of the following definitions, 
;;    a. Draw the box and pointer diagram 
;;    b. Give the sequence of cars and cdrs needed to return the number 4
(define a (list 1 2 3 4))
(define b (cons (cons 3 4) (cons 5 6)))
(define c (list 1 (list 2 3) 4))

;; Answer part a of this question using comment line and change #f to
;; #t
      
;; For box-and-pointer diagrams, you may either draw in ASCII in this
;; buffer (and comment out), or you may hand-draw and submit images of
;; your drawings, or, you may draw using a software program and submit
;; PNG files.

;; Just bundle the additional files with your submission. The
;; auto-grader will ignore them, and we'll review them manually.

;a)
(define p1_a #t)

;b)
; To get 4 from a
(define (p1_b1 a) (car (cdr (cdr (cdr a)))))

; To get 4 from b 
(define (p1_b2 b) (cdr (car b)))

;To get 4 from c 
(define (p1_b3 c) (car (cdr (cdr c))))
      
;; **********************************************************************

;; 2. Draw a box and pointer diagram for each of the lists d, e and f
;; defined as follows:
(define d (list 1 2))
(define e (cons d d))
(define f (append d d))

;; 3. What would be printed by Scheme when asked for the values of d,
;; e and f sequentially?  Answer this question using comment line and
;; change #f to #t
(define p3 #t)
;; '(1 2)
;; '((1 2) 1 2)
;; '(1 2 1 2)

;; **********************************************************************

;; 4. Consider the following recursive procedure:
(define (list-prod lst) 
  (if (null? lst) 
      1 
    (* (car lst) 
       (list-prod (cdr lst))))) 

;; a) How many times is list-prod called when evaluating the
;; expression (list-prod '(1 2 3 4)) ?

;; b) What is the order of growth in space and time for the list-prod
;; procedure above?

;; c) Write an iterative version of the procedure list-prod.    

;; d) What is the order of growth in space and time for your iterative
;; list-prod procedure from part c?

;; Answer (a) (b) and (d) using comment line and change #f to #t 
(define p4 #t)
;; a) 4
;; b) O(n)
;; c) O(n)
;; d) O(1)

;; For (c), fill in the below procedure
(define (list-prod-iter 1st)
  (define (iter rslt current)
    (if (null? current)
        rslt
        (iter (* (car current) rslt) (cdr current))))
  (iter 1 1st))

;; **********************************************************************

;; 5. Write a procedure called double-list in three different ways:
;; a) Write a list manipulation procedure of your own to do this.
;; b) Use the scale-list procedure on pp. 105 in your definition.
;; c) Use the map procedure on pp. 105 in your definition.

;;Answer:
;a)
(define (double-list1 lst)
  (if (empty? lst)
     '()
     (cons (* (car lst) 2) (double-list2 (cdr lst)))))
    

;b)
;; using scale-list 
(define (double-list2 lst)
  (scale-list lst 2))

;c)
;; using map
(define (double-list3 lst)
  (define (map proc items)
  (if (null? items)
      '()
      (cons (proc (car items))
            (map proc (cdr items)))))
  (map (lambda (x) (* x 2)) lst))

;; **********************************************************************

;; 6. SICP exercise 2.21 (pp. 106), on square-list.

;;Answer:
(define (square-list items)
  (if (empty? items)
      '()
      (cons (square (car items))
            (square-list (cdr items)))))

(define (square-list-using-map items)
  (define (map proc items)
  (if (null? items)
      '()
      (cons (proc (car items))
            (map proc (cdr items)))))
  (map square items))


;; **********************************************************************

;; 7. SICP exercise 2.33 (pp. 119), implementing map, append, and
;; length.  
;;
;; uncomment line starting with "accumumlate" and replace with answer

(define (my-map op sequence)
 (accumulate (lambda (x y) (cons (op x) y )) '() sequence))

(define (my-append seq1 seq2)
 (accumulate cons seq2 seq1))

(define (my-length sequence)
 (accumulate (lambda (x y) (+ 1 y)) 0 sequence))

;; **********************************************************************

;; 8. SICP exercise 2.35 (pp. 120), redefining count-leaves as an
;; accumulation.  Fill in the below procedure.
;;
;; uncomment line starting with "accumumlate" and replace with answer

(define (count-leaves t)
  (accumulate + 0 
              (map (lambda (x) 
                     (if (not (pair? x)) 
                         1
                         (count-leaves x)))
                   t)))

;; *********************************************************************

;; 9. SICP exercise 2.4. Here is an alternative procedural
;; representation of pairs. For this representation, verify that (car
;; (cons x y)) yields x for any objects x and y.

(define (my-cons x y)
  (lambda (m) (m x y)))

(define (my-car z)
  (z (lambda (p q) p)))

;; What is the corresponding definition of my-cdr? (Hint: To verify
;; that this works, make use of the substitution model of Section
;; 1.1.5.)  Fix the code below to work.

(define (my-cdr z)
  (z (lambda (p q) q)))

;; ************************ END OF FILE *********************************
