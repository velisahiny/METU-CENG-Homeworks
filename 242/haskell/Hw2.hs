module Hw2 where

import Data.List -- YOU MAY USE THIS MODULE FOR SORTING THE AGENTS

data Level = Newbie | Intermediate | Expert deriving (Enum, Eq, Ord, Show, Read)
data Hunter = Hunter {hID::Int, hlevel::Level, hEnergy::Int, hNumberOfCatches::Int, hActions::[Direction]} deriving (Eq, Show, Read)
data Prey = Prey {pID::Int, pEnergy::Int, pActions::[Direction]} deriving (Eq, Show, Read)
data Cell = O | X | H Hunter | P Prey | T deriving (Eq, Show, Read)
data Direction = N | S | E | W deriving (Eq, Show, Read)
type Coordinate = (Int, Int)
instance Ord Hunter where
   compare (Hunter id1 lvl1 heng1 catch1 _) (Hunter id2 lvl2 heng2 catch2 _) = if lvl1 == lvl2 then
                                                                                        if heng1 == heng2 then
                                                                                           if catch1 == catch2 then
                                                                                              compare id2 id1
                                                                                           else compare catch1 catch2
                                                                                        else compare heng1 heng2
                                                                                else compare lvl1 lvl2


instance Ord Prey where
   compare (Prey id1 peng1 _) (Prey id2 peng2 _) = if peng1==peng2 then compare id2 id1 else compare peng1 peng2


huntergenerator::[Cell]->Coordinate->[(Hunter,Coordinate)]
huntergenerator [] (x,y) = []
huntergenerator ((H h1):rest) (x,y) =   ( h1,(x,y)) : (huntergenerator rest (x+1,y) )
huntergenerator (a:rest) (x,y) = huntergenerator rest ((x+1),y)

huntergen::[[Cell]]->Int->[(Hunter,Coordinate)]
huntergen [] _ = []
huntergen (a:rest) y = ( huntergenerator a (0,y) ) ++ (huntergen rest (y+1))

hunterg::[[Cell]]->[(Hunter,Coordinate)]
hunterg clist = huntergen clist 0


preygenerator::[Cell]->Coordinate->[(Prey,Coordinate)]
preygenerator [] (x,y) = []
preygenerator ((P p1):rest) (x,y) =   ( p1,(x,y)) : (preygenerator rest (x+1,y) )
preygenerator (a:rest) (x,y) = preygenerator rest ((x+1),y)

preygen::[[Cell]]->Int->[(Prey,Coordinate)]
preygen [] _ = []
preygen (a:rest) y = ( preygenerator a (0,y) ) ++ (preygen rest (y+1))

preyg::[[Cell]]->[(Prey,Coordinate)]
preyg clist = preygen clist 0

preyid :: Coordinate ->[(Int,Coordinate)] -> [Int]
preyid _ [] = []
preyid (_,-1) (coord:rest) = []
preyid (-1,_) (coord:rest) = []
preyid (x,y) (coord:rest) = if (snd coord) == (x,y) then ( (fst coord) : (preyid (x,y) rest) )
                            else preyid (x,y) rest --koordinatı girilen degere eşit olan preylerin idlerini dönüyor

huntermvr::[[Cell]] -> (Hunter,Coordinate) -> Coordinate
huntermvr clist (h,(hx,hy)) =   case (hActions h)!!0 of N -> let location =  (hx,(hy-1))
                                                             in if (isclean location clist)== 1 then location
                                                                else (hx,hy)
                                                        S -> let location =  (hx,(hy+1))
                                                             in if (isclean location clist)== 1 then location
                                                                else (hx,hy)
                                                        E ->let location =  ((hx+1),hy)
                                                             in if (isclean location clist)== 1 then location
                                                                else (hx,hy)
                                                        W ->let location =  ((hx-1),hy)
                                                             in if (isclean location clist)== 1 then location
                                                                else (hx,hy)

search::[Int] -> Int -> Int
search [] _ = 0
search (id:r) pid = if pid == id then 1
                  else search r pid

cutp:: [Int] -> Int -> [Prey]->[Prey]
cutp _ n [] = []
cutp _ 2 p = p
cutp [] _ p = p
cutp id n (p:rest) = if search id (pID p) == 1 then cutp id (n+1) rest
                     else ( p : (cutp id n rest) ) -- idleri verilen preylerin ilk ikisini silip yeni [Prey] dönüyor

