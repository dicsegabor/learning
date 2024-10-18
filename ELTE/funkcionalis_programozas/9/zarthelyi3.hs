module Zarthelyi3 where

import Data.List (isInfixOf)

{- 
1. Azért mert a g fv d-t ad vissza és a h e-t vár.
 -}

squaredFirst :: [(a -> Int)] -> a -> Int
squaredFirst (f:xs) n = f n ^ 2

isBeef :: [String] -> Int
isBeef [] = 0
isBeef (x:xs)
    | isInfixOf "marha" x = 1 + isBeef xs
    | otherwise = isBeef xs

evenList :: Integral a => [[a]] -> [[a]]
evenList [] = []
evenList l = filter (even . sum) l