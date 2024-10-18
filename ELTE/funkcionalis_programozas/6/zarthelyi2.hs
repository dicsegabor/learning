module Zarthelyi where

{- 
1. (x:y) ez egy listához fűz egy elemt, x++y ez pedig két listát fűz össze
    (x:y) x<-a, y>-[a] | x++y x,y<-[a]
2. Az egyik egy mintaillesztés, a másik pedig egy guardban használható feltétel, ami a mintaillesztés után következik
 -}

keepWhereMiddleIsLargest :: Ord a => [(a,a,a)] -> [(a,a,a)]
keepWhereMiddleIsLargest [] = []
keepWhereMiddleIsLargest (t@(a,b,c):xs)
    | a < b && c < b = t : keepWhereMiddleIsLargest xs
    | otherwise = keepWhereMiddleIsLargest xs

deleteEveryThird :: [a] -> [a]
deleteEveryThird [] = []
deleteEveryThird l = take 2 l ++ deleteEveryThird (drop 3 l)

alternate :: [a] -> [a] -> [a]
alternate [] _ = []
alternate _ [] = []
alternate (x:xs) (y:ys) = x : alternate ys xs