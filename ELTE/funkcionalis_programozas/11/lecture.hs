module Lecture where

sum' :: Num a => [a] -> a
sum' [] = 0
sum' (x : xs) = x + sum' xs

product' :: Num a => [a] -> a
product' [] = 1
product' (x : xs) = x * sum' xs

elem' :: Eq a => a -> [a] -> Bool
elem' _ [] = False
elem' e (x : xs) = x == e || elem' e xs

length' :: [a] -> Int
length' [] = 0
length' (x : xs) = 1 + length' xs

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ def [] = def
foldr' f def (x:xs) = foldr' f (f x def) xs

composeAll :: [a -> a] -> (a -> a)
composeAll = foldl (.) id

maximum' :: Ord a => a -> [a] -> a
maximum' = foldr max

minimum' :: Ord a => a -> [a] -> a
minimum' = foldr min

mySpecialFunction :: Num a => [a] -> a
mySpecialFunction = foldr (\a acc -> (a ^ 2) - acc) 0