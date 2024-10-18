module Homework4 where

mulAll :: Num a => [a] -> a
mulAll [] = 1
mulAll [a] = a
mulAll (x : xs) = x * mulAll xs

zipLists :: [a] -> [b] -> [(a, b)]
zipLists [] _ = []
zipLists _ [] = []
zipLists (x : xs) (y : ys) = (x, y) : zipLists xs ys

concatList :: [[a]] -> [a]
concatList [] = []
concatList (x : xs) = x ++ concatList xs

doublingFrom :: Num a => a -> [a]
doublingFrom a = a : doublingFrom (2 * a)

onlyIncreasing :: Ord a => [(a, a, a)] -> [(a, a, a)]
onlyIncreasing [] = []
onlyIncreasing ((a, b, c) : xs)
  | a < b && b < c = (a, b, c) : onlyIncreasing xs
  | otherwise = onlyIncreasing xs

takeN :: Int -> [a] -> [a]
takeN _ [] = []
takeN n (x : xs)
  | n <= 0 = []
  | otherwise = x : takeN (n - 1) xs

dropN :: Int -> [a] -> [a]
dropN _ [] = []
dropN n l@(x : xs)
  | n < 0 = []
  | n == 0 = l
  | otherwise = dropN (n - 1) xs

triUnzip :: [(a, b, c)] -> ([a], [b], [c])
triUnzip [] = ([], [], [])
triUnzip ((a, b, c) : xs) = (a : a2, b : b2, c : c2)
  where
    (a2, b2, c2) = triUnzip xs

indexList :: [a] -> [(Int, a)]
indexList [] = []
indexList [a] = [(0, a)]
indexList (x : xs) = (n + 1, x) : l
  where
    l@((n, a) : list) = indexList xs