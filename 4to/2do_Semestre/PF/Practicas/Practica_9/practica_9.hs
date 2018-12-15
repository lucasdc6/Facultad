data TipTree a = Tip a | Join (TipTree a) (TipTree a) deriving Show

tipTreeE = Join (Tip 2) (Join (Tip 1) (Join (Tip 2) (Tip 3)))

foldTipTree :: ( a -> b ) -> ( b -> b -> b ) -> TipTree a -> b
foldTipTree f g (Tip t) = f t
foldTipTree f g (Join t1 t2) = g (foldTipTree f g t1) (foldTipTree f g t2)

heightTip' :: TipTree a -> Int
heightTip' = foldTipTree (const 0) (\t1 t2 -> if t1 > t2 then 1 + t1 else 1 + t2)

leaves' :: TipTree a -> Int
leaves' = foldTipTree (const 1) (+)

nodes' :: TipTree a -> Int
nodes' = foldTipTree (const 0) (\t1 t2 -> t1 + t2 + 1)

walkover' :: TipTree a -> [a]
walkover' = foldTipTree (: []) (++)

idTip' :: TipTree a -> TipTree a
idTip' = foldTipTree Tip Join

mirrorTip' :: TipTree a -> TipTree a
mirrorTip' = foldTipTree Tip (flip Join)

mapTip' :: (a -> b) -> TipTree a -> TipTree b
mapTip' f = foldTipTree (Tip . f) Join


-- Punto 2
data BinTree a = Empty | Bin a (BinTree a) (BinTree a) deriving (Show, Eq)


binTree = Bin 1 (Bin 2 Empty Empty) Empty

-- nodesBin Empty = ...
-- nodesBin Bin n t1 t2 = n ... nodesBin t1 ... nodesBin t2

nodesBin :: BinTree a -> Int
nodesBin Empty = 0
nodesBin (Bin n t1 t2) = 1 + nodesBin t1 + nodesBin t2

-- heightBin Empty = ...
-- heightBin (Bin n t1 t2) = n ... heightBin t1 ... heightBin t2

heightBin :: BinTree a -> Int
heightBin Empty = 0
heightBin (Bin n t1 t2) = if heightBin t1 > heightBin t2 then heightBin t1 + 1 else heightBin t2 + 1

mapBin :: (a -> b) -> BinTree a -> BinTree b
mapBin f Empty = Empty
mapBin f (Bin n t1 t2) = Bin (f n) (mapBin f t1) (mapBin f t2)

mirrorBin :: BinTree a -> BinTree a
mirrorBin Empty = Empty
mirrorBin (Bin n t1 t2) = Bin n t2 t1

foldBin :: (a -> b -> b -> b) -> b -> BinTree a -> b
foldBin f z Empty = z
foldBin f z (Bin n t1 t2) = f n (foldBin f z t1) (foldBin f z t2) 

mapBin' :: (a -> b) -> BinTree a -> BinTree b
mapBin' f = foldBin (\n t1 t2 -> (Bin (f n) t1 t2)) Empty

heightBin' :: BinTree a -> Int
heightBin' = foldBin (\n t1 t2 -> t1 + t2 + 1) 0

mirrorBin' :: BinTree a -> BinTree a
mirrorBin' = foldBin (\n t1 t2 -> (Bin n t2 t1)) Empty

-- Punto 3

data GenTree a = Gen a [GenTree a] deriving Show

foldGen :: (a -> [b] -> b) -> GenTree a -> b
foldGen f (Gen t ts) = f t (map (foldGen f) ts)

foldGen' :: (a -> c -> b) -> ([b] -> c) -> GenTree a -> b
foldGen' f g (Gen x ts) = f x (g (map (foldGen' f g) ts))

children (Gen _ ts) = ts


treeGen = Gen 2 [Gen 2 [], Gen 3 [Gen 3 []]]

recGen :: (a -> [b] -> [GenTree a] -> b) -> GenTree a -> b
recGen f t@(Gen x ts) = foldGen f' t t
  where f' x fs (Gen _ ts) = f x (zipWith ($) fs ts) ts


takeWhileGen :: (a -> Bool) -> GenTree a -> GenTree a
takeWhileGen p = recGen (\x rs _ -> if p x then Gen x rs else Gen x [] ) 

-- dropWhileGen :: (a -> Bool) -> GenTree a -> GenTree a
-- dropWhileGen p = recGen (\x _ ts -> if p x then Gen (head ts) (tail ts) else Gen x ts )


-- Punto 5

data GenExp a = Leaf a | Un (GenExp a) | BinG (GenExp a) (GenExp a)

foldGenExp :: (a -> b) -> (b -> b) -> (b -> b -> b) -> GenExp a -> b
foldGenExp fLeaf fUn fBinG (Leaf x) = fLeaf x
foldGenExp fLeaf fUn fBinG (Un e) = fUn (foldGenExp fLeaf fUn fBinG e)
foldGenExp fLeaf fUn fBinG (BinG e1 e2) = fBinG (foldGenExp fLeaf fUn fBinG e1) (foldGenExp fLeaf fUn fBinG e2)

data NExp = Num Int | Sum NExp NExp | Sub NExp NExp | Mul NExp NExp | Neg NExp

foldNExp :: (Int -> a) -> (a -> a -> a) -> (a -> a -> a) -> (a -> a -> a) -> (a -> a) -> NExp -> a
foldNExp fNum fSum fSub fMul fNeg (Num n) = fNum n
foldNExp fNum fSum fSub fMul fNeg (Sum e1 e2) = fSum (foldNExp fNum fSum fSub fMul fNeg e1) (foldNExp fNum fSum fSub fMul fNeg e2)
foldNExp fNum fSum fSub fMul fNeg (Sub e1 e2) = fSub (foldNExp fNum fSum fSub fMul fNeg e1) (foldNExp fNum fSum fSub fMul fNeg e2)
foldNExp fNum fSum fSub fMul fNeg (Mul e1 e2) = fMul (foldNExp fNum fSum fSub fMul fNeg e1) (foldNExp fNum fSum fSub fMul fNeg e2)
foldNExp fNum fSum fSub fMul fNeg (Neg e) = fNeg (foldNExp fNum fSum fSub fMul fNeg e)

foldEither :: (a -> c) -> (b -> c) -> Either a b -> c
foldEither f g (Left x) = f x
foldEither f g (Right x) = g x


data Nat = Zero | Succ Nat deriving Show

foldNat :: (a -> a) -> a -> Nat -> a
foldNat f z Zero = z
foldNat f z (Succ n) = f (foldNat f z n)

sumNat :: Nat -> Int
sumNat = foldNat (\tot -> tot + 1) 0

zero = Zero
one = Succ(Zero)
seven = Succ(Succ(Succ(Succ(Succ(Succ(Succ(Zero)))))))

-- Extra

data Weird a b = First a
               | Second b
               | Third [(a,b)]
               | Fourth (Weird a b) deriving Show

weirdE = Fourth (Third [(1,'a')])

foldW :: ( a -> c ) -> ( b -> c ) -> ( [(a,b)] -> c ) -> ( c -> c ) -> Weird a b -> c
foldW fFirst fSecond fThird fFourth (First x) = fFirst x
foldW fFirst fSecond fThird fFourth (Second x) = fSecond x
foldW fFirst fSecond fThird fFourth (Third xs) = fThird xs
foldW fFirst fSecond fThird fFourth (Fourth w) = fFourth (foldW fFirst fSecond fThird fFourth w)
