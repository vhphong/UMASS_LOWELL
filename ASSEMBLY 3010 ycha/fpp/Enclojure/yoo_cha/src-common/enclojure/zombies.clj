(ns enclojure.zombies
  (:require [play-clj.core :refer :all]
            [play-clj.g2d :refer :all]
            [play-clj.math :refer :all]
            [enclojure.utils :as u]))

;;;;;;;;;zombies.clj by Yoo Min Cha; random zombie x by Michael Jannino

(defn create-zombie                                                                    ;Defining a create function
  [stand jump & walk]                                                           ;stand jump & walk, walk is dotted-tail (can be multiple args) 
  (assoc stand                                                                  ;Associating key values for "stand"
         :stand-right stand                                                     ;stand-right will be the default texture
         :stand-left (texture stand :flip true false)                           ;stand-left uses :flip, a play-clj method. true for horizontal flip and false for vertical. this means it faces backwards but not upside down
         :jump-right jump                                                       ;jump-right uses the jump sprite passed to this function
         :jump-left (texture jump :flip true false)                             ;jump-left uses the same primitive, :flip, in the same way
         :walk-right (animation u/duration                                      ;walk-right is a key value that starts an animation. /utilities/duration is the length of the animation
                                walk                                            ;walk is the list of all of the walking sprites. this is taking advantage of dotted tail and can add for all types of walking animations. cool!
                                :set-play-mode (play-mode :loop-pingpong))      ;ping-pong is a looping mechanism that loops to the end and then loops back. natural walking loop
         :walk-left (animation u/duration                                       ;walk left is all of the prior but mapping the flip function to each walk sprite
                               (map #(texture % :flip true false) walk)         ;this flips the whole animation
                               :set-play-mode (play-mode :loop-pingpong))       ;but keeps the ping-pong looping mechanism
         :width 1                                                               ;index of sprite
         :height (/ 26 18)                                                      ;
         :x-velocity 0                                                          ;init velocity to 0, not moving
         :y-velocity 0                                                          ;
         :x (+ 25 (rand-int 150))                                                ;random zombie pack
         :y 25                                                                  ;-----------------------------
         :attack-time 0
         :id false
         :npc? true                                                             ;primitive introduced here to identify whether or not an entity is the player
         :can-jump? false                                                       ;this initializes it to false because the player spawns in the air. when the player collides with the ground, he can jump.
         :direction :left)) 

(defn move-zombie                                                                      ;zombie move function
  [{:keys [delta-time]} {:keys [x y can-jump?] :as entity}]                     ;Parameters are hash maps. param 1 establishes delta-time, param 2 gets x, y and can-jump? keys from the entity this proc returned is called on
  (let [x-velocity (u/get-x-velocity entity)                                    ;Local bindings with let. x-velocity is using get-x-velocity from the entity being called on
        y-velocity (+ (u/get-y-velocity entity) u/gravity)                      ;getting y-velocity as well
        x-change (* x-velocity delta-time)                                      ;establishing the new change as the velocity times delta-time. this is an easing movement based on time. makes the movement much smoother and less jerky.
