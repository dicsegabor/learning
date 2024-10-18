module Homework1 where

intExpr1::Int
intExpr1 = 2

intExpr2::Int
intExpr2 = 3

intExpr1PowIntExpr2::Int
intExpr1PowIntExpr2 = intExpr1 ^ intExpr2

stringExpr1::String
stringExpr1 = "func"

stringExpr2::String
stringExpr2 = "prog"

charExpr1::Char
charExpr1 = 'f'

charExpr2::Char
charExpr2 = 'p'

mult3Ints::Int->Int->Int->Int
mult3Ints x y z = x * y * z


is6006divisibleBy::Int->Int->Bool
is6006divisibleBy x y = (mod 6006 x == 0) && (mod 6006 y == 0)

threeAnd::Bool->Bool->Bool->Bool
threeAnd x y z = x && y && z

inc :: Int -> Int
inc x = x + 1

double :: Int -> Int
double x = x * 2

zero :: Int
zero = 0

is_14_1::Int
is_14_1 = double(inc(double(inc(inc(inc zero)))))

is_14_2::Int
is_14_2 = double(inc(double(inc(double(inc zero)))))

chocolatePerFriend::Int->Int->Int
chocolatePerFriend friend chocolate = div chocolate friend

leftoverChocolate::Int->Int->Int
leftoverChocolate friend chocolate = mod chocolate friend

isLeapYear::Int->Bool
isLeapYear year = (mod year 4 == 0) && ((mod year 100 /= 0) || (mod year 400 == 0)) 