;coins.clj for Enclojure by Michael Jannino
;UML OPL Fall 2014

(ns enclojure.coins
  (:require [play-clj.core :refer :all]
            [play-clj.g2d :refer :all]
            [enclojure.utils :as u]))

;Coin generator created by Michael Jannino
;
; Two different ways of making coins as of writing this. Not sure which to use.
;
;

(defn random-coins []                                                           ;Procedure that takes no parameters
  (let [x (+ 100 (rand-int 6000))                                               ;Local bindings with let, binding x a random place from the left of the stage to the end of the stage
        y (+ 100 (rand-int 312))]                                               ;and binding y to a random place within the reach of the player
    (assoc (texture "coin.png") :x x, :y y, :width 16, :height 16)))            ;and associating this returned entity with the texture of a coin, the x and y vals, and the size of a coin
   


(defn create-coin                                                               ;Defining a coin function
  [stay]                                                                        ;single "stay" sprite 
  (assoc stay                                                                   ;Associating key values for "stay"
         :stand stay                                                            ;instantiating stand with the one sprite
         :width 1                                                               ;height and width one pixel unit
         :height 1                                                              ;;
         :x (+ 50 (rand 6000))                                                  ;initial placing of the coin. random within bounds.
         :y (+ 25 (rand 300))                                                   ;-----------------------------
         :me? false                                                             ;primitive to identify whether or not an entity is the player
         ))                                                  

