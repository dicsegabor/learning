{- 1. kerdes: Az a nem biztos, hogy olyan típus amivel szorozni lehet -}
{- 2. kerdes: Mindennek megvan a típusa, és a fordító fordítási időben ki tudja találni -}

module ZARTHELYI1 where

scalar :: (Int, Int, Int) -> (Int, Int, Int) -> Int
scalar (x1, y1, z1) (x2, y2, z2) = (x1 * x2) + (y1 * y2) + (z1 * z2)

numbers :: [Int]
numbers = reverse [x | x<-[1..1000], mod x 5 == 3, mod (3 * x) 7 == 2]

xor::Bool->Bool->Bool
xor True False = True
xor False True = True
xor _ _ = False

logicalFunctionB :: Bool -> Bool -> Bool -> Bool
logicalFunctionB True True _ = False
logicalFunctionB True _ _ = False
logicalFunctionB False a b = xor a b