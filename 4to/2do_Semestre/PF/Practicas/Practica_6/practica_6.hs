data TipTree a = Tip a | Join (TipTree a) (TipTree a) deriving Show
-- examples
-- Join (Tip 1) (Join (Tip 1) (Join (Join (Tip 2) (Tip 9)) (Tip 2)))

eTipTree1 = (Join (Tip 1) (Join (Tip 1) (Join (Join (Tip 2) (Tip 9)) (Tip 2))))
eTipTree2 = (Tip 1)
eTipTree3 = (Join (Join (Tip 1) (Tip 8)) (Join (Tip 1) (Join (Join (Tip 2) (Tip 9)) (Tip 2))))

-- heightTip
-- heightTip :: TipTree -> Int

heightTip :: TipTree a -> Int

-- Definicion por recursion en la estructura
-- heightTip Tip t = ...
-- heightTip Join (TipTree t1) (TipTree t2) = ... heightTip t1 ... heightTip t2

heightTip (Tip t) = 0
heightTip (Join t1 t2) = if heightTip t1 > heightTip t2 then 1 + heightTip t1 else 1 + heightTip t2

-- Definicion por recursion en la estructura
-- leaves Tip t = ...
-- leaves Join (TipTree t1) (TipTree t2) = ... leaves t1 ... leaves t2

leaves :: TipTree a -> Int
leaves (Tip t) = 1
leaves (Join t1 t2) = leaves t1 + leaves t2

nodes :: TipTree a -> Int

-- Definicion por recursion en la estructura
-- nodes Tip t = ...
-- nodes Join (TipTree t1) (TipTree t2) = ... nodes t1 ... nodes t2

nodes (Tip t) = 0
nodes (Join t1 t2) = 1 + nodes t1 + nodes t2

walkover :: TipTree a -> [TipTree a]
-- Definicion por recursion en la estructura
-- walkover Tip t = ...
-- walkover Join (TipTree t1) (TipTree t2) = ... walkover t1 ... walkover t2

walkover (Tip t) = [ Tip t ]
walkover (Join t1 t2) = walkover t1 ++ walkover t2

mirrorTip :: TipTree a -> TipTree a
-- Definicion por recursion en la estructura
-- mirrorTip Tip t = ...
-- mirrorTip Join (TipTree t1) (TipTree t2) = ... mirrorTip t1 ... mirrorTip t2

mirrorTip (Tip t) = (Tip t)
mirrorTip (Join t1 t2) = (Join (mirrorTip t2) (mirrorTip t1))

mapTip :: (a -> b) -> TipTree a -> TipTree b
mapTip f (Tip t) = Tip (f t)
mapTip f (Join t1 t2) = Join (mapTip f t1) (mapTip f t2)

foldTip :: (a -> b) -> (b -> b -> b) -> (TipTree a) -> b
foldTip fTip fJoin (Tip t) = fTip t
foldTip fTip fJoin (Join t1 t2) = fJoin (foldTip fTip fJoin t1) (foldTip fTip fJoin t2)


--------------------------------------------------------------------------------
data Seq a = Nil | Unit a | Cat (Seq a) (Seq a) deriving Show