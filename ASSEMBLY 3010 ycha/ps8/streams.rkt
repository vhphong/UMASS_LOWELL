#lang racket

;;; STREAMS

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