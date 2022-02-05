;;; mc-eval.ss
;;; Metacircular evaluator from section 4.1 of SICP

;;; NOTE:
;;; uses R5RS language -- not racket!

;;; enter the interpreter by evaluating in the REPL:
;;;   (mc-eval-loop)
;;;
;;; also, if you exit the interpreter, you can restart it without
;;; reinitializing the global environment with:
;;;   (driver-loop)

;;; mc-eval and mc-apply are the heart of the evaluator

(define (mc-eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((or? exp) (eval-or exp env)) ; our or implementation
	((and? exp) (eval-and exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp) (lambda-body exp) env))
        ((begin? exp) (eval-sequence (begin-actions exp) env))
        ((cond? exp) (mc-eval (cond->if exp) env))
	((let? exp) (mc-eval (let->combination exp) env))
        ((application? exp)
         (mc-apply (mc-eval (operator exp) env)
		(list-of-values (operands exp) env)))
        (else (error "Unknown expression type -- MC-EVAL"))))


(define (mc-apply procedure arguments)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure procedure arguments))
        ((compound-procedure? procedure)
         (eval-sequence
          (procedure-body procedure)
	  (extend-environment (procedure-parameters procedure)
			      arguments
			      (procedure-environment procedure))))
        (else (error "Unknown procedure type -- MC-APPLY" procedure))))

;;; list-of-values is used to produce the list of arguments to which
;;; a procedure is to be applied

(define (list-of-values exps env)
  (if (no-operands? exps)
      '()
      (cons (mc-eval (first-operand exps) env)
	    (list-of-values (rest-operands exps) env))))


;;; eval-if evaluates the predicate part of an if expression in the
;;; given environment

(define (eval-if exp env)
  (if (true? (mc-eval (if-predicate exp) env))
      (mc-eval (if-consequent exp) env)
      (mc-eval (if-alternative exp) env)))


;;; eval-sequence is used by mc-apply to evaluate the sequence of 
;;; expressions in a procedure body and by eval to evaluate the
;;; sequence of expressions in a begin expression

(define (eval-sequence exps env)
  (cond ((last-exp? exps) (mc-eval (first-exp exps) env))
        (else (mc-eval (first-exp exps) env)
              (eval-sequence (rest-exps exps) env))))


;;; eval-assignment handles assignment to variables

