-- Punto 1
seven :: a -> Int
seven _ = 7

sign :: Int -> Int
sign x | x < 0 = -1
       | x > 0 = 1
       | otherwise = 0

absolute :: Int -> Int
absolute x = sign x * x

absolute' :: Int -> Int
absolute' x | x < 0 = x * (-1)
            | otherwise = x

and' :: (Bool, Bool) -> Bool
and' (x,y) | not x
           | y == False = False
           | otherwise = True

andC' :: Bool -> Bool -> Bool
andC' x y | x == False = False
          | y == False = False
          | otherwise = True

or' :: (Bool, Bool) -> Bool
or' (x,y) | x == True = True
          | y == True = True
          | otherwise = False

orC' :: Bool -> Bool -> Bool
orC' x y | x == True = True
         | y == True = True
         | otherwise = False

not' :: Bool -> Bool
not' x | x == True = False
       | x == False = True

xor' :: (Bool, Bool) -> Bool
xor' (x,y) | x == y = False
           | otherwise = True

xorC' :: Bool -> Bool -> Bool
xorC' x y | x == y = False
          | otherwise = True

dividesTo :: (Int, Int) -> Bool
dividesTo (x,y) | mod x y == 0 = True
                | otherwise = False

dividesToC :: Int -> Int -> Bool
dividesToC x y | mod x y == 0 = True
               | otherwise = False

isMultiple :: (Int, Int) -> Bool
isMultiple (x,y) = dividesTo(x,y)

isMultipleC :: Int -> Int -> Bool
isMultipleC = dividesToC

isCommonDivisor :: (Int, (Int, Int)) -> Bool
isCommonDivisor (n,(x, y)) | not dividesTo(x,n) = False
                           | not dividesTo(y,n) = False
                           | otherwise = True

isCommonDivisorC :: Int -> (Int, Int) -> Bool
isCommonDivisorC n (x, y) | not (dividesToC x n) = False
                          | not (dividesToC y n) = False
                          | otherwise = True

swap :: (Int, Int) -> (Int, Int)
swap (x, y) = (y, x)

swapC :: Int -> Int -> (Int,Int)
swapC x y = (y, x)

-- Punto 2

greaterThan :: (Int, Int) -> Bool
greaterThan (x,y)  | x > y = True
                   | otherwise = False

greaterThanC :: Int -> Int -> Bool
greaterThanC x y | x > y = True
                 | otherwise = False

-- Punto 3

sqr :: Int -> Int
sqr x = x * x

power4 :: Int -> Int
power4 x =  let sqr y = y * y
            in sqr (sqr x)

power4' :: Int -> Int
power4' x = sqr (sqr x)

power4'' :: Int -> Int
power4'' x = sqr x * sqr x

-- Punto 4

fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

-- Punto 9

leapYear :: Int -> Bool
leapYear x | dividesToC (mod x 100) 4 && mod x 100 > 0 = True
           | dividesToC x 400 = True
           | otherwise = False
