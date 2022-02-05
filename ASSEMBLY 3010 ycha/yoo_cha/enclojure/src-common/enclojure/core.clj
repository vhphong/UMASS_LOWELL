;core.clj for Enclojure by Yoo Min Cha and Michael Jannino
;UML OPL Fall 2014
;Sources and start code will be linked to within the documents in our project
;Credit for inspiration and starter code to play-clj documentation and reddit.com/r/playclj
;
;Documentation link: http://oakes.github.io/play-clj/
;
;Subreddit link: http://www.reddit.com/r/playclj
;
;As a preface to this project, we will explain the usage of "entities" and how the world works
;Entities is a vector/sequence that contains all of the objects to be displayed through the libGDX wrapper
;Nearly all functions return anonymous functions that operate on entities and these functions return a new sequence
;State is never mutated, only fed through and re-generated as per functional programming paradigm
;Functions we wrote ourselves 100% are documented and attributed by name throughout the files
;
;Functions specifically written by us in core.clj:
;Michael Jannino: for-loop macro, main-screen body augmentation, death-screen, win-screen, win-move, and all art for the .tmx file along with fredm.png.
;Yoo Min Cha: zombie art and interface with zombies.clj
;
;core.clj documentation by Michael Jannino

(ns enclojure.core
  (:require [play-clj.core :refer :all]                                   
            [play-clj.g2d :refer :all]
            [play-clj.ui :refer :all]                                           ;Inclusion of core files and our own seperate files
            [play-clj.math :refer :all]
            [enclojure.coins :as coins]
            [enclojure.zombies :as zomb]
            [enclojure.entities :as ents]
            [enclojure.utils :as utils]))

                                                                                ;For loop shorthand macro written by Michael Jannino for use throughout project

