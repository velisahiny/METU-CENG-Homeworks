:- module( hw5 , [ configuration / 3 ] ) .
:- [ hardware ] .




  

elementinlist([H|[]],H).
elementinlist([H|T],H).
isouter(Comp,Cons):-member(outer_edge(Comp),Cons).
isclose_to(Comp,Cons,R):-member(close_to(Comp,R),Cons);member(close_to(R,Comp),Cons).
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

adjacentlist(_,[],[]).
adjacentlist(Sect,[S|T],[S|AdjList]):-isadjacent(Sect,S),!,adjacentlist(Sect,T,AdjList).
adjacentlist(Sect,[S|T],AdjList):-adjacentlist(Sect,T,AdjList).




configuration([],_,[]).
configuration(CompList,ConstList,Placement):-sections(SectionList),helper(CompList,ConstList,SectionList,NSL,[],Placement).





puter(Comp,Sect,put(Comp,Sect)).

putlist(Comp,[Possible|T],Result,[Put|Result]):-puter(Comp,Possible,Put).
putlist(Comp,[_|T],Result,Res):-putlist(Comp,T,Result,Res).









putlister([],_,List,List).
putlister([Comp|CompRest],Possible,List,Result):-putlist(Comp,Possible,List,Put),putlister(CompRest,Possible,Put,Result).

change([],[]).
change([H|T],[H|Result]):-change(T,Result).







helper([],_,_,[],List,Result):-reverse(List,Result).
helper([Comp|CompRest],ConstList,SectionList,NewSectionList,List,Result):-isouter(Comp,ConstList),!,outer(SectionList,SectionList,Outer),putlist(Comp,Outer,List,PutList),member(put(Comp,Sect),PutList),delete(SectionList,Sect,NewSectionList),helper(CompRest,ConstList,NewSectionList,NSL,PutList,Result).

helper([Comp|CompRest],ConstList,SectionList,NewSectionList,List,Result):-isclose_to(Comp,ConstList,Adj),not(member(put(Adj,_),List)),!,putlist(Comp,SectionList,List,PutList),member(put(Comp,Sect),PutList),delete(SectionList,Sect,NewSectionList),helper(CompRest,ConstList,NewSectionList,NSL,PutList,Result).

helper([Comp|CompRest],ConstList,SectionList,NewSectionList,List,Result):-isclose_to(Comp,ConstList,Adj),member(put(Adj,PutSection),List),!,adjacentlist(PutSection,SectionList,AdjList),putlist(Comp,AdjList,List,PutList),member(put(Comp,Sect),PutList),delete(SectionList,Sect,NewSectionList),helper(CompRest,ConstList,NewSectionList,NSL,PutList,Result).



helper([Comp|CompRest],ConstList,SectionList,NewSectionList,List,Result):-putlist(Comp,SectionList,List,PutList),member(put(Comp,Sect),PutList),delete(SectionList,Sect,NewSectionList),helper(CompRest,ConstList,NewSectionList,NSL,PutList,Result).










