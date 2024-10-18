module Lecture where

-- deriving Show "interface"
data Color = Red | Blue | Yellow | Green deriving (Show)

stringifyColor :: Color -> String
stringifyColor Red = "Red"
stringifyColor Blue = "Blue"
stringifyColor Yellow = "Yellow"
stringifyColor Green = "Green"

data Color' = RGB Int Int Int

-- Own method implementing show "interface"
instance Show Color' where
    show (RGB r g b) = show r ++ show g ++ show b

data Weather = Sunny | Rainy | Snowy deriving (Show)

instance Eq Weather where
    Sunny == Sunny = True
    Rainy == Rainy = True
    Snowy == Snowy = True
    _ == _ = False

data Clothing = Pants | Jacket | TShirt | Shoes Int deriving (Show)

instance Eq Clothing where
  Pants == Pants = True
  Jacket == Jacket = True
  TShirt == TShirt = True
  (Shoes x) == (Shoes y) = x == y
  _ == _ = False

data Component = CPU Int | GPU Int | HDD | SSD | PSU deriving (Eq)

instance Show Component where
  show (CPU x) = "CPU" ++ show x
  show (GPU x) = "GPU" ++ show x
  show HDD = "HDD"
  show SSD = "SSD"
  show PSU = "PSU"

-- Alias
type String' = String

-- Polmorf paraméter
--data Maybe' a = Nothing | Just a

data Tuple a b = Tuple a b deriving (Show)

safeIndex :: Int -> [a] -> Maybe a
safeIndex _ [] = Nothing 
safeIndex i (x:xs)
    | i < 0 = Nothing
    | i == 0 = Just x
    | otherwise = safeIndex (i-1) xs 

