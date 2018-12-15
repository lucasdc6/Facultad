-- Punto 4
-- a
-- first :: (a,b) -> a
first (x,y) = x

-- b
-- second :: (a,b) -> b
second (x, y) = y

-- c
-- const :: a -> b -> a
const' x y = x

-- d
-- compose :: (a -> b) -> (c -> a) -> c -> b
compose f g = (\x -> f (g x))

-- e
-- apply :: (a -> b) -> a -> b
apply f x = f x

-- f
-- subst :: (a -> b -> c) -> (a -> b) -> a -> c
subst f g x = f x (g x)

-- g
-- pairFunc: (a -> b, b -> a) -> b -> a -> (b -> a)
pairFunc (f1,f2) x y = (f1 (f2 x), f2 (f1 y))


-- Punto 6
-- a) if (seven ’a’ < 1) then 5 else power4 2
-- Correcta, el resultado es 4

-- b) if False then True
-- Incorrecto, el if, debe contar con then y else

-- c) a := 4
-- Incorrecto, No se asigna de esa manera

-- d) (1 < x && x < 100) || x == True || x == False
-- Incorrecto, se intenta comprar un entero (x), con un Bool (True y False)

-- e) False == (1 < 3)
-- Correcto, el resultado es False

-- f) (1 < x < 2)
-- Incorrecto, no se cuenta con un operador de ese tipo

-- Punto 8
-- a Colores
data PrimaryColor = Red | Blue | Yellow deriving Show
data SecondaryColor = Green | Violet | Orange deriving Show

mix :: PrimaryColor -> PrimaryColor -> SecondaryColor
mix Red Blue = Violet
mix Red Yellow = Orange
mix Blue Yellow = Green
mix Blue Red = Violet
mix Yellow Red = Orange
mix Yellow Blue = Green

-- b Puntos
data (Num a) => Point a = Point2D a a | Point3D a a a deriving Show

sqr :: Float -> Float
sqr x = x * x

xcoord :: Point -> Float
xcoord (Point2D x _) = x
xcoord (Point3D x _ _) = x

ycoord :: Point -> Float
ycoord (Point2D _ y) = y
ycoord (Point3D _ y _) = y

zcoord :: Point -> Float
zcoord (Point3D _ _ z) = z

pointModule :: Point -> Point -> Float
pointModule (Point2D x1 y1) (Point2D x2 y2) = sqrt ((sqr (x2 - x1)) + (sqr (y2 - y1)))
pointModule (Point3D x1 y1 z1) (Point3D x2 y2 z2) = sqrt ((sqr (x2 - x1)) + (sqr (y2 - y1)) + (sqr (z2 - z1)))
pointModule (Point2D x1 y1) (Point3D x2 y2 z2) = sqrt ((sqr (x2 - x1)) + (sqr (y2 - y1)) + (sqr (z2)))
pointModule (Point3D x1 y1 z1) (Point2D x2 y2) = sqrt ((sqr (x2 - x1)) + (sqr (y2 - y1)) + (sqr (z1)))

pointAdd :: Point -> Point -> Point
pointAdd (Point2D x1 y1) (Point2D x2 y2) = (Point2D (x1 + x2) (y1 + y2))
pointAdd (Point3D x1 y1 z1) (Point3D x2 y2 z2) = (Point3D (x1 + x2) (y1 + y2) (z1 + z2))
pointAdd (Point2D x1 y1) (Point3D x2 y2 z2) = (Point3D (x1 + x2) (y1 + y2) (z2))
pointAdd (Point3D x1 y1 z1) (Point2D x2 y2) = (Point3D (x1 + x2) (y1 + y2) (z1))

originDistance :: Point -> Point
originDistance (Point2D x1 y1) = Point2D (abs(x1)) (abs(y1))
originDistance (Point3D x1 y1 z1) = Point3D (abs(x1)) (abs(y1)) (abs(z1))

-- c Figura
data Shape = Circle Point Float
            | Rectangle Point Point
            | Triangle Point Point Point deriving Show

area :: Shape -> Float
area (Circle _ ratio) = pi * (ratio ** 2)
area (Rectangle (Point2D x1 y1) (Point2D x2 y2)) = (abs (x1 - x2)) * (abs (y1 - y2))
area (Triangle (Point2D x1 y1) (Point2D x2 y2) (Point2D x3 y3)) = (abs ((x1-x2)-(y1-y2))) * (abs ((x1-x3)-(y1-y3))) / 2

perimeter :: Shape -> Float
perimeter (Circle _ ratio) = 2 * pi * ratio
perimeter (Rectangle (Point2D x1 y1) (Point2D x2 y2)) = (2*(abs (x1 - x2))) * (2*(abs (y1 - y2)))

move :: Shape -> Float -> Float -> Shape
move (Circle (Point2D x y) ratio ) newX newY = Circle (Point2D (x+newX) (y+newY)) ratio
move (Rectangle (Point2D x1 y1) (Point2D x2 y2)) newX newY = Rectangle (Point2D (x1+newX) (y1+newY)) (Point2D (x2+newX) (y2+newY))
