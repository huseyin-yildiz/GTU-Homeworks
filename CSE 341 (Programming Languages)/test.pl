even(X) :- mod(X,2) =:= 0.


%even_between(A,B,X) :- X is (A+1) , X = B, even(X)   .
%even_between(A,B,X) :- A<X , B>=X, even(X), A1 is A+1,even_between(A1,B,X) .

even_between(A,B,X) :- between(A, B, X), even(X) .