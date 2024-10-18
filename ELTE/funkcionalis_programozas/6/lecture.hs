module Lecture where

select :: (a -> b) -> [a] -> [b]
select _ [] = []
select f (x : xs) = f x : select f xs

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f (x : xs)
  | f x = x : filter' f xs
  | otherwise = filter' f xs

countProperty :: (a -> Bool) -> [a] -> Int
countProperty _ [] = 0
countProperty f (x : xs)
  | f x = 1 + countProperty f xs
  | otherwise = countProperty f xs


sumVia :: Num b => (a->b) -> [a] -> b
sumVia _ [] = 0
sumVia f (x:xs) = f x + sumVia f xs

zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' _ _ [] = []
zipWith' _ [] _ = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' _ [] = []
dropWhile' f l@(x:xs)
    | f x = dropWhile' f xs
    | otherwise = l

takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' _ [] = []
takeWhile' f (x:xs)
    | f x = x : takeWhile' f xs
    | otherwise = []

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ def [] = def
foldr' f def (x:xs) = foldr' f (f x def) xs
