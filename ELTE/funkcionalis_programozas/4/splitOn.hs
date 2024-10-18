module SplitOn where

splitOn :: Eq a => a -> [a] -> [[a]]
splitOn _ [] = [[]]
splitOn c [x]
  | c == x = [[], []]
  | otherwise = [[x]]
splitOn c l@(x : xs)
  | c == x = rec
  | length xs > length (head rec) = [x] : rec
  | otherwise = (x : head rec ) : tail rec
  where
    rec = splitOn c l