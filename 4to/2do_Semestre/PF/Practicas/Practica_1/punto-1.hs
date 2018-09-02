seven :: a -> Int
seven x = 7

sign :: Int -> Int
sign x | x < 0 = -1
       | x > 0 = 1
       | otherwise = 0

absolute :: Int -> Int
absolute x = (sign x * x)

absolute' :: Int -> Int
absolute' x | x < 0 = x * -1
            | otherwise = x

and' :: Bool -> Bool -> Bool
and' x y | x == False = False
         | y == False = False
         | otherwise = True

or' :: Bool -> Bool -> Bool
or' x y | x == True = True
        | y == True = True
        | otherwise = False

not' :: Bool -> Bool
not' x | x == True = False
       | x == False = True

xor' :: Bool -> Bool -> Bool
xor' x y | x == y = False
         | otherwise = True

dividesTo :: Int -> Int -> Bool
dividesTo x y | (mod x y) == 0 = True
              | otherwise = False

isMultiple :: Int -> Int -> Bool
isMultiple x y = dividesTo x y

isCommonDivisor :: Int -> (Int, Int) -> Bool
isCommonDivisor n (x, y) | dividesTo x n == False = False
                         | dividesTo y n == False = False
                         | otherwise = True

swap :: (Int, Int) -> (Int, Int)
swap (x, y) = (y, x)

greaterThan :: Int -> Int -> Bool
greaterThan x y | x > y = True
                | otherwise = False