searchpidcord::[Prey]-> Int ->Int
searchpidcord [] _ = 0
searchpidcord (p:r) pid = if pid == (pID p) then 1
                          else searchpidcord r pid

cutpidcord::[Prey]-> [(Int,Coordinate)]->[(Int,Coordinate)]
cutpidcord [] _ = []
cutpidcord _ [] = []
cutpidcord p (coord:rest) = if (searchpidcord p (fst coord)) == 1 then (coord:cutpidcord p rest)
                            else cutpidcord p rest -- verilen preylistesinde id si olmayan id leri [(Int,Coordinate)]
                                                            --listesinden siliyor yenisini dönüyor

clean :: Int -> [Cell] -> Int
clean _ [] = 0
clean (-1) (v:rest) = 0
clean y (v:rest) = if y == 0 && v == X then 0
                            else if  y == 0 then 1
                                 else clean (y-1) rest

isclean :: (Int,Int)->[[Cell]] -> Int
isclean _ [] = 0
isclean (_,-1) (clist:rest) = 0
isclean (-1,_) _ = 0
isclean (x,y) (clist:rest) = if y == 0 then (clean x clist)
                                 else isclean (x, (y-1) ) (rest)


trap :: Int -> [Cell] -> Int
trap _ [] = 0
trap (-1) (v:rest) = 0
trap y (v:rest) = if y == 0 && v == T then 1
                            else if  y == 0 then 0
                                 else trap (y-1) rest

istrap :: (Int,Int)->[[Cell]] -> Int
istrap _ [] = 0
istrap (_,-1) (clist:rest) = 0
istrap (x,y) (clist:rest) = if y == 0 then (trap x clist)
                                 else istrap (x, (y-1) ) (rest)


hunter_move::[[Cell]] -> (Hunter,Coordinate) -> [Prey] -> [(Int,Coordinate)] -> ((Hunter,Coordinate),[Prey], [ (Int,Coordinate) ] )

hunter_move clist (h ,(x,y)) rsp pidcord = if (hEnergy h) >= 10 then
                                              let location = huntermvr clist (h,(x,y))
                                              in let pid = preyid location pidcord
                                                in if (length pid) >= 1  then --prey/ler yakalandı
                                                     let rsp1 = cutp pid 0 rsp
                                                     in let fark = (length rsp) - (length rsp1)
                                                        in if ((hEnergy h)+((fark*20) -1)) <= 100 then
                                                             let energy = (hEnergy h)+((fark*20) -1)
                                                             in let pidcord1 = cutpidcord rsp1 pidcord
                                                                    hunter1 = Hunter (hID h) (hlevel h) energy ( (hNumberOfCatches h)+ fark ) (drop 1 (hActions h))
                                                                in ((hunter1,location),rsp1,pidcord1)
                                                           else let energy = 100
                                                                in let pidcord1 = cutpidcord rsp1 pidcord
                                                                       hunter1 = Hunter (hID h) (hlevel h) energy ( (hNumberOfCatches h)+ fark ) (drop 1 (hActions h))
                                                                in ((hunter1,location),rsp1,pidcord1)
                                                   else let hunter0 = Hunter (hID h) (hlevel h) ( (hEnergy h) -1)  ( (hNumberOfCatches h) ) (drop 1 (hActions h))
                                                        in ((hunter0,location),rsp,pidcord)
                                           else let location = (x,y)
                                                in let pid = preyid location pidcord
                                                   in if (length pid) >= 1  then --prey/ler yakalandı
                                                        let rsp1 = cutp pid 0 rsp
                                                        in let fark = (length rsp) - (length rsp1)
                                                           in if ((hEnergy h)+((fark*20) -1)) <= 100 then
                                                                let energy = (hEnergy h)+((fark*20) -1)
                                                                in let pidcord1 = cutpidcord rsp1 pidcord
                                                                       hunter1 = Hunter (hID h) (hlevel h) energy ( (hNumberOfCatches h)+fark ) (drop 1 (hActions h))
                                                                   in ((hunter1,location),rsp1,pidcord1)
                                                              else let energy = 100
                                                                   in let pidcord1 = cutpidcord rsp1 pidcord
                                                                          hunter1 = Hunter (hID h) (hlevel h) energy ( (hNumberOfCatches h)+fark ) (drop 1 (hActions h))
                                                                      in ((hunter1,location),rsp1,pidcord1)

                                                      else if ((hEnergy h)+1) <= 100 then
                                                             let hunter0 = Hunter (hID h) (hlevel h) ( (hEnergy h)+1) ( (hNumberOfCatches h) ) (drop 1 (hActions h))
                                                             in ( (hunter0,location),rsp,pidcord)
                                                           else let energy = 100
                                                                in let hunter0 = Hunter (hID h) (hlevel h) energy ( (hNumberOfCatches h) ) (drop 1 (hActions h))
                                                                   in ( (hunter0,location),rsp,pidcord)

