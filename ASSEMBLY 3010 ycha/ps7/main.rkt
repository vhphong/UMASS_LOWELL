#lang racket

;;+++++++++++++++ Auto Grader Code ++++++++++++++++++++++++++++++++++++++

;;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; ********************************************************************************************

;;; Exercise 1: Draw a simple inheritance diagram showing all the kinds of objects (classes) 
;;; defined in the adventure game system (game-plt4.ss), the inheritance relations between them, 
;;; and the methods defined for each class.

;;; Answer:
;; PUT YOUR DIAGRAM HERE OR
;; YOU CAN DRAW IN A PAPER AND ATTACH SCANNED COPY IN THE ASSIGNMENT

class: make-named-object (symbol name)
inherits from: none
methods: NAME(returns name symbol)

class: make-mobile-object (symbol name, object location)
inherits from: make-named-object
methods: PLACE (returns location object)
         INSTALL (asks location to install self)
         SET-PLACE (changes object location to be a new place)
         else inherits from: make-named object
         
class: make-thing (symbol name, object birthplace)
inherits from: make-mobile-object
methods: OWNER (returns owner)
         OWNABLE (returns ownable confirmation)
         OWNED (references owner to return true or false)
         SET-OWNER (sets new owner)
         else inherit from: make-mobile-object
         
         
