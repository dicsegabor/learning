module Lecture where

data Rational' = Rational' Int Int -- a/b1 b/=0

instance Show Rational' where
  show (Rational' a b) = show a ++ "/" ++ show b

instance Eq Rational' where
  (Rational' a1 b1) == (Rational' a2 b2) = div a1 b1 == div a2 b2

instance Num Rational' where
  (Rational' a1 b1) + (Rational' a2 b2) = Rational' ((a1 * b2) + (a2 * b1)) (b1 * b2)
  (Rational' a1 b1) * (Rational' a2 b2) = Rational' (a1 * a2) (b1 * b2)
  negate (Rational' a b) = Rational' (a * (-1)) b
  abs (Rational' a b) = Rational' (abs a) (abs b)
  signum (Rational' a b) = Rational' (signum a * signum b) 1
  fromInteger a = Rational' (fromInteger a) 1

simplify :: Rational' -> Rational'
simplify r@(Rational' a b)
  | gcd a b == 1 = r
  | otherwise = Rational' (div a (gcd a b)) (div b (gcd a b))

data Peano = Zero | Succ Peano deriving (Ord, Eq)

instance Num Peano where
  Zero + x = x
  (Succ x) + y = Succ (x + y)
  Zero - x = Zero
  x - Zero = x
  x - (Succ y)
    | Succ a <- x - y = a
    | otherwise = 0
  Zero * x = Zero
  (Succ Zero) * x = x
  (Succ x) * y = y * (x + y)
  abs x = x
  fromInteger x
    | x > 0 = Succ (fromInteger (x - 1))
    | otherwise = Zero
  signum Zero = Zero
  signum _ = Succ Zero

length' :: [a] -> Peano
length' [] = Zero
length' (x:xs) = Succ (length' xs)


data Whole = Pos Peano | NegSucc Peano
instance Num Whole where
    
    (Pos a) + (Pos b) = Pos (a + b)
    (Pos a) + (NegSucc b)
        | a >= b = Pos (a - b)
        | otherwise = NegSucc(a - b)
    (NegSucc a) + (NegSucc b) = NegSucc (a + b)


