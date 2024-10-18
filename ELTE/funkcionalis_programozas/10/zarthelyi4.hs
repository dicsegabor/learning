module Zarthelyi4 where

import Data.List (sortBy, maximumBy)

{- 
1. Nincsen a típusra az Eq definiálva
 -}

data Plant = Fruit String Int | Vegetable String Int deriving (Show)

instance Eq Plant where
    (Vegetable s1 p1) == (Vegetable s2 p2) = s1 == s2 && p1 == p2
    (Fruit s1 p1) == (Fruit s2 p2) = s1 == s2 && p1 == p2
    (Fruit _ _) == (Vegetable _ _) = False
    (Vegetable _ _) == (Fruit _ _) = False

type Plants = [Plant]

plantType::Plant->String
plantType (Fruit _ _) = "Fruit"
plantType _ = "Vegetable"

sortPlants::Plants -> Plants
sortPlants [] = []
sortPlants l = sortBy (\(Vegetable _ p1) (Vegetable _ p2) -> compare p1 p2) vegetables ++ sortBy (\(Fruit _ p1) (Fruit _ p2) -> compare p1 p2) fruits
    where
        fruits = filter (\x -> plantType x == "Fruit") l
        vegetables = filter (\x -> plantType x == "Vegetable") l

searchVegetable :: Plants -> String -> Maybe Plant
searchVegetable [] _ = Nothing
searchVegetable (v@(Vegetable n _):xs) s
    | n == s = Just v
    | otherwise = searchVegetable xs s
searchVegetable (x:xs) s = searchVegetable xs s

expensiveFruit :: Plants -> Maybe Plant
expensiveFruit [] = Nothing
expensiveFruit l
    | null fruits = Nothing
    | otherwise = Just (maximumBy (\(Fruit _ p1) (Fruit _ p2) -> compare p1 p2) fruits)
    where
        fruits = filter (\x -> plantType x == "Fruit") l