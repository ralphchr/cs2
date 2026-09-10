module LE2 where
--keep the line above and dont rename this file


cube :: Int -> Int
cube x = x * x * x

double :: Int -> Int
double x = 2 * x

modulus :: Int -> Int -> Int
modulus x y
    | x < y = x
    | otherwise = modulus (x-y) y

factorial :: Int -> Int
factorial 0 = 1
factorial x = x * factorial (x - 1)


compose :: (Int -> Int) -> (Int -> Int) -> (Int -> Int)
compose f g = (\x -> f(g x))

subtractMaker :: Int -> (Int -> Int)
subtractMaker x = \y -> x - y

applyNTimes :: (Int -> Int) -> Int -> Int -> Int
applyNTimes f n x
    | n <= 0 = x
    | otherwise = applyNTimes f (n-1) (f x)

largestPowerOf2 :: Int -> Int
largestPowerOf2 1 = 1
largestPowerOf2 x = 2 * largestPowerOf2 (x `div` 2)