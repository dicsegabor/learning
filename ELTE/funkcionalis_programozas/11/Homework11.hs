module Homework11 where

import Data.List (find, inits)

repeated :: Ord a => [a] -> [a]
repeated [] = []
repeated (x:xs)
    | Just a <- find (==x) xs = x : repeated [y | y<-xs, y /= x]
    | otherwise = repeated xs

-- Máshogy jött ki az algoritmus, elvileg jó, csak más sorrendet csinál
sublists :: [a] -> [[a]]
sublists [] = [[]]
sublists l@(x:xs) = filter (not . null) $ inits l ++ sublists xs

subListWithLength :: Int -> [a] -> [[a]]
subListWithLength _ [] = []
subListWithLength 0 _ = []
subListWithLength n l = filter ((==) n . length) (sublists l)

until' :: (a -> Bool) -> (a -> a) -> a -> a
until' p f x
    | p x = x
    | otherwise = until' p f (f x)