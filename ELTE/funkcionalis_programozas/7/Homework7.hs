module Homework7 where

{-
1. f . g x = f (g x)
2. f :: Int -> Int -> Int = f :: Int -> (Int -> Int)
3. Vagy fv-t kap paraméterül, vagy azt ad vissza
4. Azért, mert a map visszatérési éstékre nem [Int], hanem Int
 -}

spanWhile :: (a -> Bool) -> [a] -> ([a], [a])
spanWhile _ [] = ([], [])
spanWhile f l = (takeWhile f l, dropWhile f l)

pairwise :: (a -> a -> b) -> [a] -> [b]
pairwise _ [] = []
pairwise _ [x] = []
pairwise f (x : y : xs) = f x y : pairwise f (y : xs)

takeWhilePair :: (a -> a -> Bool) -> [a] -> [a]
takeWhilePair _ [] = []
takeWhilePair _ [x] = [x]
takeWhilePair f (x : y : xs)
  | f x y = x : takeWhilePair f (y : xs)
  | otherwise = [x]

dropWhilePair :: (a -> a -> Bool) -> [a] -> [a]
dropWhilePair _ [] = []
dropWhilePair _ [x] = []
dropWhilePair f l@(x : y : xs)
  | f x y = dropWhilePair f (y : xs)
  | otherwise = l

descendingSegments :: Ord a => [a] -> [[a]]
descendingSegments [] = []
descendingSegments l
  | null dw_l = [] -- list is in ascending order
  | otherwise = tw_g : next
  where
    dw_l = dropWhilePair (<=) l -- remove ascending elements
    tw_g = takeWhilePair (>) dw_l -- take descending elements
    dw_g = dropWhilePair (>) dw_l -- remove descending elements
    next = descendingSegments dw_g

