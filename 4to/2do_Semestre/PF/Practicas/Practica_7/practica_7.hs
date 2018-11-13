import Data.Char
import Data.List

-- foldr :: (a -> b -> b) -> b -> [a] -> b
--recr :: b -> (a -> [a] -> b -> b) -> [a] -> b
recr z f xs = foldr (\x h (_:ys) -> f x ys (h ys)) (const z) xs xs


-- recr' z f [] = ...
-- recr' z f (x:xs) = x ... recr' xs ...
recr' :: b -> (a -> [a] -> b -> b) -> [a] -> b
recr' z f [] = z
recr' z f (x:xs) = f x xs (recr' z f xs) 

tail' = recr (error "Lista vacía") (\_ xs _ -> xs)

sum' :: [Int] -> Int
sum' = foldr (+) 0

any' :: [Bool] -> Bool
any' = foldr (||) False

all' :: [Bool] -> Bool
all' = foldr (&&) True

codes' :: [Char] -> [Int]
codes' = foldr ((:) . ord) []

remainders' :: [Int] -> Int -> [Int]
remainders' = flip (\r -> foldr (\x xs -> (x `div` r) : xs) [])

squares' :: [Int] -> [Int]
squares' = foldr (\x xs -> (x * x) : xs) []

squares'' :: [Int] -> [Int]
squares'' = map (\x -> x*x)

lengths' :: [[a]] -> [Int]
lengths' = foldr ((:) . length) []

pairs' :: [Int] -> [Int]
pairs' = foldr (\x xs -> if even x then x : xs else xs) []

chars' :: [Char] -> [Char]
chars' = foldr (\x xs -> if isAlpha x then x : xs else xs) []

moreThan' :: [[a]] -> Int -> [[a]]
moreThan' = flip (\n -> foldr (\xs xss -> if length xs > n then xs : xss else xss) [])

----------------------------------------------------------------
hs :: [[Char]] -> Int
hs = foldr (\str i -> if "he" `isPrefixOf` str then i+1 else i+0) 0

hs' :: [[Char]] -> Int
hs' x = length (filter (isPrefixOf "he") x)

avgLength :: [[Char]] -> Int
avgLength = \xs -> let lengths = lengths' xs
                    in (sum lengths) `div` (length lengths)

avgLength' :: [[Char]] -> Int
avgLength' xs = (sum lengths) `div` (length lengths)
                where lengths = lengths' xs

adjacents :: [a] -> [(a,a)]
adjacents = recr' [] (\x xs ys -> [(x, x)])

