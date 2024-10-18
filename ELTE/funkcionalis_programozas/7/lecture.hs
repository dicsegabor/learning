module Lecture where

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

foldl' :: (a -> b -> b) -> b -> [a] -> b
foldl' _ def [] = def
foldl' f def (x:xs) = foldl' f (f x def) xs

iterate' :: (a -> a) -> a -> [a]
iterate' f a = a : iterate' f (f a)

all' :: (a -> Bool) -> [a] -> Bool
all' _ [] = False
all' f (x:xs) = f x && all' f xs


any' :: (a -> Bool) -> [a] -> Bool
any' _ [] = False
any' f (x:xs) = f x || any' f xs

makeRow :: [Int] -> [[Int]]
makeRow [] = [[]]
makeRow (x:xs) = row : makeRow row
    where
        row = 1 : zipWith (+) (x:xs) xs ++ [1]

pascalTriangle :: [[Int]]
pascalTriangle = [1] : makeRow [1]

compose:: (b->c) -> (a->b) -> a -> c
compose f g a = f (g a )

dollar :: (a -> b) -> a -> b
dollar f a = f a

-- Pointfree programozás: eldobjuk a lehető legjobb paramétert

a b c = b * c -- a = (*)
{- 
a b c = (*)b c
a b = (*) b 
a = (*)
 -}

group ::Eq a => [a] -> [[a]]
group [] = []
group l@(x:xs) = takeWhile (==x) l : group (dropWhile (==x) l)

compress:: Eq a => [a] -> [(Int, a)]
compress [] = []
compress l@(x:xs) = (length $ takeWhile (==x) l, x) : compress (dropWhile (==x) xs)

decompress :: [(Int, a)] -> [a]
decompress [] = []
decompress ((n, a):xs) = replicate n a ++ decompress xs
--decompress xs = concatMap (\(n, a) -> replicate n a) xs
