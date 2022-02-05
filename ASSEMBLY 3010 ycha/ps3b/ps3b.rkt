#lang racket

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++

(define a (list (list 1 2) (list 3 (list 4 5)))) 

;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; **********************************************************************

;; 1. SICP exercise 2.20 (pp. 104), on the dotted-tail notation.
;; While answering this question you may write helper procedures
(define (same-parity first . lst)
  (define (filter op list)
    (if (empty? list)
        '()
        (if (op (car list))
                (cons (car list)(filter op (cdr list)))
                (filter op (cdr list)))))
  (cond ((empty? list) '())
        ((even? first) (cons first (filter even? lst)))
        ((odd? first) (cons first (filter odd? lst)))))
      

;; **********************************************************************

;; 2. Solve SICP exercise 2.27 on deep-reverse. Note: it is be easy
;; enough to Google for the answer on this.  Obviously this will
;; short-circuit your learning.  So don't do that, and instead please
;; show steps along the way to your solution e.g., partly working
;; code, what inputs you tested it on, what results it produced, what
;; you did next.

; reverse
; this should be reverse the items at the top level of the list
(define (reverse items) 
   (define (iter list rslt)
     (if (empty? list)
         rslt
         (iter (cdr list) (cons (car list) rslt))))
  (iter items '()))

;; This procedure is a result of an idea of creating a iterative version of 
;; scale list.  Starting with a base item first and working my way up to the top
;; results in a reverse list and all that needed to be done was to implement
;; the iterative process of scale list without a scale being applied.

; deep reverse
; recursively reverse sublists
(define (deep-reverse items) 
  (define (proc items rslt)
    (cond ((empty? items) rslt)
         ((pair? (car items)) (cons (proc (cdr items) rslt) (proc (car items) rslt)))
         (else (reverse items))))
  (proc items '()))

;; I ran (deep-reverse a) and got an output of ((() (4 5) 3) 2 1) and was unable
;; to come up with a solution to get deep-reverse to work.  I also made another deep-reverse
;; procedure that would produce an output of (((5 4 3 ) 3) (2 1)) but I could not
;; figure out where the extra three was coming from.  After many hours trying to 
;; solve this problem I am near the end of the deadline and have no more time to work
;; on the problem.  

;; ************************ END OF FILE *********************************
