
{-# LANGUAGE DeriveFoldable #-}
module Lecture where

data List a = Nil | Cons a (List a) deriving (Foldable)

data Tree a = TNil | Leaf a | Node a (Tree a) (Tree a)

sum' :: Num a => List a -> a
sum' Nil = 0
sum' (Cons a as) = a + sum' as

sum'' :: Num a => Tree a -> a
sum'' TNil = 0
sum'' (Leaf a) = a
sum'' (Node a t1 t2) = a + sum'' t1 + sum'' t2

product' :: Num a => List a -> a
product' Nil = 1
product' (Cons a as) = a * product' as

product'' :: Num a => Tree a -> a
product'' TNil = 1
product'' (Leaf a) = a
product'' (Node a t1 t2) = a * product'' t1 * product'' t2

elem' :: Eq a => a -> List a -> Bool
elem' _ Nil = False
elem' x (Cons a as) = a == x || elem' x as

elem'' :: Eq a => a -> Tree a -> Bool
elem'' _ TNil = False
elem'' x (Leaf a) = a == x
elem'' x (Node a t1 t2) = a == x || elem'' x t1 || elem'' x t2 

inorder :: Show a => Tree a -> String
inorder TNil = ""
inorder (Leaf a) = show a
inorder (Node a t1 t2) = inorder t1 ++ show a ++ inorder t2 

preorder :: Show a => Tree a -> String
preorder TNil = ""
preorder (Leaf a) = show a
preorder (Node a t1 t2) = show a ++ preorder t1 ++ preorder t2 

postorder :: Show a => Tree a -> String
postorder TNil = ""
postorder (Leaf a) = show a
postorder (Node a t1 t2) = postorder t1 ++ postorder t2 ++ show a

data NonEmptyList a = NEList a | NECons a (NonEmptyList a)

data ThreeTree a = TTNil | TLeaf a | TNode a (ThreeTree a) (ThreeTree a) (ThreeTree a)

data Stream a = SCons a (Stream a)
