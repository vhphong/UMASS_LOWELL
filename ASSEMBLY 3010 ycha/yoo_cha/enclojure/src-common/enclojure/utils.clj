(ns enclojure.utils
  (:require [play-clj.core :refer :all]))

(def ^:const vertical-tiles 20)
(def ^:const pixels-per-tile 16)
(def ^:const duration 0.15)
(def ^:const damping 0.5)
(def ^:const max-velocity 13)
(def ^:const max-velocity-npc 1)
(def ^:const max-jump-velocity (* max-velocity 4))
(def ^:const deceleration 0.9)
(def ^:const gravity -1)

(defn decelerate																				                        ;decelerate takes in velocity as an argument 
  [velocity]																					                          ;		
  (let [velocity (* velocity deceleration)]											          			;creates a local binding and scales velocity based on the deceleration
    (if (< (Math/abs velocity) damping)											            				;if the absolute value of velocity is less than damping..
      0																						                            	;we return 0
      velocity)))																		                        		;or else we return the scaled value of velocity. this creates "easing", smooth movement horizontally and gravity vertically


;touched? defined from starter code, written by oakes. This is mobile support, we didn't really feel the need to remove it as it made testing easier physically

(defn touched?																				                         	;touched controls player movements based on where we click or touch on the screen
  [key]																							                            ;has one argument key
  (and (game :touched?)																	                    		;registers if the screen been touched? and in which direction
       (case key																			                        	;
         :down (< (game :y) (/ (game :height) 3))											        	;registers if the screen is touched below 1/3 of its height
         :up (> (game :y) (* (game :height) (/ 2 3)))										       	;registers if the screen has been touched above 2/3 of its height
         :left (< (game :x) (/ (game :width) 3))												        ;registers if the screen has been touched on the left third of the screen
         :right (> (game :x) (* (game :width) (/ 2 3)))										              	;registers if the screen has been touched on the right third of the screen
         :center (and (< (/ (game :width) 3) (game :x) (* (game :width) (/ 2 3)))			  	;registers the center button at the middle horizontal 1/3 to 2/3 portion of screen
                      (< (/ (game :height) 3) (game :y) (* (game :height) (/ 2 3))))			;registers if the center button is in the vertical mid 1/3 to 2/3 portion of screen
         false)))


;;x-velocity function, with user input and NPC random movement by Yoo Min Cha and Michael Jannino
;;
;;

(defn get-x-velocity																			                      ;this function tells us which x-direction our object is heading
  [{:keys [me? npc? x-velocity]}]														                 		;takes in as its argument a hash map with keys as the key and a vector of its me? boolean value and x-velocity as its mapped value
  (cond 
    me?																					                              	;if me? is true..
    (cond																						                            ;we check these conditions..
      (or (key-pressed? :dpad-left) (touched? :left))				       							;if the left direction key has been pressed or touched left..
      (* -1 max-velocity)																	                    	;we return max-velocity in the negative x direction
      (or (key-pressed? :dpad-right) (touched? :right))			    								;if the right direction key has been pressed or touched right..
      max-velocity																			                       	;we return max-velocity in the positive x direction
      :else																					                          	;the last else condition..
      x-velocity)																				                        ;we simply return the current x-velocity
    npc?
    (if (> 5 (rand 100))
      (if (< 5 (rand 10))
        (* max-velocity-npc (- (rand-int 10)))
        ;else
        (* max-velocity-npc (rand-int 10)))
      0)
     :else x-velocity))																		                   		;if not me? we return the current x-velocity

;Get-y-velocity by Yoo Min Cha

(defn get-y-velocity																		                       	;this function tells us which y-direction our object is heading
  [{:keys [me? y-velocity can-jump?]}]							             								;takes in as its argument a hash mapping with keys as the key, and it is mapped to a vector containing the me? boolean value and the y-velocity
  (if me?																					                            	;if me? is true..
    (cond																					                            	;we test the conditions..
      (and can-jump? (or (key-pressed? :dpad-up) (touched? :up)))								;is can-jump? true, and has the right directional key been pressed or touched right?
      max-jump-velocity															                     				;return the max-jump-velocity
      :else																					                          	;else..
      y-velocity)																	                        			;return the current y-velocity
    y-velocity))																		                         		;if object is not me? return the objects current y-velocity

;Direction getter by Yoo Min Cha

(defn get-direction																	                      			;this function returns the directon we are moving in
  [{:keys [x-velocity direction]}]									                        		;takes in as its argument as hash mapping of :keys to a vector containing the x-velocity and direction
  (cond																					                             		;we check these conditions..
    (> x-velocity 0) :right														                  				;if positive x-velocity we return right
    (< x-velocity 0) :left															                  			;if negative x-velocity we return left
    :else																					                            	;else..
    direction))																		                        			; we return its existing direction

(defn get-touching-tile																		                    	;this function reacts to collision
  [screen {:keys [x y width height]} & layer-names]									      			;takes as input the hash mapping of the x and y coordinates and the width and height of the character and the layers around him
  (let [layers (map #(tiled-map-layer screen %) layer-names)]					  				;creates a local binding of all the mapped tiled-map-layer screen objects to all the layers in layer-names
    (->> (for [tile-x (range (int x) (+ x width))										        		;from the first x tile to the last
               tile-y (range (int y) (+ y height))]									      			;from the first y tile to the last
           (some #(when (tiled-map-cell % tile-x tile-y)							    			;return on the non nil items from layers that are colliding with the object
                    [tile-x tile-y])												              			;				
                 layers))															                    			;return the first item from the resulting list
         (drop-while nil?)														                   				;
         first)))														                        						;