(define (eval-assignment exp env)
  (set-variable-value! (assignment-variable exp)
                       (mc-eval (assignment-value exp) env)
                       env)
  'ok)


;;; eval-definition handles definition of variables

(define (eval-definition exp env)
  (define-variable! (definition-variable exp)
                    (mc-eval (definition-value exp) env)
                    env)
  'ok)


;;; Following are the procedures that define the syntax of our language
;;; We preface the usual scheme commands with "uml:" to allow us to 
;;; differentiate when we are using the metacircular evaluator to 
;;; evaluate expressions (it will only be used for "uml:" expressions)
;;; and when scheme code is being evaluated by the usual scheme 
;;; interpreter

;;; Self-evaluating entities: numbers and strings

(define (self-evaluating? exp)
  (cond ((number? exp) #t)
	((string? exp) #t)
	(else #f)))

;;; Variables

(define (variable? exp) (symbol? exp))

;;; Quotations

(define (quoted? exp) 
  (tagged-list? exp 'uml:quote))

(define (text-of-quotation exp) (cadr exp))

;;; Special forms (in general)

(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))

;;; Assignment--- set!

(define (assignment? exp) 
  (tagged-list? exp 'uml:set!))

(define (assignment-variable exp) (cadr exp))

(define (assignment-value exp) (caddr exp))

;;; Definitions

(define (definition? exp)
  (tagged-list? exp 'uml:define))

(define (definition-variable exp)
  (if (symbol? (cadr exp))
      (cadr exp)
      (caadr exp)))

(define (definition-value exp)
  (if (symbol? (cadr exp))
      (caddr exp)
      (make-lambda (cdadr exp)		;formal parameters
		   (cddr exp))))        ;body

;;; lambda expressions

(define (lambda? exp) (tagged-list? exp 'uml:lambda))

(define (lambda-parameters exp) (cadr exp))

(define (lambda-body exp) (cddr exp))

;;; constructor for lambda expressions, used by definition-value above

(define (make-lambda parameters body)
  (cons 'uml:lambda (cons parameters body)))

;;; if conditionals

(define (if? exp) (tagged-list? exp 'uml:if))

(define (if-predicate exp) (cadr exp))

(define (if-consequent exp) (caddr exp))

(define (if-alternative exp)
  (if (not (null? (cdddr exp)))
      (cadddr exp)
      'false))

;;; constructor for if expressions, to be used for cond->if to 
;;; transform cond expressions into if expressions

(define (make-if predicate consequent alternative)
  (list 'uml:if predicate consequent alternative))

;;; Procedures to implement uml:and as a special form in our new language

(define (eval-and exp env)
  (define (iter clauses)
    (if (null? clauses)
	#t
	(if (false? (mc-eval (car clauses) env))
	    #f
	    (iter (cdr clauses)))))
  (iter (and-clauses exp)))

(define (and? exp) (tagged-list? exp 'uml:and))

(define (and-clauses exp) (cdr exp))

;;; Procedures to implement uml:or as a special form in our new language 

 (define (eval-or exp env) 
   (define (iter clauses)
    (if (null? clauses)
	#f
	(if (true? (mc-eval (car clauses) env))
	    #t
	    (iter (cdr clauses)))))
  (iter (and-clauses exp))) 
  
 (define (or? exp) (tagged-list? exp 'uml:or)) 
  
 (define (or-operands exp) (cdr exp))

;;; begin expressions (a.k.a. sequences)

(define (begin? exp) (tagged-list? exp 'uml:begin))

(define (begin-actions exp) (cdr exp))

(define (last-exp? seq) (null? (cdr seq)))

(define (first-exp seq) (car seq))

(define (rest-exps seq) (cdr seq))

;;; constructor sequence->exp for use by cond->if that transforms
;;; a sequence into a single expression, using begin if necessary

(define (sequence->exp seq)
  (cond ((null? seq) seq)
	((last-exp? seq) (first-exp seq))
	(else (make-begin seq))))

(define (make-begin seq) (cons 'uml:begin seq))

;;; procedure applications

(define (application? exp) (pair? exp))

(define (operator exp) (car exp))

(define (operands exp) (cdr exp))

(define (no-operands? args) (null? args))

(define (first-operand args) (car args))

(define (rest-operands args) (cdr args))

;;; cond conditionals: a derived expression

(define (cond? exp) (tagged-list? exp 'uml:cond))

(define (cond-clauses exp) (cdr exp))

(define (cond-else-clause? clause)
  (eq? (cond-predicate clause) 'uml:else))

(define (cond-predicate clause) (car clause))

(define (cond-actions clause) (cdr clause))

(define (cond->if exp)
  (expand-clauses (cond-clauses exp)))

(define (expand-clauses clauses)
  (if (null? clauses)
      'false
      (let ((first (car clauses))
	    (rest (cdr clauses)))
	(if (cond-else-clause? first)
	    (if (null? rest)
		(sequence->exp (cond-actions first))
		(error "ELSE clause isn't last -- COND->IF"
		       clauses))
	    (make-if (cond-predicate first)
		     (sequence->exp (cond-actions first))
		     (expand-clauses rest))))))

;;; Adding uml:let to the evaluator

(define (let? exp) (tagged-list? exp 'uml:let))

(define (let-variables exp)
    (map car (cadr exp)))

(define (let-values exp)
    (map cadr (cadr exp)))

(define (let-body exp)
    (cddr exp))

(define (let->combination exp)
    (let ((variables (let-variables exp))
          (values (let-values exp))
          (body (let-body exp)))
       (cons (cons 'uml:lambda (cons variables body))
             values)))

;;; Data structures for our evaluator

;;; for conditionals, we accept anything that isn't the explicit false
;;; object to be true

(define (true? x)
  (not (eq? x #f)))

(define (false? x)
  (eq? x #f))

;;; representing procedures

(define (make-procedure parameters body env)
  (list 'procedure parameters body env))

(def