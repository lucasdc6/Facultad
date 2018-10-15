-- Punto 5

-- a
-- twice f x = f (f x)

twice = \f x -> f (f x)

-- b
-- flip f x y = f y x
flip = \f x y -> f y x

-- c
-- inc = (+1)
inc = \x -> (x+1)

fix f x = f (fix f) x