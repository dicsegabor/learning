module ZH where

import Data.Function (on)
import Data.List (elemIndex, findIndex, maximumBy, minimumBy, nub, sort)

mapSplit :: (a -> (b, c)) -> [a] -> ([b], [c])
mapSplit _ [] = ([], [])
mapSplit f (x : xs) = (a : c, b : d)
  where
    (a, b) = f x
    (c, d) = mapSplit f xs

applyUntil :: a -> (a -> a) -> (a -> Bool) -> [a]
applyUntil x f p
  | p x = x : applyUntil (f x) f p
  | otherwise = [x]

apexes :: Ord a => [a] -> [a]
apexes [] = []
apexes l = x : [y | y <- xs, not $ null $ takeWhile (< y) cl]
  where
    cl@(x : xs) = nub l

maxDivisorsUntil :: Integer -> Integer
maxDivisorsUntil n = maximumBy (compare `on` countDivisors) [1 .. n]
    where
        countDivisors n = foldr (\x -> (+) 1) 0 [y | y <- [1 .. n], mod n y == 0]

elemIndex' :: Eq a => a -> [a] -> Int
elemIndex' _ [] = 0
elemIndex' a l
  | Just i <- elemIndex a l = 1 + i
  | otherwise = 0

maxIndices :: Ord a => [a] -> [Int]
maxIndices [] = []
maxIndices l = map (\x -> elemIndex' x (sort l)) l

maxIndex :: Ord a => [a] -> Int
maxIndex [] = error "Empty list has no max."
maxIndex l
  | Just i <- elemIndex (maximum l) l = 1 + i
  | otherwise = error "There is no max."

closestToOrigo :: Real a => [(a, a)] -> (a, a)
closestToOrigo = minimumBy (compare `on` (\(a,b) -> a ^ 2 + b ^ 2))