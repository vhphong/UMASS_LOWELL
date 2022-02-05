-- UMass Lowell
-- Organization of Programming Languages (OPL)
-- by Phong Vo - Spring 2019
-- Assignment 1
-- reference link: https://rosettacode.org/wiki/Permutations#Haskell

module Main where
import Data.Char

permutations :: [a] -> [[a]]
permutations =
	foldr (\x ac -> ac >>= (fmap . ins x) <*> (enumFromTo 0 . length)) [[]]
	where
		ins x xs n =
		let (a, b) = splitAt n xs
		in a ++ x : b
 
main :: IO ()
main = print $ permutations[1, 2, 3]