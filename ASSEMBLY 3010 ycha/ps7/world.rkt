#lang racket

(require racket/include)

(define nil '())
(include "game.rkt")

;;;============================================================================
;;; You can extend this file to make more stuff part of your world.
;;;============================================================================

;;;============================================================================
;;; *CAVEAT* To keep your world consistent, whenever you change a procedure or 
;;;          redefine a person/place/etc you should reload this entire file    
;;;          into Scheme. This prevents you from having old-moldy folks running
;;;          around who have not evolved to adhere to your modifications. To   
;;;          make this work out well, you should create little scripts at the  
;;;          end of this file to make the game evolve as you work through it.  
;;;          [See the bottom of this file for an example.]                     
;;;============================================================================


(initialize-clock-list)

;; Here we define the places in our world...
;;------------------------------------------

(define conf-room           (make-place 'conf-room))
(define tom-office          (make-place 'tom-office))
(define dept-office         (make-place 'dept-office))
(define east-hall           (make-place 'east-hall))
(define ken-office          (make-place 'ken-office))
(define elevator-lobby      (make-place 'elevator-lobby))
(define computer-lab        (make-place 'computer-lab))
(define systems-lab         (make-place 'systems-lab))
(define west-hall           (make-place 'west-hall))
(define robotics-lab        (make-place 'robotics-lab))
(define network-closet      (make-place 'network-closet))
(define dungeon             (make-place 'dungeon))


;; One-way paths connect individual places in the world.
;;------------------------------------------------------

(define (can-go from direction to)
  (ask from 'add-neighbor direction to))

(define (can-go-both-ways from direction reverse-direction to)
  (can-go from direction to)
  (can-go to reverse-direction from))

(can-go-both-ways conf-room            'south    'north    tom-office)
(can-go-both-ways dept-office          'east     'west     tom-office)
(can-go-both-ways east-hall            'south    'north    dept-office)
(can-go-both-ways ken-office           'south    'north    east-hall)
(can-go-both-ways east-hall            'east     'west     conf-room)
(can-go-both-ways east-hall            'west     'east     elevator-lobby)
(can-go-both-ways elevator-lobby       'north    'south    computer-lab)
(can-go-both-ways elevator-lobby       'south    'north    systems-lab)
(can-go-both-ways elevator-lobby       'west     'east     west-hall)
(can-go-both-ways west-hall            'south    'north    network-closet)
(can-go-both-ways west-hall            'north    'south    robotics-lab)

(can-go dungeon        'up        network-closet)
(can-go network-closet 'secretly  systems-lab)



;; The important critters in our world...
;;---------------------------------------

(define fredm    (make&install-person 'fredm    robotics-lab        3))
(define swathi     (make&install-person 'swathi     computer-lab   2))
(define grendel  (make&install-troll  'grendel  dungeon        40))
(define gunther (make&install-student 'gunther computer-lab 2))
(define anna (make&install-advisor 'anna conf-room 2))

;; And some things for the world...
;;---------------------------------

(define late-homework 
  (make&install-thing 'late-homework  computer-lab))
(define opl-textbook
  (make&install-thing 'opl-textbook   computer-lab))
(define chalk
  (make&install-thing 'chalk           dept-office))
(define schedule-book
  (make&install-thing 'schedule-book   dept-office))
(define magic-password
  (make&install-thing 'magic-password  ken-office))

;; The beginning of an ever-expanding game script
;;------------------------------------------------

(define (play-game)
  (display (ask fredm 'go 'south))
  (display (ask fredm 'go 'east))
  (display (ask grendel 'move))
  (display (ask grendel 'move))
  true)

;; ...now whenever you re-load this file, you can bring things up to
;; date by invoking PLAY-GAME.
(define south 'south)
(define north 'north)
(define east 'east)
(define west 'west)