class: make-place (symbol name)
inherits from: make-named-object
methods: THINGS (returns things)
         NEIGHBORS (returns a list of all the nearby locations that aren't the exit)
         EXITS (returns the nearest neighbor)
         NEIGHBOR-TOWARDS (tells us if there is anything in that direction)
         ADD-NEIGHBOR (set new place to neihbor-map if nothing exists there already)
         ACCEPT-PERSON?(tells us if it is okay to put new person into this location)
         ADD-THING (adds new-things to things list if it doesn't already exist there)
         DEL-THING (deletes thing from things list if the object exists there)
         else inherit from: make-named-object
         
class: make-person (symbol name, object place, number threshold)
inherits from: make-mobile-objects
methods: PERSON? (returns true when inquired about this person)
         POSSESSIONS (returns a list of the person's possessions)
         LIST-POSSESSIONS (displays a message informing us of the person's possessions)
         HAVE-FIT (displays a message regarding the person's mood)
         LOOK-AROUND (displays a message informing us of other objects in the room)
         TAKE (takes items if allowed)
         LOSE (loses item if allowed)
         MOVE (calls act if the random meets the threshold)
         ACT (moves to new place if threshold is met)
         MOVE-TO (explictly moves to new place) 
         GO (calls move to if direction is accessible)
         INSTALL (installs the new person into world)
         else inherit from: make-person
         
class: make-troll (symbol name, object place, number threshold)
inherits from: make-person
methods: ACT (check to see if other persons in same room and calls eat person if there is)
         EAT-PERSON (eats the person)
         else inherit from: make-person
;; ********************************************************************************************

;;; Exercise 2: Draw a simple map showing all the places created by evaluating world-plt4.ss, 
;;; and how they interconnect. You will probably find this map useful in dealing with the 
;;; rest of the problem set.

;;; Answer:
;;PUT YOUR DIAGRAM HERE
;; YOU CAN DRAW IN A PAPER AND ATTACH SCANNED COPY IN THE ASSIGNMENT
           
;; ********************************************************************************************

;;; Exercise 3: Suppose we evaluate the following expressions:
;;; (define pizza (make-thing 'pizza robot-lab)) 
;;; (ask pizza 'set-owner fredm) 
;;; At some point in the evaluation of the second expression, the expression
;;; (set! owner new-owner) 
;;; will be evaluated in some environment. Draw an environment diagram, showing the full structure 
;;; of pizza at the point where this expression is evaluated. Don't show the details of fredm or 
;;; robot-lab—just assume that fredm and robot-lab are names defined in the global environment 
;;; that point off to some objects that you draw as blobs.

;;; Answer:

;;PUT YOUR DIAGRAM HERE
;; YOU CAN DRAW IN A PAPER AND ATTACH SCANNED COPY IN THE ASSIGNMENT

;; ********************************************************************************************

;;; Exercise 4: Suppose that, in addition to pizza in Exercise 3, we define
;;; (define pepperoni-pizza (make-named-object 'pizza)) 
;;; Are pizza and pepperoni-pizza the same object (i.e., are they eq?)? If fredm wanders to a place 
;;; where they both are and looks around, what message will he print?
;;; Part 3—Main Assignment

;;; Solutions to these exercises should also be turned in with your solutions to the warm-up exercises.

;;; Answer:
;;PUT YOUR ANSWER HERE
         
No they are no the same object, if we ask fredm to look around, he will say that he sees pizza pizza because
there are two seperate discrete pizza objects in the world. 

;; ********************************************************************************************
             
;;; Exercise 5: We suggest that you do this exercise before you start coding the assignment, 
;;; because it illustrates a bug that is easy to fall into when working with the adventure game.
;;; Note how install is implemented as a method defined as part of both mobile-object and person. 
;;; Notice that the person version puts the person on the clock list (this makes them “animated”) 
;;; then invokes the mobile-object version on self, which makes the birthplace where self is being 
;;; installed aware that self thinks it is in that place. That is, it makes the self and birthplace 
;;; consistent in their belief of where self is. The relevant details of this situation are outlined 
;;; in the code excerpts below:

;(define (make-person name birthplace threshold)
;  (let ((mobile-obj (make-mobile-object name birthplace))
;        ...)
;    (lambda (message)
;      (cond ...
;            ...
;            ((eq? message 'install)
;             (lambda (self)
;               (add-to-clock-list self)
;               ((get-method mobile-obj 'install) self) ))   ; **
;                ...))))

;(define (make-mobile-object name place)
;  (let ((named-obj (make-named-object name)))
;    (lambda (message)
;      (cond ...
;            ...
;            ((eq? message 'install)
;             (lambda (self)
;               (ask place 'add-thing self)))
;               ...))))

;;; Louis Reasoner suggests that it would be simpler if we change the last line of the make-person 
;;; version of the install method to read:
; (ask mobile-obj 'install) )) ; ** 

;;; Alyssa P. Hacker points out that this would be a bug. “If you did that,” she says, “then when you 
;;; make&install-person fredm and fredm moves to a new place, she'll thereafter be in two places at once!
;;; The new place will claim that fredm is there, and fredm's place of birth will also claim that fredm is there.”

;;; What does Alyssa mean? Specifically, what goes wrong? You will likely need to draw an appropriate 
;;; environment diagram to explain carefully.

;;; Answer:

;;PUT YOUR ANSWER HERE
Get-method keeps you in the same frame of the install method and installs the make-person's self instance of fredm into robotics lab.
The ask procedure takes you out of the make-person scope and creates a seperate mobile-object self instance of fredm into robotics lab.  
When you call the ask procedure to install fredm, we create self mobile-object inside of robotics lab seperate from the make-person self 
for fredm.  When we move fredm out of the robotics lab, we have a person self moving into new place but not the mobile
object self.  So the two different fredms will exist in two different places.

;; ********************************************************************************************
             
;;; Exercise 6: We do not expect you to have to make significant changes in the game code, though you may do so if you want to.
;;; You have a world buffer. Since the simulation model works by data mutation, it is possible to get your 
;;; Scheme-simulated world into an inconsistent state while debugging. To help you avoid this problem, 
;;; we suggest the following discipline: any procedures you change or define should be placed in your answer file; 
;;; any new characters or objects you make and install should be added to world.
;;; This way, whenever you change some procedure you can make sure your world reflects these changes by simply 
;;; re-evaluating the entire world.rkt file.
;;; Finally, to save you from retyping the same scenarios repeatedly—for example, when debugging you may 
;;; want to create a new character, move it to some interesting place, then ask it to act—we suggest you 
;;; define little test “script” procedures at the end of the world buffer that you can invoke to act out 
;;; the scenarios when testing your code.
;;; See the comments in world for details. After loading the files, make fredm and swathi move around by 
;;; repeatedly evaluating (clock). (a) Which person is more restless? 
;;; (b) How often do both of them move at the same time?

;;; Answer:

;;PUT YOUR ANSWER HERE

The most restless person is swathi because his threshold number is the lowest.  The way that random works is that it generates a random
number in the range from 0 to the threshold, when the range is smaller the chances of getting zero are much higher.  The chances of
them moving at the same time is very random because the random number generates different numbers for both of them every clock call.

;; ********************************************************************************************

;;; Exercise 7: Implement student, a special kind of person. Define a procedure make-student that creates 
;;; the student object. It should inherit from person. A student has an instance variable, passed-opl, 
;;; that indicates whether or not the student has taken and passed OPL.
;;; Initally, all students have not passed OPL. A student has a method take-opl that changes the 
;;; state of passed-opl to #t. A student also has a method cheat-on-problem-set that changes the state 
;;; of passed-opl to #f. A student also has a method passed-opl? that evaluates to #t if the student has 
;;; passed OPL and #f otherwise.

;;; Answer:

;;PUT YOUR PROCEDURES HERE

(define (make-student name birthplace threshold)
  (let ((passed #f)
        (person (make-person name birthplace threshold)))
    (lambda (message)
      (cond ((eq? message 'take-opl)
             (lambda (self)
               (set! passed #t)
               'passed))
            ((eq? message 'cheat-on-problem-set)
             (lambda (self)
               (set! passed #f)
               'failed))
            ((eq? message 'passed-opl?)
             (lambda (self)
               passed))
            (else (get-method person message))))))

(define (make&install-student name birthplace threshold)
  (let ((student  (make-student name birthplace threshold)))
    (ask student 'install)
    student))

;; ********************************************************************************************

;;; Exercise 8: Make and install a new character of a student type, yourself, with a high enough threshold
;;; (say, 100) so that you have “free will” and are not likely to be moved by the clock.
;;; Place yourself initially in the computer-lab. Also make and install a thing called late-homework, 
;;; so that it starts in the computer-lab. Pick up the late-homework, find out where fredm is, go there, 
;;; and try to get fredm to take the homework even though he is notoriously adamant in his stand against 
;;; accepting tardy problem sets. Can you find a way to do this that does not leave you upset? Turn in a 
;;; list of your definitions and actions. If you wish, you can intersperse your moves with calls to the 
;;; clock to make things more interesting. (Watch out for grendel!)

;;; Answer:

;;PUT YOUR PROCEDURES AND PROCEDURE CALLS HERE
I commented out (ask owner 'have fit) from the TAKE function of make-person and ran these actions.

(define gunther (make&install-student 'gunther computer-lab 100))
(define late-homework 
  (make&install-thing 'late-homework  computer-lab))
(ask gunther 'take late-homework)
(ask gunther 'go 'south)
(ask fredm 'take late-homework)

;; ********************************************************************************************

;;; Exercise 9: Define a procedure make-advisor that makes a special kind of person. It should inherit 
;;; from a person but have an additional method: (ask 'advise Person). An advisor will enroll a student 
;;; in OPL if they are in the same place and the student has not yet passed OPL. When enrolled, the student
;;; is sent to the OPL classroom (you can do this with (ask Person 'move-to OPL)).

;;; Note that you'll need to create the OPL place in your world. It's up to you whether or not to make this
;;; a place from which one can exit.
;;; In addition, you should make the clock-tick method for an advisor automatically enroll any students who
;;; haven't passed OPL in the place where the advisor is. If no students are in the current location, the 
;;; advisor will act like a normal person; that is, it should invoke the super-class (person) clock-tick 
;;; method. You may find the other-people-at-place procedure (defined in game.ss) useful. Create and 
;;; install at least one advisor in your world in the elevator-lobby.

;;; Answer:

;;PUT YOUR PROCEDURE HERE

I created a condition in make-person for (eq? message student?) (lambda (self) false)
and a make-student (eq? message student?) (lambda (self) false)
and then I can put these definitions into place to make the advisor enroll students who
have no passed opl.

(define (make-advisor name birthplace threshold)
  (let ((person (make-person name birthplace threshold)))
    (lambda (message)
      (cond ((eq? message 'act)
             (lambda (self)
               (let ((others (other-people-at-place self (ask self 'place))))
                 (if (not (null? others))
                     (map (lambda (x) (ask self 'advise x)) 
                          (filter (lambda (t) (ask t 'student?)) others))
                     ((get-method person 'act) self)))))
            ((eq? message 'advise)
             (lambda (self person)
               (cond ((not(ask person 'passed-opl?))             
                      (ask self 'say
                    (list "Have fun in OPL "
                          (ask person 'name)))
               (go-to-opl person))
                     (else 
                      (ask self 'say 
                           (list "Have a nice day!"))))))
            (else (get-method person message))))))

(define (make&install-advisor name birthplace threshold)
  (let ((advisor  (make-advisor name birthplace threshold)))
    (ask advisor 'install)
    advisor))

(define (go-to-opl person)
  (for-each (lambda (item) (ask person 'lose item))
            (ask person 'possessions))
  (ask person 'say
       '("
                     I LIVE FOR OPL!"
         ))
  (ask person 'move-to opl)
  (remove-from-clock-list person)
  'OPL-for-you-dude)

;; ********************************************************************************************

;;; Exercise 10: Now you have the elements of a simple game that you play by interspersing your own moves with calls 
;;; to the clock. Your goal is to leave the computer-lab, gain access to the robot-lab, and return, without 
;;; being enrolled in OPL (start yourself off as not having passed OPL, as you're still in the course now).

;;; To make the game more interesting, you should also create some student(s) besides yourself and set up the student 
;;; act method so that a student will try to move around campus, collecting interesting things that they find 
;;; and occasionally leaving some of their possessions behind when they move on.
;;; Turn in your new student act method and a demonstration that it works.

;;; Answer:

;;PUT YOUR PROCEDURES HERE 
;;WRITE FEW SENTENCES WHAT YOU ARE TRYING TO DO HERE

This 'act method picks up items if the room has anything it and if he already has that item and act is called,
he will move around.  He should pick up an item if there is no item in the room already but I am having 
difficulties with checking to see what items he owns without outputting an entire phrase.  This definition will
work when implemented, but I would need to change the list-possessions method in order to get it to function
completely.  

insert cond ((eq? message 'person?) (lambda (self) false)) into make-thing definition

insert cond 
1((eq? message 'act)
 2            (lambda (self)
  3             (let ((stuff (filter 
   4                          (lambda (x) (not (ask x 'person?))) 
    5                         (ask (ask self 'place) 'things))))
     6          (if (not (empty? stuff))
      7             (if (not (equal? (ask (car stuff) 'owner) self))
       8                (ask self 'take (car stuff))
        9               ((get-method person 'act) self))
         10          (if (not (empty? (ask self 'list-possessions)))
           11            ;(if (= (random threshold 0))
             12              (ask self 'lose (caddr(ask self 'list-possessions)))
               13            ;((get-method person 'act) self))
                 14      ((get-method person 'act) self))))))  


;; ********************************************************************************************

;;; Required for Honor Students and Graduate Students; Extra Credit for Others

;;; Exercise 11: Design a non-trivial extension to this simulated world. You can do what you want (so long as it 
;;; is in good taste, of course). The extension can be as elaborate as you like, but don't go overboard; 
;;; this is meant to be a problem set, not a term paper, after all.
;;; Try to base your extended simulation around a theme. Possibilities include classes, labs, food, robots, etc. 
;;; Use your imagination!
;;; Whatever you choose to do, your simulation should include at least two new kinds of persons, places, or things, 
;;; using inheritance. For example, you might implement a classroom as a new kind of place. Your new objects should have 
;;; some special methods or special properties in relation to other objects. To continue the previous example, you might
;;; make new kinds of people called overworked-students, who go to sleep when they enter classrooms. In answering this 
;;; problem, you should turn in:

;;; ==> One or two paragraphs explaining the “story” behind your simulation. 
;;;     Describe your new objects and their behaviors.
;;; ==> An inheritance diagram showing your new classes.
;;; ==> Listings of any new procedures you write, or old procedures that you modify.
;;; ==> A transcript that shows your simulation in action.

;;; Note that it's more impressive to implement a simple, elegant idea, than to just amass tons of new objects and places.

;;; Answer:

;;PUT YOUR ANSWER HERE



;; **************************** END OF FILE ****************************************************
