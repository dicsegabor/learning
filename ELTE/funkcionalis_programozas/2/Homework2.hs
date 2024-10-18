module Homework2 where

isCoconut :: String -> Bool
isCoconut "coconut" = True
isCoconut "kókuszdió" = True
isCoconut _ = False

twoPlusTwoIsFive :: Int -> Int -> Int
twoPlusTwoIsFive 2 2 = 5
twoPlusTwoIsFive x y = x + y

powers :: (Int, Int) -> (Int, Int)
powers (a, b) = (a ^ b, b ^ a)

triTuplify :: a -> b -> c -> (a, b, c)
triTuplify a b c = (a, b, c)

replaceMiddle :: d -> (a, b, c) -> (a, d, c)
replaceMiddle d (a, b, c) = (a, d, c)

dropThird :: (a, b, c, d) -> (a, b, d)
dropThird (a, b, c, d) = (a, b, d)

identity :: a -> a
identity a = a