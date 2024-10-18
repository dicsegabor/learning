module Lecture where

f :: Num a => a -> a -> a
f a b = a + b

g :: Eq a => a -> a -> Bool
g a b = a == b

myList :: [Int]
myList = [1, 2, 3, 4, 6, 5, 7]

myList2 :: [Int]
myList2 = [1 .. 200]

myList3 :: [Int]
myList3 = [1, 0 .. (-10)]

-- infinite list
myList4 :: [Int]
myList4 = [1, 0 ..]

isEmpty :: [a] -> Bool
isEmpty [] = True
isEmpty (x : xs) = False

concatBothWays :: [a] -> [a] -> ([a], [a])
concatBothWays a b = (a ++ b, b ++ a)

appendTwo :: (a, a) -> [a] -> [a]
appendTwo (a, b) l = a : (b : l)

isLength3 :: [a] -> Bool
isLength3 [a, b, c] = True
isLength3 _ = False

addOne::[Int] -> [Int]
addOne ls = [l + 1 | l <- ls]

addOneToPositives :: [Int] -> [Int]
addOneToPositives ls = [l + 1 | l <- ls, l > 0]

intersection :: [Int] -> [Int] -> [Int]
intersection a b = [l1 | l1 <- a, l2 <- b, l1 == l2]

onlyOnes :: [Int] -> [Int]
onlyOnes l = [1 | 1 <- l]

squareAll::[Int] -> [Int]
squareAll ls = [l ^ 2 | l<-ls]

divisors:: Int -> [Int] -> [Int]
divisors a ls = [l | l<-ls, mod l a == 0]

mulTups :: [(Int, Int, Int)] -> [Int]
mulTups ls = [a * b * c | (a, b, c) <- ls]

concatList :: [[a]] -> [a]
concatList ls = [i2 | i1<-ls, i2<-i1]