(ns enclojure.core.desktop-launcher
  (:require [enclojure.core :refer :all])
  (:import [com.badlogic.gdx.backends.lwjgl LwjglApplication]
           [org.lwjgl.input Keyboard])
  (:gen-class))

(defn -main
  []
  (LwjglApplication. enclojure "Enclojure" 800 600)
  (Keyboard/enableRepeatEvents true))