preymvr::[[Cell]] -> (Prey,Coordinate) -> Coordinate
preymvr clist (p,(x,y)) =   case (pActions p)!!0 of N -> let location =  (x,(y-1))
                                                         in if (isclean location clist)== 1 then location
                                                            else (x,y)
                                                    S -> let location =  (x,(y+1))
                                                         in if (isclean location clist)== 1 then location
                                                            else (x,y)
                                                    E ->let location =  ((x+1),y)
                                                        in if (isclean location clist)== 1 then location
                                                           else (x,y)
                                                    W ->let location =  ((x-1),y)
                                                        in if (isclean location clist)== 1 then location
                                                           else (x,y)

preycoordfinder::Prey->[(Int,Coordinate)]->(Prey,Coordinate)
preycoordfinder p [] = (p,(-1,-1))
preycoordfinder p (coord:r) = if (fst coord) == (pID p) then (p,(snd coord))
                              else preycoordfinder p r




prey_move::[[Cell]]->Prey -> [(Int,Coordinate)]-> (Prey,Coordinate)
prey_move clist p coord = let (p1,c1) = preycoordfinder p coord
                          in if (pEnergy p1) >= 10 then
                               let location = preymvr clist (p1,c1)
                               in if (istrap location clist) == 1 then
                                    if ((pEnergy p1)-11) < 0 then
                                        let p2 = Prey (pID p1) 0 (drop 1 (pActions p1))
                                        in (p2,location)
                                    else
                                        let p2 = Prey (pID p1) ((pEnergy p1)-11) (drop 1 (pActions p1))
                                        in (p2,location)
                                  else let p2 = Prey (pID p1) ((pEnergy p1)-1) (drop 1 (pActions p1))
                                       in (p2,location)
                             else if (istrap c1 clist) == 1 then
                                    let p2 = Prey (pID p1) 0 (drop 1 (pActions p1))
                                    in (p2,c1)
                                  else let p2 = Prey (pID p1) ((pEnergy p1)+1) (drop 1 (pActions p1))
                                       in (p2,c1)

preysorted_move::[[Cell]]->[Prey]->[(Int,Coordinate)]->[(Prey,Coordinate)]
preysorted_move clist [] _ = []
preysorted_move clist (p:r) coord = (prey_move clist p coord):(preysorted_move clist r coord)


huntercoordfinder::Hunter->[(Hunter,Coordinate)]->(Hunter,Coordinate)
huntercoordfinder h [] =  (h,(-1,-1))
huntercoordfinder h (coord:rest) = if (hID (fst coord) ) == (hID h) then (h,(snd coord))
                                   else huntercoordfinder h rest

huntercoordchanger::(Hunter,Coordinate)->[(Hunter,Coordinate)]->[(Hunter,Coordinate)]
huntercoordchange (h,c) [] =  []
huntercoordchanger (h,c) (coord:rest) =  if (hID (fst coord) ) == (hID h) then (h,c):rest
                                         else coord:(huntercoordchanger (h,c) rest)


huntersorted_move::[[Cell]] -> [Hunter]-> [(Hunter,Coordinate)] -> [Prey] -> [(Int,Coordinate)] -> ( [(Hunter,Coordinate)], [Prey], [ (Int,Coordinate) ] )-- preylerin sayısı değişti hunterlar değişti
huntersorted_move _ [] hcoord p pcoord = (hcoord,p,pcoord)
huntersorted_move clist (h:r) hcoord p pcoord = let (h1,c1) = huntercoordfinder h hcoord
                                                in let ((h2,c2),p2,pcoord2) = hunter_move clist (h1,c1) p pcoord
                                                   in let hcoord2 = huntercoordchanger (h2,c2) hcoord
                                                      in huntersorted_move clist r hcoord2 p2 pcoord2


