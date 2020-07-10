:- module( hw5 , [ configuration / 3 ] ) .
:- [ hardware ] .




  

elementinlist([H|[]],H).
elementinlist([H|T],H).
isouter(Comp,Cons):-member(outer_edge(Comp),Cons).
isclose_to(Comp,Cons,R):-member(close_to(Comp,R),Cons).
isadjacent(A,B):-adjacent(A,B);adjacent(B,A).


putter(_,[],[]).
putter(A,[H|T],[put(A,H)|R]):-putter(A,T,R).  

notouter([],_,[]). 
notouter([H|T],Fix,[H|R]):-notout(H,Fix,0),!,notouter(T,Fix,R).
notouter([H|T],Fix,R):-not(notout(H,Fix,0)),!,notouter(T,Fix,R).


notout(A,[H|T],0):-isadjacent(A,H),!,notout(A,T,1).
notout(A,[H|T],1):-isadjacent(A,H),!,notout(A,T,2).
notout(A,[H|T],2):-isadjacent(A,H),!,notout(A,T,3).
notout(A,[H|T],3):-isadjacent(A,H),!.
notout(A,[H|T],0):- not(isadjacent(A,H)),!,notout(A,T,0).
notout(A,[H|T],1):- not(isadjacent(A,H)),!,notout(A,T,1).
notout(A,[H|T],2):- not(isadjacent(A,H)),!,notout(A,T,2).
notout(A,[H|T],3):- not(isadjacent(A,H)),!,notout(A,T,3).

out([],_,[]).
out([H|T],Fix,[H|R]):-not(member(H,Fix)),!,out(T,Fix,R).
out([H|T],Fix,R):-member(H,Fix),!,out(T,Fix,R).

outer(A,Fix,R):- notouter(Fix,Fix,Notouter),out(A,Notouter,R).




configuration([],_,[]).


helper([],_,_,_,_,PrevResult,PrevResult).
helper([Comp|Comprest],ConstList,SectionList,Outer,Notouter,PrevResult,Result):-isouter(Comp,ConstList),!,putlist(Comp,Outer,PrevResult,Result),change(Result,PrevResult),helper(Comprest,ConstList,SectionList,Outer,Notouter,PrevResult,Result).

helper([Comp|T],ConstList,SectionList,Outer,Notouter,PrevResult,Result):-helper(T,ConstList,SectionList,Outer,Notouter,PrevResult,Result).



% putouter(Component,Outer,[put(Component,Outer)|R]):-


puter(Comp,Sect,put(Comp,Sect)).

putlist(Comp,[Possible|T],Result,[Put|Result]):-puter(Comp,Possible,Put).
putlist(Comp,[_|T],Result,Res):-putlist(Comp,T,Result,Res).






% putlist(Comp,[Possible|T],Put):-puter(Comp,Possible,Put).
% putlist(Comp,[_|T],Res):-putlist(Comp,T,Res).


putlister([],_,List,List).
putlister([Comp|CompRest],Possible,List,Result):-putlist(Comp,Possible,List,Put),putlister(CompRest,Possible,Put,Result).

change([],[]).
change([H|T],[H|Result]):-change(T,Result).

helper([],_,_,_,List,Result):-reverse(List,Result).
helper([Comp|CompRest],ConstList,[Outer|OuterRest],AdjacentList,List,Result):-isouter(Comp,ConstList),!, not(member( put(_,Outer),List )),!,putlist(Comp,[Outer|OuterRest],List,PutList),helper(CompRest,ConstList,OuterRest,AdjacentList,PutList,Result).

helper([Comp|CompRest],ConstList,[Outer|OuterRest],AdjacentList,List,Result):-not(isouter(Comp,ConstList)),!,helper(CompRest,ConstList,[Outer|OuterRest],AdjacentList,List,Result).

helper([Comp|CompRest],ConstList,[Outer|OuterRest],AdjacentList,List,Result):-isouter(Comp,ConstList),!, member(put(_,Outer),List),!,helper([Comp|CompRest],ConstList,OuterRest,AdjacentList,List,Result).
