data Point = Point2D Float Float | Point3D Float Float Float deriving Show
data Shape = Circle Point Float
            | Rectangle Point Point
            | Triangle Point Point Point deriving Show

area :: Shape -> Float
area (Circle _ ratio) = pi * (ratio ** 2)
area (Rectangle (Point2D x1 y1) (Point2D x2 y2)) = (abs (x1 - x2)) * (abs (y1 - y2))
area (Triangle (Point2D x1 y1) (Point2D x2 y2) (Point2D x3 y3)) = (abs ((x1-x1)-(y1-y2))) * ()

perimeter :: Shape -> Float
perimeter (Circle _ ratio) = 2 * pi * ratio
perimeter (Rectangle (Point2D x1 y1) (Point2D x2 y2)) = (2*(abs (x1 - x2))) * (2*(abs (y1 - y2)))

move :: Shape -> Float -> Float -> Shape
move (Circle (Point2D x y) ratio ) newX newY = Circle (Point2D (x+newX) (y+newY)) ratio
move (Rectangle (Point2D x1 y1) (Point2D x2 y2)) newX newY = Rectangle (Point2D (x1+newX) (y1+newY)) (Point2D (x2+newX) (y2+newY))
