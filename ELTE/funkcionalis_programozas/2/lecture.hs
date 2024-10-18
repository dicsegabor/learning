module Lecture where

tuple :: (Int, Bool)
tuple = (4, True)

not' :: Bool -> Bool
not' True = False
not' False = True

not'' :: Bool -> Bool
not'' True = False
not'' _ = True

sixth :: (Int, Double, Bool, String, String, Char) -> Char
sixth (a, b, c, d, e, f) = f

myFavoriteNumer :: Int -> Bool
myFavoriteNumer 42 = True
myFavoriteNumer _ = False

and' :: Bool -> Bool -> Bool
and' True True = True
and' _ _ = False

or' :: Bool -> Bool -> Bool
or' False False = False
or' _ _ = True

xor' :: Bool -> Bool -> Bool
xor' x y = not' (and' x y)

addThree :: (Int, Int, Int) -> Int
addThree (a, b, c) = a + b + c

first :: (a, b) -> a
first = fst

triplify :: a -> (a, a, a)
triplify a = (a, a, a)

quadruplify :: a -> (a, a, a, a)
quadruplify a = (a, a, a, a)

swap :: (a, b) -> (b, a)
swap (a, b) = (b, a)

shiftRight :: (a, b, c) -> (c, a, b)
shiftRight (a, b, c) = (c, a, b)

isSmallPrime :: Int -> Bool
isSmallPrime 2 = True
isSmallPrime 3 = True
isSmallPrime 5 = True
isSmallPrime 7 = True
isSmallPrime _ = False

addThreeNums :: (Num a) => a -> a -> a -> a
addThreeNums a b c = a + b + c