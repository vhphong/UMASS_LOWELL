#lang racket

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++
(define nil '())

(define (map proc items)
  (if (null? items)
      nil
      (cons (proc (car items))
            (map proc (cdr items)))))

(define (filter predicate sequence)
  (cond ((null? sequence) nil)
        ((predicate (car sequence))
         (cons (car sequence)
               (filter predicate (cdr sequence))))
        (else (filter predicate (cdr sequence)))))

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

(define (fold-left op initial sequence)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter initial sequence))

;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; **********************************************************************
;;
;; 1. Assume that we want to develop an inventory database for an
;; online CD store.  
;;
;; For each CD, the database stores its title, artist, price, how many
;; copies are in stock, and its category of music (such as rock,
;; blues, or country).  
;;
;; Write a data definition for CD inventories. When completing the
;; following exercises, please make sure to use map, filter, and
;; accumulate (aka, reduce) as much as reasonable.  
;; 
;; 1a. Create a constructor procedure with parameters, title, artist,
;; price, category, and units-in-stock, and corresponding accessors to
;; retrieve these fields.  
;; 
;; 1b. Populate an inventory (i.e., a list) with 10 or so records
;; created from your constructor.  
;;
;; 1c. Write a procedure all-titles that consumes an inventory and
;; produces a list of all titles in the inventory.  
;; 
;; 1d. Write a procedure titles-in-stock that consumes an inventory
;; and produces a list of all titles in the inventory with at least 1
;; copy in stock.  
;;
;; 1e. Write a procedure restock that consumes a CD title, number of
;; new copies of that CD and an inventory and produces an inventory in
;; which the named CD has the given number of additional copies (and
;; all other CDs remain the same).  
;; 
;; 1f. Write a procedure titles-by that consumes an artist name and
;; inventory and produces a list of titles of CDs by that artist.
;; 
;; 1g. Write a procedure copies-in-stock that consumes a CD title,
;; artist name and an inventory and produces the number of copies of
;; that item that are in stock.  Return 0 if the named CD isn't in the
;; inventory.
;; 
;; 1h. Write a procedure blues-sale that consumes an
;; inventory and produces an inventory in which all blues CDs are
;; discounted by 10%.
;; 
;; 1i. Write a procedure carry-cd? that consumes a
;; title and artist name and produces a boolean indicating whether
;; that item is in the inventory (whether in or out of stock).
;;
;; This problem is courtesy of a lab exercise from WPI's Scheme
;; course.

