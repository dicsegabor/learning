module Homework5 where

import Data.Char (isLower)

removeLowers :: String -> String
removeLowers [] = []
removeLowers (x : xs)
  | isLower x = rec
  | otherwise = x : rec
  where
    rec = removeLowers xs

orderList :: Ord a => [a] -> [a]
orderList [] = []
orderList [a] = [a]
orderList l@(x : y : xs)
  | x <= minimum l = x : orderList (y : xs)
  | x > y = orderList (y : orderList (x : xs))
  | otherwise = orderList (x : orderList (y : xs))

parallelAdd :: Num a => [a] -> [a] -> [a]
parallelAdd _ [] = []
parallelAdd [] _ = []
parallelAdd (x : xs) (y : ys) = (x + y) : parallelAdd xs ys

superIndex :: Int -> [a] -> a
superIndex _ [] = error "Empty list can't be indexed."
superIndex i l
  | i < 0 = reverse l !! neg_i
  | otherwise = l !! i
  where
    neg_i = (i + 1) * (-1)

delAll :: Eq a => a -> [a] -> [a]
delAll _ [] = []
delAll e (x : xs)
  | x == e = rec
  | otherwise = x : rec
  where
    rec = delAll e xs

uniques :: Eq a => [a] -> [a]
uniques [] = []
uniques (x : xs) = x : uniques (delAll x xs)

{-
    1.  A statikus típusrendszer azt jelenti, hogy mindennek a típusát tudjuk fordítási időben.
    2.  Ha egy hosszú futási idővel rendelkező fv-t, nem biztos, hogy ki kell értékelni, akkor nem biztos, hogy lefut a fv. (nem kell külön odafigyelni erre)
    3.  1. Lekéri egy háromelemű lista második elemét, ami a statikusan definiált 1.
    4.  Az eset ami biztosan lefut, de csak akkor, ha előtte egy sem futott le.
    5.  Az első guardban nem csökkentjük a listát a rekurzív hívásnál.
 -}