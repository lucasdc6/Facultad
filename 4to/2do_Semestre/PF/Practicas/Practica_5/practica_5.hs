import Data.Char

-- listSum :: [a] -> Int
-- listSum x = ...
-- listSum (x:xs) = ... x ... listSum xs ...

listSum :: [a] -> Int
listSum [] = 0
listSum (x:xs) = 1 + listSum xs

-- listAny :: [Bool] -> Bool
-- listAny x = ...
-- listAny (x:xs) = ... x ... listAny xs ...

listAny :: [Bool] -> Bool
listAny [] = False
listAny (x:xs) = x || listAny xs

-- listAll :: [Bool] -> Bool
-- listAll x = ...
-- listAll (x:xs) = ... x ... listAll xs ...

listAll :: [Bool] -> Bool
--listAll [] = False
listAll [x] = x
listAll (x:xs) = x && listAll xs

-- codes :: [Char] -> [Int]
-- codes x = ...
-- codes (x:xs) = ... x ... codes xs ...


codes :: [Char] -> [Int]
codes [] = []
codes (x:xs) = (ord x) : codes xs

-- remainders :: [Int] -> Int -> Int
-- remainders x = ...
-- remainders (x:xs) = ... x ... remainders xs ...

remainders :: [Int] -> Int -> [Int]
remainders [] _ = []
remainders (x:xs) num = (x `div` num) : remainders xs num

-- squares :: [Int] -> [Int]
-- squares x = ...
-- squares (x:xs) = ... x ... squares xs ...

squares :: [Int] -> [Int]
squares [] = []
squares (x:xs) = x*x : squares xs

-- lengths :: [[a]] -> Int
-- lengths x = ...
-- lengths (x:xs) = ... x ... lengths xs ...

lengths :: [[a]] -> [Int]
lengths [] = []
lengths (x:xs) = (length x) : lengths xs 