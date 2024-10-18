module Homework10 where

data TriBool = Yes | No | Maybe deriving (Eq, Show)

instance Ord TriBool where
  No <= _ = True
  Maybe <= No = False
  Maybe <= Yes = True
  Maybe <= Maybe = True
  Yes <= _ = False

triOr :: TriBool -> TriBool -> TriBool
triOr Yes _ = Yes
triOr _ Yes = Yes
triOr Maybe _ = Maybe
triOr _ Maybe = Maybe
triOr No No = No

triAnd :: TriBool -> TriBool -> TriBool
triAnd No _ = No
triAnd _ No = No
triAnd Maybe _ = Maybe
triAnd _ Maybe = Maybe
triAnd Yes Yes = Yes

incMonotonityTest :: Ord a => Int -> [a] -> TriBool
incMonotonityTest _ [] = Yes
incMonotonityTest _ [a] = Yes
incMonotonityTest n (x : xs)
  | n == 1 = Maybe
  | x < head xs = triAnd Yes (incMonotonityTest (n - 1) xs)
  | otherwise = No

data GolfScore = Ace | Albatross | Eagle | Birdie | Par | Bogey Int

instance Eq GolfScore where
  Ace == Ace = True
  Albatross == Albatross = True
  Eagle == Eagle = True
  Birdie == Birdie = True
  Par == Par = True
  (Bogey a) == (Bogey b) = a == b
  _ == _ = False

instance Ord GolfScore where
  Ace <= _ = False
  _ <= Ace = True
  _ <= Albatross = True
  _ <= Eagle = True
  _ <= Birdie = True
  _ <= Par = True
  (Bogey a) <= (Bogey b) = a <= b
  _ <= (Bogey a) = False

score :: Int -> Int -> GolfScore
score _ 1 = Ace
score l n
  | s > 0 = Bogey s
  | s == 0 = Par
  | s == -1 = Birdie
  | s == -2 = Eagle
  | s <= -3 = Albatross
  where
    s = n - l