#lang racket

;;; +++++++++ Required for auto grading (from streams.rkt) ++++++++++++

;; Allow name nil to be used for the empty list.
(define nil '()) 			

;; Some other constants with non-traditional names:
(define true #t)
(define false #f)

;; For stream programming section 3.5
;; We use a force and delay which are slightly
;; different from the force and delay defined in the book:
;; delay (aka make-promise) handles recursive forcing.

(define the-empty-stream '())
(define stream-null? null?)
(define stream-car car)
(define (stream-cdr s)
  (force (cdr s)))

(define-syntax cons-stream
  (syntax-rules ()
    ((_ head tail)
     (cons head (delay tail)))))

(define (stream-ref a n)
  (if (= n 0)
      (stream-car a)
      (stream-ref (stream-cdr a) (- n 1))))

(define (stream-map proc s)
  (if (stream-null? s)
      the-empty-stream
      (cons-stream (proc (stream-car s))
                   (stream-map proc (stream-cdr s)))))

(define (stream-for-each proc s)
  (if (stream-null? s)
      the-empty-stream
      (begin (proc (stream-car s))
             (stream-for-each proc (stream-cdr s)))))

(define (stream-filter pred stream)
  (cond ((stream-null? stream) the-empty-stream)
        ((pred (stream-car stream))
         (cons-stream (stream-car stream)
                      (stream-filter pred
                                     (stream-cdr stream))))
        (else (stream-filter pred (stream-cdr stream)))))

(define (display-stream s)
  (stream-for-each display-line s))

(define (display-line x)
  (newline)
  (display x))

(define (stream-enumerate-interval low high)
  (if (> low high)
      the-empty-stream
      (cons-stream
       low
       (stream-enumerate-interval (+ low 1) high))))

(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))

(define integers (integers-starting-from 1))

(define (add-streams s1 s2)
  (stream-map + s1 s2))

(define (stream->list stream)
            (if (stream-null? stream)
                '()
                (cons (stream-car stream)
                      (stream->list (stream-cdr stream)))))

;;; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


;;; *******************************************************************
;;; Problem 1:
;;; 
;;; Use stream-map (pp. 320 of textbook) to define a procedure called
;;; convert-temps that takes a stream of temperatures in Fahrenheit
;;; and returns a stream of converted temperatures in Celsius. Recall
;;; that to convert Fahrenheit to Celsius, the equation is C = 5/9 *
;;; (F-32).

(define (convert-temps fahrenheit-stream)
  (stream-map (lambda (x) (* (/ 5 9) (- x 32))) fahrenheit-stream))


;;; ******************************************************************
;;; Problem 2:
;;; 
;;; Use stream-filter (pp. 322 of textbook) to define the stream of
;;; all integers that are evenly divisible by 2, 3, or 5.
;;;


(define (divisible? x y)
  (= (remainder x y) 0))

(define (divisible-by-2-3-5 int-stream)
  (stream-filter (lambda (x) (or (divisible? x 2) (divisible? x 3) (divisible? x 5))) int-stream))



;;; ******************************************************************
;;; Problem 3:
;;; 
;;; Replace the lambda function to complete the following alternative
;;; definition of the integers stream:
;;;
;;; (define my-integers (cons-stream 1 (stream-map <??> my-integers)))
;;;

(define my-integers
  (cons-stream 1 (stream-map (lambda (x) (+ 1 x)) my-integers)))

 
;;; ******************************************************************
;;; Problem 4:
;;; 
;;; Complete Exercise 3.51 on pp. 325 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.51
;;;
;;; In order to take a closer look at delayed evaluation, we will use
;;; the following procedure, which simply returns its argument after
;;; printing it:
;;;
(define (show x)
  (display-line x)
  x)
;;;
;;; What does the interpreter print in response to evaluating each
;;; expression in the following sequence?
;;;
;;; Put your answer in comments and change the symbol #f to #t after
;;; answering.

(define p4_1 #t)
;;; (define x (stream-map show (stream-enumerate-interval 0 10)))
; 0

(define p4_2 #t)
;;; (stream-ref x 5)
; 5

(define p4_3 #t)
;;; (stream-ref x 7)
;7


;;; ******************************************************************
;;; Problem 5:
;;;
;;; Complete Exercise 3.52 on pp. 325–326 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.52
;;;
;;; Consider the sequence of expressions
;;;
(define sum 0)
(define (accum x)
(set! sum (+ x sum))
sum)
;;; (define seq (stream-map accum (stream-enumerate-interval 1 20)))
;;; (define y (stream-filter even? seq))
;;; (define z (stream-filter (lambda (x) (= (remainder x 5) 0))
;;;                          seq))
;;; (stream-ref y 7)
;;; (display-stream z)

;;;
;;; What is the value of sum after each of the above expressions is
;;; evaluated? What is the printed response to evaluating the
;;; stream-ref and display-stream expressions? Would these responses
;;; differ if we had implemented (delay <exp>) simply as (lambda ()
;;; <exp>) without using the optimization provided by memo-proc ?
;;; Explain.
;;;
;;; Put your answers in comments, and change the value of p5 from
;;; #f to #t after answering.
(define p5 #t)

;;; (define seq (stream-map accum (stream-enumerate-interval 1 20)))
;sum =1
;;; (define y (stream-filter even? seq))
;sum = 6
;;; (define z (stream-filter (lambda (x) (= (remainder x 5) 0))
;;;                          seq))
;sum = 10
;;; (stream-ref y 7)
; 136
;;; (display-stream z)
; 10
; 15
; 45
; 55
; 105
; 120
; 190
; 210
; sum = 210

;When using the non-optimized version of delay, we would obtain different
; results because the evaluation of (accum x) might give give different results
; depending on the value of sum.
;(define seq (stream-map accum (stream-enumerate-interval 1 20)))
; sum = 1
; seq = (1 (accum 2) (accum 3) (accum 4) ...)
;(define y (stream-filter even? seq))
; y = (6 (stream-filter even? ((accum 4) (accum 5) ...)))
; sum = 6
;(define z (stream-filter (lambda (x) (= (remainder x 5) 0))
;                         seq))
; the second argument of stream-filter (think it as a local copy of seq)
;  is (1 8 11 15 (accum 5) ...)
; z = (15 (stream-filter (lambda (x) (...)) ((accum 5) ...)))
; sum = 15
;(stream-ref y 7)        
; y = (6 24 30 54 64 100 114 162 (stream-filter even? ((accum 18) ...)))
; So it returns 162
; sum = 162
;(display-stream z)
; z = (15 (stream-filter (lambda (x) (...))
;  (162+5=167 167+6=173 173+7=180 180+8=188 188+9=197 197+10=207
;   207+11=218 218+12=230 230+13=243 243+14=257 257+15=272 272+16=288
;   288+17=305 305+18=323 323+19=342 342+20=362)
; 15
; 180
; 230
; 305
; sum = 362

;;; ******************************************************************
;;; Problem 6:
;;; 
;;; Complete Exercise 3.53 on pp. 330 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.53
;;;
;;; Without running the program, describe the elements of the stream
;;; defined by
;;;
;;; (define s (cons-stream 1 (add-streams s s)))
;;;
;;; Put your answers in comments, and change the value of p6 from
;;; #f to #t after answering.
(define p6 #t)

; s is a stream of powers of 2 because it doubles the previous value an infinite number
; of times.

;;; ******************************************************************
;;; Problem 7:
;;; 
;;; Complete Exercise 3.54 on pp. 331 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.54
;;;
;;; Define a procedure mul-streams, analogous to add-streams, that
;;; produces the elementwise product of its two input streams. Use
;;; this together with the stream of integers to complete the
;;; following definition of the stream whose nth element (counting
;;; from 0) is n + 1 factorial:
;;;
;;; (define factorials (cons-stream 1 (mul-streams <??> <??>)))

(define (mul-streams s1 s2)
  (stream-map * s1 s2))

(define factorials
  (cons-stream 1 (mul-streams factorials integers)))


;;; ******************************************************************
;;; Problem 8:
;;;
;;; Complete Exercise 3.57 on pp. 332 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.57
;;;
;;; Given this implementation of Fibonacci:
;;;
;;; (define fibs
;;;   (cons-stream 0
;;; 	       (cons-stream 1
;;; 			    (add-streams (stream-cdr fibs)
;;; 					 fibs))))
;;;
;;; 

(define p8_1 #t)
;;; How many additions are performed when we compute the nth Fibonacci
;;; number using the definition of fibs based on the add-streams
;;; procedure?

;n-1 additions are performed.

(define p8_2 #t)
;;;  Show that the number of additions would be exponentially greater
;;;  if we had implemented (delay <exp>) simply as (lambda () <exp>),
;;;  without using the optimization provided by the memo-proc
;;;  procedure described in section 3.5.1.

;the number of additions would be N(m) = N(m-1) + N(m-2) + 1.

;;;
;;; Put your answers in comments, and change the values of p8_1 and
;;; p8_2 from #f to #t after answering.

;;; ************************ END OF FILE *****************************