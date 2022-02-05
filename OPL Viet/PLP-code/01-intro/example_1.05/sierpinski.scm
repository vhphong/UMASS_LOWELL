#lang racket

; Sierpinski triangles
; Run DrRacket, and load this file
; See https://docs.racket-lang.org/teachpack/2htdpimage.html
; and https://docs.racket-lang.org/teachpack/2htdpimage-guide.html

(require 2htdp/image) ; draw a picture
(let sierpinski ([n 8])
    (cond
          [(zero? n) (triangle 2 'solid 'red)]
	      [else (define t (sierpinski (- n 1)))
		              (freeze (above t (beside t t)))]))
