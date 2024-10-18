module Homwork9 where

import Prelude hiding (NonEmpty(..)) -- a létező NonEmpty típust és a konstruktorait nem importálja be

data List a = Nil | Cons a (List a) deriving (Eq, Show)
data NonEmpty a = Last a | NECons a (NonEmpty a) deriving (Eq, Show)
data BinTree a = Leaf a | Node a (BinTree a) (BinTree a) deriving (Eq, Show)
data Stream a = SCons a (Stream a) deriving (Show)

dropMaybes :: [Maybe a] -> [a]
dropMaybes [] = []
dropMaybes (x:xs)
    | Just a <- x = a : dropMaybes xs
    | otherwise = dropMaybes xs

mapMaybe :: (a -> Maybe b) -> [a] -> [b]
mapMaybe _ [] = []
mapMaybe f (x:xs)
    | Just a <- f x = a : mapMaybe f xs
    | otherwise = mapMaybe f xs

(+++) :: List a -> List a -> List a
(+++) Nil l = l
(+++) (Cons a Nil) l = Cons a l
(+++) (Cons a l1) l2 = Cons a (l1 +++ l2)

treeToList :: BinTree a -> List a
treeToList (Leaf a) = Cons a Nil
treeToList (Node a t1 t2) = Cons a (treeToList t1) +++ treeToList t2

neLength :: NonEmpty a -> Int
neLength (Last a) = 1
neLength (NECons _ l) = 1 + neLength l

(++++) :: NonEmpty a -> NonEmpty a -> NonEmpty a
(++++) (Last a) l = NECons a l
(++++) (NECons a (Last b)) l = NECons a (NECons b l)
(++++) (NECons a l1) l2 = NECons a (l1 ++++ l2)


treeToNonEmpty :: BinTree a -> NonEmpty a
treeToNonEmpty (Leaf a) = Last a
treeToNonEmpty (Node a t1 t2) = NECons a (treeToNonEmpty t1) ++++ treeToNonEmpty t2

eqUpTo :: Eq a => Int -> Stream a -> Stream a -> Bool
eqUpTo 0 _ _ = True
eqUpTo 1 (SCons a al) (SCons b bl) = a == b
eqUpTo n (SCons a al) (SCons b bl) = a == b && eqUpTo (n-1) al bl

cycleNE :: NonEmpty a -> Stream a
cycleNE l@(Last a) = SCons a (cycleNE l)
cycleNE (NECons a l@(Last b)) = SCons a (cycleNE l)
cycleNE (NECons a l) = SCons a (cycleNE l)