pidcoordgenerator::[(Prey,Coordinate)]->[(Int,Coordinate)]
pidcoordgenerator [] = []
pidcoordgenerator (pcoord:rest) = ( (pID (fst pcoord) ) , (snd pcoord) ): pidcoordgenerator rest

pcoordsorter::[(Prey,Coordinate)]->[Prey]
pcoordsorter [] = []
pcoordsorter (pcoord:rest) = (fst pcoord) :(pcoordsorter rest)

pcoordsearch::Prey -> [(Int,Coordinate)]->(Prey,Coordinate)
pcoordsearch p (pid:rest) = if (pID p) == fst pid then (p,snd pid)
                            else pcoordsearch p rest

pcoordgenerator::[Prey]->[(Int,Coordinate)]->[(Prey,Coordinate)]
pcoordgenerator [] _  = []
pcoordgenerator _ [] = []
pcoordgenerator (p:r) pid = (pcoordsearch p pid) : (pcoordgenerator r pid)


huntersorter::[(Hunter,Coordinate)]->[Hunter]
huntersorter [] = []
huntersorter (hcoord:rest) = (fst hcoord) :(huntersorter rest)

simulatehelp::[[Cell]]->Int->[(Hunter,Coordinate)]->[(Prey,Coordinate)]-> ([(Hunter,Coordinate)] , [( Prey , Coordinate )])
simulatehelp _ 0 hcoord pcoord = (hcoord,pcoord)
simulatehelp _ _ hcoord [] = (hcoord,[])
simulatehelp clist n hcoord pcoord = let plist = reverse (sort (pcoordsorter pcoord)) --bana gore sorted büyükbaşta
                                         pidcoord = (pidcoordgenerator pcoord)
                                         hlist = reverse (sort (huntersorter hcoord) ) --bana gore sorted
                                     in let pcoord2 = preysorted_move clist plist pidcoord
                                        in let plist1 = reverse (sort (pcoordsorter pcoord2))--bana gore sorted
                                               pidcoord1 = pidcoordgenerator pcoord2
                                            in let reverseplist = reverse plist1  --bana gore reverse sorted büyük sonda
                                               in let (hcoord2,plist2,pidcoord2) = (huntersorted_move clist hlist hcoord reverseplist pidcoord1)
                                                  in let pcoord3 = pcoordgenerator plist2 pidcoord2
                                                     in if (length plist2 ) == 0 then (hcoord2 ,[])
                                                     else simulatehelp clist (n-1) hcoord2 pcoord3


directioncounter::(Hunter,Coordinate)->Int
directioncounter hcoord = length (hActions (fst hcoord))


prehuntsearch::Hunter -> [(Hunter,Coordinate)] ->(Hunter,Coordinate)
prehuntsearch h (hcoord:rest) = if (hID h) == (hID (fst hcoord)) then (h, (snd hcoord))
                                else prehuntsearch h rest

prehuntsort::[Hunter]->[(Hunter,Coordinate)]->[(Hunter,Coordinate)]
prehuntsort [] _ = []
prehuntsort _ [] = []
prehuntsort (h:r) hcoord = (prehuntsearch h hcoord) : (prehuntsort r hcoord)





prepreysearch::Prey -> [(Prey,Coordinate)] ->(Prey,Coordinate)
prepreysearch p (pcoord:rest) = if (pID p) == (pID (fst pcoord)) then (p, (snd pcoord))
                                else prepreysearch p rest

prepreysort::[Prey]->[(Prey,Coordinate)]->[(Prey,Coordinate)]
prepreysort [] _ = []
prepreysort _ [] = []
prepreysort (p:r) pcoord = (prepreysearch p pcoord) : (prepreysort r pcoord)


preysorter::[(Prey,Coordinate)]->[Prey]
preysorter [] = []
preysorter (pcoord:rest) = (fst pcoord) :(preysorter rest)



simulate ::[[Cell]]->([(Hunter,Coordinate)] , [( Prey , Coordinate )])
simulate clist = let hcoord = (hunterg clist)
                     pcoord = (preyg clist)
                 in let n = directioncounter (hcoord !! 0)
                    in let (notsortedhcoord,notsortedpcoord) = simulatehelp clist n hcoord pcoord
                       in let hlist = huntersorter notsortedhcoord
                              plist = preysorter notsortedpcoord
                          in let sortedhcoord = reverse( sort(prehuntsort hlist notsortedhcoord) )
                                 sortedpcoord = sort (prepreysort plist notsortedpcoord)
                             in (sortedhcoord,sortedpcoord)
