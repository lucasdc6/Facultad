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

-- order :: [(Int, Int)] -> [(Int, Int)]
-- order x = ...
-- order (x,xs) = ... x ... order xs ...

order :: [(Int, Int)] -> [(Int, Int)]
order [] = []
order ((x1, x2):xs) = if x1*3 < x2 then (x1, x2) : order xs else order xs

-- pairs :: [Int] -> [Int]
-- pairs x = ...
-- pairs (x:xs) = ... x ... pairs xs ...

pairs :: [Int] -> [Int]
pairs [] = []
pairs (x:xs) = if even x then x : pairs xs else pairs xs

-- chars :: [Char] -> [Char]
-- chars x = ...
-- chars (x:xs) = ... x ... chars xs ...

chars :: [Char] -> [Char]
chars [] = []
chars (x:xs) = if isAlpha x then x : chars xs else chars xs

-- moreThan :: [[a]] -> Int -> [[a]]
-- moreThan x = ...
-- moreThan (x:xs) = ... x ... moreThan xs ...

moreThan :: [[a]] -> Int -> [[a]]
moreThan [] _ = []
moreThan (x:xs) num = if length x > num then x : moreThan xs num else moreThan xs num

-- listOdd :: [[Int]] -> [Int]
-- listOdd x = ...
-- listOdd (x:xs) = ... x ... listOdd xs ...