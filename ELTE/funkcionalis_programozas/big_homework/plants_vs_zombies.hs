module PlantsVsZombies where

import Data.List (elemIndex, filter, lookup, minimumBy)
import Data.Maybe (fromJust, isJust, isNothing)

type Coordinate = (Int, Int)

type Sun = Int

data Plant = Peashooter Int | Sunflower Int | Walnut Int | CherryBomb Int deriving (Eq, Show)

getPlantHealth :: Plant -> Int
getPlantHealth (Peashooter h) = h
getPlantHealth (Sunflower h) = h
getPlantHealth (Walnut h) = h
getPlantHealth (CherryBomb h) = h

plantPrice :: Plant -> Sun
plantPrice (Peashooter _) = 100
plantPrice (CherryBomb _) = 150
plantPrice _ = 50

tryPurchase :: GameModel -> Coordinate -> Plant -> Maybe GameModel
tryPurchase (GameModel s pl zl) c@(x, y) p
  | outOfBounds c = Nothing
  | plantPrice p > s = Nothing
  | isJust (lookup c pl) = Nothing
  | otherwise = Just (GameModel (s - plantPrice p) ((c, p) : pl) zl)

damagePlant :: Plant -> Int -> Plant
damagePlant (Peashooter hp) n = Peashooter (hp - n)
damagePlant (Sunflower hp) n = Sunflower (hp - n)
damagePlant (Walnut hp) n = Walnut (hp - n)
damagePlant (CherryBomb hp) n = CherryBomb (hp - n)

damagePlantOnCoordinate :: Coordinate -> Int -> [(Coordinate, Plant)] -> [(Coordinate, Plant)]
damagePlantOnCoordinate c1 n = map (\(c2, p) -> if c1 == c2 then (c2, damagePlant p n) else (c2, p))

plantActions :: GameModel -> (Coordinate, Plant) -> GameModel
plantActions gm@(GameModel s pl zl) (c, Peashooter _) = GameModel s pl (damageZombieOnCoordinate (getNextZombieCoordinateOnLane c zl) 1 zl)
plantActions gm@(GameModel s pl zl) (c, Sunflower _) = GameModel (s + 25) pl zl
plantActions gm@(GameModel s pl zl) (c, CherryBomb h) = GameModel s (damagePlantOnCoordinate c h pl) (foldl (flip killZombieOnCoordinate) zl (getSurroundingCoordinates c 1))
plantActions gm@(GameModel s pl zl) _ = gm

-- Plant constructors
defaultPeashooter :: Plant
defaultPeashooter = Peashooter 3

defaultSunflower :: Plant
defaultSunflower = Sunflower 2

defaultWalnut :: Plant
defaultWalnut = Walnut 15

defaultCherryBomb :: Plant
defaultCherryBomb = CherryBomb 2

data Zombie = Basic Int Int | Conehead Int Int | Buckethead Int Int | Vaulting Int Int deriving (Eq, Show)

getZombieHealth :: Zombie -> Int
getZombieHealth (Basic h _) = h
getZombieHealth (Conehead h _) = h
getZombieHealth (Buckethead h _) = h
getZombieHealth (Vaulting h _) = h

getZombieSpeed :: Zombie -> Int
getZombieSpeed (Basic _ s) = s
getZombieSpeed (Conehead _ s) = s
getZombieSpeed (Buckethead _ s) = s
getZombieSpeed (Vaulting _ s) = s

placeZombieInLane :: GameModel -> Zombie -> Int -> Maybe GameModel
placeZombieInLane (GameModel s pl zl) z x
  | outOfBounds c = Nothing
  | isJust (lookup c zl) = Nothing
  | otherwise = Just (GameModel s pl ((c, z) : zl))
  where
    c = (x, 11)

zombieEat :: GameModel -> (Coordinate, Zombie) -> GameModel
zombieEat gm@(GameModel s pl zl) (c, _) = GameModel s (damagePlantOnCoordinate c 1 pl) zl

replaceZombie :: (Coordinate, Zombie) -> (Coordinate, Zombie) -> [(Coordinate, Zombie)] -> [(Coordinate, Zombie)]
replaceZombie zwc_f zwc_r zl = x ++ zwc_r : ys
  where
    (x, _ : ys) = splitAt (fromJust $ elemIndex zwc_f zl) zl

