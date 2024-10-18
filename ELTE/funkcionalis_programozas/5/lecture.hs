{- 
Parciális fv = olyan fv, ami nincs minden esetre definiálva
Totális fv = olyan fv, ami minden sestre definiálva van
Statikus típusosság = Minden kifejezésnek fordítási időben el lehet dönteni a típusát
Polimorfizmus = Egy olyan érték, aminek nincsen meghatározott típusa (fordítási időben van hozzárendelve) (f :: a -> a)
Inferálás = A fordító kitalálja az érték típusát
Ad-hoc polimorfizmus = leszőkítjük egy polimorf típus típusait (f :: Num a => a)
Lusta kiértékelés = Csak akkor értékelődik ki egy kifejezés, ha szükség van rá
Tiszta fv = nincsen af fv-nek mellékhatása (pl felülírni valamit, IO)
Tuple vs list = tuple: heterogén típus, fix hossz, nincs generátor; list : homogén típus, végtelen hossz, van generátor
Halmazkifejezés = listagenerátor
:: opertáor = fv-ről vagy értékrről megköti a típusát
 -}

module Lecture where

contains :: Eq a => a -> [a] -> Bool
contains _ [] = False
contains a (x:xs)
    | a == x = True
    | otherwise = contains a xs

reverseList :: [a] -> [a]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

combineList :: [a] -> [a] -> [a]
combineList [] xs = xs
combineList xs [] = xs
combineList (y:ys) (x:xs) = y : combineList ys xs

smallest :: Ord a => [a] -> a
smallest [] = error "Empty list"
smallest [x] = x
smallest (x:xs)
    | x < sm = x
    | otherwise = sm
        where
            sm = smallest xs

removeDuplicates :: Eq a => [a] -> [a]
removeDuplicates [] = []
removeDuplicates l@(x:xs)
    | contains x xs = r
    | otherwise = x : r
    where
        r = removeDuplicates xs