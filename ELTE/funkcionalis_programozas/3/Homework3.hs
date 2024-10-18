module Homework3 where

mulThree :: Num a => a -> a -> a -> a
mulThree a b c = a * b * c

comparison :: Ord a => a -> a -> (Bool, Bool)
comparison a b = (a >= b, a <= b)

tripletToList :: (a, a, a) -> [a]
tripletToList (a, b, c) = [a, b, c]

second :: [a] -> a
second a = a !! 1

trim :: [a] -> [a]
trim [] = []
trim [a] = []
trim (x : xs) = init xs

isEmpty :: [a] -> Bool
isEmpty [] = True
isEmpty (x : xs) = False

divisors :: Int -> [Int]
divisors a = [x | x<-[2..(a-1)], mod a x == 0]

primes :: [Int]
primes = [x | x<-[2..], divisors x == []]

permutate :: [a] -> [b] -> [(a,b)]
permutate [] _ = []
permutate _ [] = []
permutate a b = [(x, y) | x<-a, y<-b]

concatLists :: [[a]] -> [a]
concatLists a = [y | x<-a, y<-x]