; Answer:
;;;;;;;;;;1a.
;Constructors
; model the db as a list of records.
(define cdDB '() )

;Each record is a list of (title artist price category units-in-stock)
(define (make-record title artist price category units-in-stock)
  (list title artist price category units-in-stock))

; Insert one record into the database, by rebinding the global symbol
; cdDB to a new list with the new record appended.
(define (insert-record rec)
  (set! cdDB (append cdDB (list rec))))

; Accessors
; these should retrieve the appropriate item from the record-list.
; remember these are procedures.
(define title 
  (lambda (rec) (car rec)))
(define artist
  (lambda (rec) (car (cdr rec))))
(define price
  (lambda (rec) (car (cdr (cdr rec)))))
(define category
  (lambda (rec) (car (cdr (cdr (cdr rec))))))
(define units-in-stock
  (lambda (rec) (car (cdr (cdr (cdr (cdr rec)))))))

;;;;;;;1b.

;insert a bunch of records.
;see examples in file "freds-db.rkt"
;make sure to submit that file back for autograding.
;but you should put your own here!!
(insert-record (make-record "Love, Shelby" "Shelby Lynne" 14.98 'country 5))
(insert-record (make-record "Phantom Blues" "Taj Mahal" 9. 'blues 3))
(insert-record (make-record "Dirt" "Alice in Chains" 12.98 'rock 7))
(insert-record (make-record "What Does It Take (To Win Your Love)"
               "Jr. Walker & The All Stars"
               9.98
               'motown
               3))
(insert-record (make-record "Midnight Run"
               "Bobby Blue Bland"
               9.
               'blues
               2))
(insert-record (make-record "Saxphone Colossus"
               "Sonny Rollins"
               12.98
               'jazz
               3))
(insert-record (make-record "Live at Montreux"
               "Miles & Quincy"
               17.98
               'jazz
               2))
(insert-record (make-record "Abbey Road"
               "The Beatles"
               14.98
               'rock
               0))
(insert-record (make-record "Revolver"
               "The Beatles"
               14.98
               'rock
               3))
(insert-record (make-record "The White Album"
	       "The Beatles"
	       19.99
	       'rock
	       7))

;;;;;;;1c.
; all-titles
; map the title operator over the db.
(define (all-titles db)
  (map title db))

;;;;;;1d.
; titles-in-stock
; filter the db for units-in-stock being more than 0,
; then map the title operator over it.
(define (titles-in-stock db)
  (all-titles (filter (lambda (rec) (> (units-in-stock rec) 0)) db)))
  

;;;;;;;1e.
; restock
; map a fcn over the database that returns either:
;  a new record with the num of copies increased by the restock count, or
;  just the existing record (if title doesn't match
(define (restock this-title num-copies db)
  (define (fcn tc nc dbc)
    (cond ((empty? dbc) '())
          ((eq? tc (title (car dbc)))
           (cons (make-record (title (car dbc)) (artist (car dbc)) (price (car dbc)) (category (car dbc)) (+ (units-in-stock (car dbc)) nc)) 
                 (fcn tc nc (cdr dbc))))
          (else (cons (car dbc) (fcn tc nc (cdr dbc))))))
  (if (filter (lambda (rec) (eq? (title rec) this-title)) db)
      (fcn this-title num-copies db)
      cdDB))
      
      
;;;;;;;;1f.
; titles-by
; filter the db by matching on artist, then map title over it.
(define (titles-by this-artist db)
  (all-titles (filter (lambda (rec) (eq? this-artist (artist rec))) db)))

;;;;;;;;1g.
; copies-in-stock
; filter by by matching title and artist, then apply units-in-stock to it.
(define (copies-in-stock this-title this-artist db)
  (if (not (empty? (filter (lambda (rec) (eq? this-title rec)) (titles-by this-artist db))))
      (units-in-stock (car (filter (lambda (rec) (and (eq? (title rec) this-title) (eq? (artist rec) this-artist))) db)))
      0))
      

;;;;;;;;1h. 
; blues-sale
; map a fcn over the db that either:
;  outputs a new record with adjusted price (if category is blues), or
;  just outputs the existing record
(define (blues-sale db)
  (define (fcn dbc)
    (cond ((empty? dbc) '())
          ((eq? 'blues (category (car dbc)))
           (cons (make-record (title (car dbc)) (artist (car dbc)) (- (price (car dbc)) .9) (category (car dbc)) (units-in-stock (car dbc))) 
                 (fcn (cdr dbc))))
          (else (cons (car dbc) (fcn (cdr dbc))))))
  (fcn db))

;;;;;;;;1i.
; carry-cd?
; filter the db for a matching record,
; then return a boolean if units-in-stock is more than 0.
(define (carry-cd? this-title this-artist db)
  (if (> (copies-in-stock this-title this-artist db) 0)
      #t
      #f))




;; **********************************************************************
;;
;; 2. Consider the following procedure for operating on trees:
(define (tree-manip tree init leaf accum) 
  (cond ((null? tree) init) 
        ((not (pair? tree)) (leaf tree)) 
        (else (accum  
               (tree-manip (car tree) init leaf accum) 
               (tree-manip (cdr tree) init leaf accum)))))

;; Suppose that we provide a test tree, 
(define test-tree '(1 (2 (3 (4) 5) 6) 7))
;;
;; 2a. Write the parameters to tree-manip that will count the number
;;     of leaves in the tree, evaluating