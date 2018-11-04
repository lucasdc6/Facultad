import Data.Char
import Data.List

sum' :: [Int] -> Int
sum' = foldr (+) 0

any' :: [Bool] -> Bool
any' = foldr (\x y -> x || y) False

all' :: [Bool] -> Bool
all' = foldr (\x y -> x && y) True

codes' :: [Char] -> [Int]
codes' = foldr ((:) . ord) []

remainders' :: [Int] -> Int -> [Int]
remainders' = flip (\r -> foldr (\x xs -> (x `div` r) : xs) [])

squares' :: [Int] -> [Int]
squares' = foldr (\x xs -> (x * x) : xs) []

lengths' :: [[a]] -> [Int]
lengths' = foldr ((:) . length) []

pairs' :: [Int] -> [Int]
pairs' = foldr (\x xs -> if even x then x : xs else xs) []

chars' :: [Char] -> [Char]
chars' = foldr (\x xs -> if isAlpha x then x : xs else xs) []

-- moreThan' :: [[a]] -> Int -> [[a]]
moreThan' = flip (\n -> foldr (\xs xss -> if length xs > n then xs : xss else xss) [])


----------------------------------------------------------------
hs :: [[Char]] -> Int
hs = foldr (\str i -> if "he" `isPrefixOf` str then i+1 else i+0) 0

avgLength :: [[Char]] -> Int
avgLength = \xs -> let lengths = lengths' xs
                    in (sum lengths) `div` (length lengths)

adjacents :: [Int] -> [(Int, Int)]
adjacents = foldr (\x xs -> (x, head xs)) []