(defmacro for-loop [[i init check change :as params] & steps]                   ;Symbol to be bound, initial value, check case, and change over time. Dotted tail & used
 `(loop [~i ~init value# nil]                                                   ;Using clojures loop and recur constructs as per clojure documentation
    (if ~check
      (let [new-value# (do ~@steps)]
        (recur ~change new-value#))
      value#)))

                                                                                ;This line declares the game space "enclojure" and tells clojure what 
                                                                                ;functions will exist. Sort of like a header file

(declare enclojure main-screen text-screen death-screen win-screen death win-move collide)   


;update-screen! is a helper function made with the help of YouTube video "Game Development in Clojure with play-clj" 
;That is found here https://www.youtube.com/watch?v=9ilUe7Re-RA

(defn update-screen!                                                            ;Define function update-screen
  [screen entities]                                                             ;Arguments are the screen and the entities to manipulate
  (doseq [{:keys [x y height me? to-destroy]} entities]                         ;Doseq getting around the need for a vector/sequence to be returned. Returns nil. (Like for..in only no returned sequence)
    (when me?  
      (position! screen x (/ utils/vertical-tiles 2))                           ;Update the screen's x based on player position (keeping player in the center). 
                                                                                ;Dividing the utilities verticle tilespace by 2 keeps a constant y value/centering
      (when (< y (- height))
        (set-screen! enclojure death-screen)))                                  ;This is the "death". Resets game when you fall off (y is less than -height).
    (when-let [[tile-x tile-y] to-destroy]                                      ;When-let, clojure--conditional binding. If body is true, make this binding. Aka, when this is true destroy in this context
      (tiled-map-layer! (tiled-map-layer screen "walls")                        ;Tiled-map-layer returns true if the tiled-map-layer call is successful. This "gets" the layer "walls" from .tmx file
                        :set-cell tile-x tile-y nil)))                          ;...And this sets the walls layer where we are (no z value because this is 2D space).
  (map #(dissoc % :to-destroy) entities))                                       ;After the doseq, take away all the to-destroy associtions to the entities 


;defscreen is a built in from documentation. This is the only way to generate environments. It returns an anonymous function that takes a screen and entities
;set-screen!, a built in function from the documentation, runs through this entire environment and displays it to the active screen.

(defscreen main-screen
  :on-show                                                                      ;main-screen show
  (fn [screen entities]                                                         ;fn is lambda, this will return a function called on screen and entities
    (->> (orthogonal-tiled-map "level1.tmx" (/ 1 utils/pixels-per-tile))        ;thrush through map with the screen update/renderer. Thrush is kind of like foldr, and continues like that until the first element
         (update! screen :timeline [] :camera (orthographic) :renderer))        ;Uses a .tmx file and built-in interpreter to place it block by block as objects
    (let [sheet (texture "fredm.png")                                           ;character
          enemysheet (texture "zombie.png")                                     ;Loading the zombie sheet
          tiles (texture! sheet :split 18 26)                                   ;Splitting the sheet into squares of this size
          enemytiles (texture! enemysheet :split 18 26)
          zombie-images (for [col [0 1 2 3 4]]
                          (texture (aget enemytiles 0 col)))
          player-images (for [col [0 1 2 3 4]]                                  ;Each square gets put into a sequence of "player-images"
                          (texture (aget tiles 0 col)))]                        ;The actual texture getting in the body of the for
      [(apply zomb/create-zombie zombie-images)
      (apply zomb/create-zombie zombie-images)
      (apply zomb/create-zombie zombie-images)
      (apply zomb/create-zombie zombie-images)
      (apply zomb/create-zombie zombie-images)                                  ;Generating some enemies!!
      (apply zomb/create-zombie zombie-images)
      (apply zomb/create-zombie zombie-images)
      (apply ents/create-player player-images)]))                               ;And the player.
  
  :on-render                                                                    ;main-screen render
  (fn [screen entities]                                                         ;lambda just like the first one called on screen and entitites
    (clear! 0 0 0 1)                                                            ;clear! provides a color to a place with no entity. essentially a background color. R G B Alpha
    (some->> (if (or (key-pressed? :space) (utils/touched? :center))            ;someThrush; this is a little complex. This animates/renders the screen in reverse. By the nature
               (rewind! screen 2)                                               ;of the entire wrapper of the library, every frame is kept in a sequence because every function returns
               (map (fn [entity]                                                ;new sequences due to the nature of functional programming. This lets us walk backwards through
                      (->> entity                                               ;the entirety of sequences that have existed. This is basically time travel.
                        (ents/move screen)                                 
                        (ents/prevent-move screen)
                        (win-move screen)                                       ;thrush these updates through all entities
                        ;(death entities)
                        (ents/animate screen) 
                        (zomb/move-zombie screen)
                        (zomb/prevent-move-zombie screen)
                        (zomb/animate-zombie screen)))                          ;----------------
                    entities))
             (render! screen)                                                   ;calls render! on screen. This updates all entities in this scope. Built in from documentation
             (update-screen! screen)))                                          ;This updates the actual map after a render.
  
  :on-resize                                                                    ;This subroutine prevents stretching when a user resizes the window.
  (fn [{:keys [width height] :as screen} entities]                              ;It keeps track of the width and height and makes sure that the tiles/textures stay the same proportion
    (height! screen utils/vertical-tiles)))                                     ;This was found in a prebuilt minecraft 2d clone on github
                                                                                ;https://github.com/oakes/play-clj-examples/blob/master/minicraft/desktop/src-common/minicraft/core.clj

(defscreen text-screen                                                          ;Defines a "screen". This is the display with the text entities.
  :on-show                                                                      ;What happens when the screen first shows (init screen etc)
  (fn [screen entities]                                                         ;Returns lambda on screen and entities. 
    (update! screen :camera (orthographic) :renderer (stage))                   ;This makes a new screen map with the var screen, camera, and the stage. Functional FPS
    (assoc (label "0" (color :white))                                           ;Returns a new, updated version of entities with label "0" (background)
           :id :fps                                                       
           :x 5))                                                         
  
  :on-render                                                                    ;This is what happens during every frame per second. Render operates ~60fps for this case 
  (fn [screen entities]                                                         ;Returns lambda on screen and entities
    (->> (for [entity entities]                                                 ;Thrushes through, making bindings with for. "For each thing, bind it with a thing when this is true"
           (case (:id entity)                                                   ;So, this gets the fps and binds it to an entity so we can print it to the screen. 
             :fps (doto entity (label! :set-text (str (game :fps))))            ;
             entity))                                                           ;essentially setting a text entity and rendering it to the screen with render!
         (render! screen)))                                                     ;
  
  :on-resize                                                                    ;Same resize routine only optimized for the text in the bottom left. keeps the size the same.
  (fn [screen entities]                                                         
    (height! screen 300)))                                                      

;Death screen by Michael Jannino

(defscreen death-screen
  :on-show
  (fn [screen entities]
    (update! screen :camera (orthographic) :renderer (stage))                   ;Printing background image and placing another button on the screen
    (let [background (texture "FAILURE.png")                                    ;Actual button click functionality tough to implement
          button (assoc (texture "okay.png") :x 400 :y 80)]
      [background button]))
  
  :on-render
  (fn [screen entities]
    (clear!)
    (render! screen entities))
  
  
  :on-key-down
  (fn [screen entities]
    (cond                                                                       ;When you press enter, restart the game
     (key-pressed? :enter)
     (on-gl (set-screen! enclojure main-screen text-screen))))


  :on-resize
  (fn [screen entities]
    (height! screen 600)))


;;;Win screen by Michael Jannino, clone of death-screen with different image but same functionality. 


(defscreen win-screen
  :on-show
  (fn [screen entities]
    (update! screen :camera (orthographic) :renderer (stage))         
    (let [background (texture "SUCCESS.png")
          button (assoc (texture "okay.png") :x 400 :y 80)]
      [background button]))
  
  :on-render
  (fn [screen entities]
    (clear!)
    (render! screen entities))
  
  :on-key-down
  (fn [screen entities]
    (cond                                                               
     (key-pressed? :enter)
     (on-gl (set-screen! enclojure main-screen text-screen))))

  :on-resize
  (fn [screen entities]
    (height! screen 600)))

;;; Death condition by Yoo Min Cha

(defn death
  [entities]   
  (if-let [zombie (filter #(contains? % :npc?) entities)]
    (let [player (some #(when (:me? %) %) entities)
          touch-zombie (filter #(rectangle! (:hitbox player) :overlaps (:hitbox %)) zombie)]
      (if (touch-zombie) 
        (set-screen! enclojure death-screen)
        entities)
    entities))
    

;;;;Win condition by Michael Jannino

(defn win-move                                                      
  [screen {:keys [x y x-change y-change] :as entity}]                        
  (let [old-x (- x x-change)                                               
        old-y (- y y-change)                                           
        entity-x (assoc entity :y old-y)                                        ;This is collision inspired from other collision examples but a little different; instead of updating
        entity-y (assoc entity :x old-x)                                        ;the game state I destroy the current list of entities and override the screen.
        up? (> y-change 0)]                                                 
    (merge entity                                                         
           (when (utils/get-touching-tile screen entity-x "flag")             
             (set-screen! enclojure win-screen)                             
           (when-let [tile (utils/get-touching-tile screen entity-y "flag")]     
             (set-screen! enclojure win-screen))))))  




(defgame enclojure                                                              ;The final driver code. Initializing using main-screen and text-screen functions, overlaying them
  :on-create                                                            
  (fn [this]                                                            
    (set-screen! this main-screen text-screen)))                        

