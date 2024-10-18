module LECTURE where

fib :: Int -> Int
fib 0 = 1
fib 1 = 1
fib a = fib (a - 1) + fib (a - 2)

sum' :: Num a => [a] -> a
sum' [] = 0
sum' (x : xs) = sum' xs + x

repeat' :: a -> [a]
repeat' x = x : repeat' x

length' :: [a] -> Int
length' [] = 0
length' (x : xs) = 1 + length' xs

duplicate :: [a] -> [a]
duplicate [] = []
duplicate (x : xs) = x : (x : duplicate xs)

growing :: Int -> [Int]
growing a = a : growing (a + 1)

makeEven :: Int -> Int
makeEven x
  | mod x 2 == 0 = x
  | otherwise = x + 1

removeEmpties :: [[a]] -> [[a]]
removeEmpties [] = []
removeEmpties (x : xs)
  | [] <- x = removeEmpties xs
  | otherwise = x : removeEmpties xs

increment :: Int -> Int
increment x = y
  where
    y = x + 1

unzip' :: [(a, b)] -> ([a], [b])
unzip' [] = ([], [])
unzip' ((a, b) : xs) = (a : as, b : bs)
  where
    (as, bs) = unzip' xs