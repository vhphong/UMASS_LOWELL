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
        y-change (* y-velocity delta-time)]                                     ;same as y in the event of jumping
    (if (or (not= 0 x-change) (not= 0 y-change))                                ;if the change is anything, ie if the object is moving, then do these associations. this creates a new entity and returns it. NO MUTATING OF DATA
      (assoc entity                                                             ;assoc self explanatory, this has bindings of the entity called on and changes the new ones to reflect the new data.
             :x-velocity (u/decelerate x-velocity)                              ;
             :y-velocity (u/decelerate y-velocity)                              ;
             :x-change x-change                                                 ;
             :y-change y-change                                                 ;-------------------
             :x (+ x x-change)                                                  ;
             :y (+ y y-change)                                                  ;
             :can-jump? (if (> y-velocity 0) false can-jump?)
             :hitbox (rectangle (:x entity) 
                                (:y entity) 
                                (:width entity) 
                                (:height entity)))                  ;This is worth explaining; if the y-velocity is ANYTHING (ie, if there is vertical movement like jumping) can-jump? is false. no double jumping
      entity)))                                                                 ;else, just return the old entity.

(defn animate-zombie                                                                   ;animate function
  [screen {:keys [x-velocity y-velocity                                         ;parameters are the screen and a map of all of the entity's movement keys
                  stand-right stand-left                                        ;
                  jump-right jump-left                                          ;-------------------
                  walk-right walk-left] :as entity}]                            ;
  (let [direction (u/get-direction entity)]                                     ;using utility function to get the direction of the entity called on, binds it with direction at a local binding
    (merge entity                                                               ;merge is a map function. this will return a new map with new things based off of condition insert inside
           (cond                                                                ;
             (not= y-velocity 0)                                                ;if there is jumping, change to jump sprite.
             (if (= direction :right) jump-right jump-left)                     ;which jump sprite we change to is dependant on the direction.
             (not= x-velocity 0)                                                ;if there is x velocity, ie movement
             (if (= direction :right)                                           ;animate walk-right. if not, animate walk-left. animation->texture is a play-clj built-in.
               (animation->texture screen walk-right)                           ;
               (animation->texture screen walk-left))                           ;
             :else                                                              ;no movement? stand in the direction you're facing.
             (if (= direction :right) stand-right stand-left))                  ;
           {:direction direction})))                                            ;merge the direction with entity to finalize a new entity, and return it as per methodology of returning new maps of objects after new data

(defn prevent-move-zombie                                                              ;COLLISION. function only gone fully into when there is collision detected.
  [screen {:keys [x y x-change y-change] :as entity}]                           ;params are the screen, and a map of :keys (x/y/changes) as an entity
  (let [old-x (- x x-change)                                                    ;this "undos" any x change. all of these are values that aren't associated yet, but may be if there is collision
        old-y (- y y-change)                                                    ;and also the y change
        entity-x (assoc entity :y old-y)                                        ;making a new entity where there was no movement that occured.
        entity-y (assoc entity :x old-x)                                        ;this essentially keeps the player out of anything that causes collision
        up? (> y-change 0)]                                                     ;true if there is y velocity. aka, is this collision happening from under the object?
    (merge entity                                                               ;merging new hash/key values to new entity
           (when (u/get-touching-tile screen entity-x "walls")                  ;this is when the actual collision utility function is being called. "walls" is the .tmx layer of objects
             {:x-velocity 0 :x-change 0 :x old-x})                              ;gives all of the new values, undoing any attempted changes
           (when-let [tile (u/get-touching-tile screen entity-y "walls")]       ;same as above
             {:y-velocity 0 :y-change 0 :y old-y                                ;but with an additional condition
              :can-jump? (not up?) :to-destroy (when up? tile)}))))