zombieMove :: GameModel -> (Coordinate, Zombie) -> GameModel
zombieMove (GameModel s pl zl) zwc@(c@(x, y), z@(Vaulting h zs))
  | isJust (lookup (x, y - 1) pl) = GameModel s pl (replaceZombie zwc ((x, y - getZombieSpeed z), Vaulting h 1) zl)
  | isJust (lookup c pl) = GameModel s pl (replaceZombie zwc ((x, y - 1), Vaulting h 1) zl)
  | otherwise = GameModel s pl (replaceZombie zwc ((x, y - getZombieSpeed z), z) zl)
zombieMove (GameModel s pl zl) zwc@(c@(x, y), z) = GameModel s pl (replaceZombie zwc ((x, y - getZombieSpeed z), z) zl)

zombieActions :: GameModel -> (Coordinate, Zombie) -> GameModel
zombieActions gm@(GameModel _ pl zl) zwc@(c, z@(Vaulting _ s))
  | s > 1 = zombieMove gm zwc
  | isJust (lookup c pl) = zombieEat gm zwc
  | otherwise = zombieMove gm zwc
zombieActions gm@(GameModel _ pl _) zwc@(c, _)
  | isJust (lookup c pl) = zombieEat gm zwc
  | otherwise = zombieMove gm zwc

damageZombie :: Zombie -> Int -> Zombie
damageZombie (Basic hp s) n = Basic (hp - n) s
damageZombie (Conehead hp s) n = Conehead (hp - n) s
damageZombie (Buckethead hp s) n = Buckethead (hp - n) s
damageZombie (Vaulting hp s) n = Vaulting (hp - n) s

damageZombieOnCoordinate :: Coordinate -> Int -> [(Coordinate, Zombie)] -> [(Coordinate, Zombie)]
damageZombieOnCoordinate c1 n = map (\(c2, z) -> if c1 == c2 then (c2, damageZombie z n) else (c2, z))

killZombieOnCoordinate :: Coordinate -> [(Coordinate, Zombie)] -> [(Coordinate, Zombie)]
killZombieOnCoordinate c1 = map (\(c2, z) -> if c1 == c2 then (c2, damageZombie z (getZombieHealth z)) else (c2, z))

-- Zombie constructors
basic :: Zombie
basic = Basic 5 1

coneHead :: Zombie
coneHead = Conehead 10 1

bucketHead :: Zombie
bucketHead = Buckethead 20 1

vaulting :: Zombie
vaulting = Vaulting 7 2

data GameModel = GameModel Sun [(Coordinate, Plant)] [(Coordinate, Zombie)] deriving (Eq, Show)

outOfBounds :: Coordinate -> Bool
outOfBounds (x, y) = x > 4 || x < 0 || y > 11 || y < 0

isEnd :: GameModel -> Maybe GameModel
isEnd gm@(GameModel _ _ zl)
  | any ((>) 0 . snd . fst) zl = Nothing
  | otherwise = Just gm

performZombieActions :: GameModel -> Maybe GameModel
performZombieActions gm@(GameModel _ _ []) = Just gm
performZombieActions gm@(GameModel s pl zl) = isEnd $ foldl zombieActions gm zl

performPlantActions :: GameModel -> GameModel
performPlantActions gm@(GameModel _ [] _) = gm
performPlantActions gm@(GameModel s pl zl) = foldl plantActions gm pl

cleanBoard :: GameModel -> GameModel
cleanBoard (GameModel s pl zl) = GameModel s (filter ((<) 0 . getPlantHealth . snd) pl) (filter ((<) 0 . getZombieHealth . snd) zl)

defendsAgainst :: GameModel -> [[(Int, Zombie)]] -> Bool
defendsAgainst gm n_zl
  | isJust aza_gm = True
  | otherwise = False
  where
    apa_gm = performPlantActions gm
    acb_gm = cleanBoard apa_gm
    aza_gm = performZombieActions acb_gm
    apz_gm = map (foldl (\acc (c,z) -> placeZombieInLane (fromJust acc) z c) aza_gm) n_zl

-- Other functions

getSurroundingCoordinates :: Coordinate -> Int -> [Coordinate]
getSurroundingCoordinates (x, y) r = [(s_x, s_y) | s_x <- [(x - r) .. (x + r)], s_y <- [(y - r) .. (y + r)]]

getNextZombieCoordinateOnLane :: Coordinate -> [(Coordinate, Zombie)] -> Coordinate
getNextZombieCoordinateOnLane _ [] = (-1, -1)
getNextZombieCoordinateOnLane (x, y) zl = fst $ minimumBy (\((_, y1), _) ((_, y2), _) -> compare y1 y2) (filter (\((x2, y2), _) -> x == x2 && y <= y2) zl)