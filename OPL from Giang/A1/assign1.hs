{-# LANGUAGE ScopedTypeVariables #-}

-- | This is an explanation of a combination function written in Haskell
-- from http://rosettacode.org/wiki/Combinations#Dynamic_Programming_2

module Main where
import Data.Char

-- | Adds a @a@ to the beginning of every list inside the list of lists.
-- However, if the list of lists is just an empty list, return an empty
-- list.
--
-- >>> append 3 []
-- []
-- >>> append 3 [[1]]
-- [[3,1]]
-- >>> append 3 [[], [1], [4,5,6]]
-- [[3], [3,1], [3,4,5,6]]
--
append :: forall a . a     -- ^ element to add
                  -> [[a]] -- ^ list to list of @a@ to add element to
                  -> [[a]] -- ^ resulting list of list
append x partial_accum = map append_x partial_accum
  where
    append_x :: [a] -> [a]
    append_x list = x : list

-- | Prepend the element @a@ to every sub-sub list (which would be a list
-- that is two lists deep).  Don't do anything to elements that are just
-- list-of-lists.
--
-- Also prepends an empty list to the beginning.
--
-- >>> g 0 []
-- [[]]
-- >>> g 0 [[]]
-- [[],[]]
-- >>> g 0 [[[]]]
-- [[],[[0]]]
-- >>> g 0 [[[1,2,3]]]
-- [[],[[0,1,2,3]]]
-- >>> g 0 [[[1,2,3],[4,5,6]],[[7,8,9]],[]]
-- [[],[[0,1,2,3],[0,4,5,6]],[[0,7,8,9]],[]]
g :: forall a . a -> [[[a]]] -> [[[a]]]
g x accum = map helper accum_with_empty_list
  where
    -- Return our accumulator with an empty list appended on the
    -- front.
    accum_with_empty_list :: [[[a]]]
    accum_with_empty_list = [] : accum

    -- | Prepend the element @a@ to all sublists in @[[a]]@.
    --
    -- >>> helper [[1,2,3,4], [5,6], [7,8,9], []]
    -- [[0,1,2,3,4], [0,5,6], [0,7,8,9], [0]] -- where @x@ is 0
    helper :: [[a]] -> [[a]]
    helper acc = append x acc


f :: a -> [[[a]]] -> [[[a]]]
f x accum = zipWith (++) (g x accum) accum

-- | This produces a list of list of lists.  The first element is a list
-- containing an empty list, and all subsequent elements are empty lists.
--
-- >>> head double_empty_list_plus_infinite_empty
-- [[]]
-- >>> tail double_empty_list_plus_infinite_empty
-- [[], [], [], [], ...]
-- >>> take 5 double_empty_list_plus_infinite_empty
-- [[[]], [], [], [], []]
--
double_empty_list_plus_infinite_empty :: [[[a]]]
double_empty_list_plus_infinite_empty = [[]] : [] : [] : [] : repeat []

combBySize :: [a] -> [[[a]]]
combBySize list = foldr f double_empty_list_plus_infinite_empty list

-- | This is our new combining function (that hopefully will be easier to
-- understand...).
comb :: Int -> [a] -> [[a]]
comb m xs = combBySize xs !! m

-- | This is the original combining function.
comb' :: Int -> [a] -> [[a]]
comb' m xs = combsBySize' xs !! m
  where
    combsBySize' = foldr f' ([[]] : repeat [])
    f' x next = zipWith (++) (map (map (x:)) ([]:next)) next

main :: IO ()
main = do
    putStrLn "Enter a value for N: "
    n <- getLine
    putStrLn "Enter a value for K: "
    k <- getLine
    let nInput = read n :: Int
        kInput = read k :: Int
    print $ comb nInput [1..kInput]
