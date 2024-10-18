module Lecture where

import Data.Text (replace)
import GHC.Arr (foldrElems)

deleteAll :: Eq a => a -> [a] -> [a]
deleteAll e = filter (e /=)

sumsOf :: Num a => [[a]] -> [a]
sumsOf [] = []
sumsOf l = map sum l

takeWhileAscending :: Ord a => [a] -> [a]
takeWhileAscending [] = []
takeWhileAscending [a] = [a]
takeWhileAscending (x : y : xs)
  | x < y = x : takeWhileAscending (y : xs)
  | otherwise = [x]

blend (x : xs) ys = x : blend ys xs
blend _ _ = []

intertwine :: (a -> c) -> (b -> c) -> [a] -> [b] -> [c]
intertwine f g l1 l2 = blend (map f l1) (map g l2)

replaceGivens :: Eq a => [a] -> a -> [a] -> [a]
replaceGivens _ _ [] = []
replaceGivens r tr (x : xs)
  | x == tr = r ++ replaceGivens r tr xs
  | otherwise = x : replaceGivens r tr xs

data Cabinet a = Cabinet String a deriving (Eq, Show)

passCode :: String -> Cabinet a -> Maybe a
passCode s1 (Cabinet s2 n)
    | s1 == s2 = Just n
    | otherwise = Nothing

deleteRepeated :: Eq a => [a] -> [a]
deleteRepeated [] = []
deleteRepeated [a] = [a]
deleteRepeated (x : y : xs)
  | x == y = x : deleteRepeated xs
  | otherwise = x : y : deleteRepeated xs

duplicatedWords :: String -> String
duplicatedWords s = unwords ( deleteRepeated (words s))