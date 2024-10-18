module Homework8 where

import Data.List (find)
import Data.Maybe (isNothing)

data Flower = Sunflower | Dandelion | Poppy

instance Show Flower where
  show Sunflower = "Napraforgó"
  show Dandelion = "Pitypang"
  show Poppy = "Pipacs"

data Metroline = MOne String Int | MTwo String Int | MThree String Int | MFour String Int

data Singleton t = One t deriving (Eq)

safeMin :: Ord a => [a] -> Maybe a
safeMin [] = Nothing
safeMin (x : xs)
  | isNothing next || Just x < next = Just x
  | otherwise = next
  where
    next = safeMin xs

composeMaybe :: a -> (a -> Maybe b) -> (b -> Maybe c) -> Maybe c
composeMaybe x f g
  | Just b <- f x = g b
  | otherwise = Nothing

safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead l = Just $ head l

unorderedEq :: Eq a => [a] -> [a] -> Bool
unorderedEq [] _ = False
unorderedEq _ [] = False
unorderedEq [a] [b] = a == b
unorderedEq (x : xs) l2
  | Just a <- find (== x) l2 = unorderedEq xs (deleteFirstMatch x l2)
  | otherwise = False
    where
      deleteFirstMatch e l = takeWhile (/=e) l ++ tail (dropWhile (/=e) l)

minimumBy :: Ord b => (a -> b) -> [a] -> a
minimumBy _ [] = error "Empty list has no min value."
minimumBy _ [a] = a
minimumBy f (x : xs)
  | f x < f next = x
  | otherwise = next
  where
    next = minimumBy f xs

powerSet :: [a] -> [[a]]
powerSet [] = [[]]
powerSet (x:xs) = powerSet xs ++ map (x:) (powerSet xs)