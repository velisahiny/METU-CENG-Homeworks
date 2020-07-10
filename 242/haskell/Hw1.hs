module Hw1 where

data Cell = H | P | O | X deriving (Read,Show,Eq)
data Result = Fail | Caught (Int,Int) deriving (Read,Show,Eq)
data Direction = N | S | E | W deriving (Read,Show,Eq)

simulate :: [[Cell]] -> [(Direction, Direction)] -> Result
-- DO NOT CHANGE ABOVE THIS LINE, WRITE YOUR CODE BELOW --
find :: Cell -> Int -> [Cell] -> Int
find  c n [] = -1
find  c n (v:rest) = if v == c then n
                         else find  c (n+1) (rest)
findper :: Cell -> Int -> [[Cell]] -> (Int,Int)
findper p r [] = (-1,-1)
findper p r (clist:rest) = let a = find p 0 clist
                           in if a == -1 then findper p (r+1) rest
                                         else (a ,r)
--findper p 0 clist ile calisacak--


replace_with_direction :: Cell ->(Int,Int)-> Int-> Int -> Direction -> [[Cell]]-> (Int,Int)
replace_with_direction _ (x,y) _ _ _ [] = (x,y)
replace_with_direction _ (x,y) (-1) _ _ _ = (x,y)
replace_with_direction _ (x,y) _ (-1) _ _ = (x,y)
replace_with_direction c (x,y) xlen ylen d clist= case d of N ->  if (y-1) >= ylen  then (x,y)
                                                                  else if isclean c (x,(y-1) ) clist == 1 then (x,(y-1))
                                                                  else (x,y)
                                                            S -> if (y+1) >= ylen then (x,y)
                                                                 else if isclean c (x,(y+1)) clist ==1 then (x,(y+1))
                                                                 else (x,y)
                                                            E -> if (x+1) >= xlen then (x,y)
                                                                 else if  isclean c ((x+1),y) clist == 1  then ((x+1),y)
                                                                 else (x,y)
                                                            W -> if (x-1) >= xlen then (x,y)
                                                                 else if isclean c ((x-1),y) clist == 1 then ((x-1),y)
                                                                 else (x,y)


x_len :: [Cell] -> Int
x_len [] = 0
x_len (v:rest) = x_len(rest) + 1

y_len :: [[Cell]]->Int
y_len [] = 0
y_len (v:rest) = y_len(rest) +1

clean :: Cell -> Int -> [Cell] -> Int
clean _ _ [] = 0
clean _ (-1) (v:rest) = 0
clean x y (v:rest) = if y == 0 && v == X then 0
                            else if  y == 0 then 1
                                 else clean x (y-1) rest

isclean :: Cell -> (Int,Int)->[[Cell]] -> Int
isclean _ _ [] = 0
isclean _ (_,-1) (clist:rest) = 0
isclean c (x,y) (clist:rest) = if y == 0 then (clean c x clist)
                                 else isclean c (x, (y-1) ) (rest)

simulatehelp :: [[Cell]]-> [(Direction,Direction)]->(Int,Int)->(Int,Int) -> Int ->Int -> Result
simulatehelp [] _ _ _ _ _ = Fail
simulatehelp _ [] _ _ _ _ = Fail
simulatehelp clist (dirlist:rest) (hx,hy) (px,py) xlen ylen = if (hx,hy) == (px,py) then Caught(px,py)
                                                              else let (hdir,pdir) = dirlist
                                                                   in let (hx2,hy2) = replace_with_direction H (hx,hy) xlen ylen hdir clist
                                                                          (px2,py2) = replace_with_direction P (px,py) xlen ylen pdir clist
                                                                      in if (hx2,hy2) == (px2,py2) then  Caught (px2,py2)
                                                                         else simulatehelp clist rest (hx2,hy2) (px2,py2) xlen ylen
simulate [] _ = Fail
simulate clist dirlist = let (hx,hy) = findper H 0 clist
                             (px,py) = findper P 0 clist
                             ylen = (y_len) clist
                             xlen = (x_len) (head clist)
                         in simulatehelp clist dirlist (hx,hy) (px,py) xlen ylen
