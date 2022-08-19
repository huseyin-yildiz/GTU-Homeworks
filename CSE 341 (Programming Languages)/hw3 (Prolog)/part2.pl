% knowledge base

flight(istanbul,izmir,2).           % fact: Istanbul and Izmir has a flight with cost 2.
flight(canakkale,erzincan,6).
flight(izmir,antalya,2).
flight(erzincan,antalya,3).
flight(istanbul,ankara,1).
flight(izmir,ankara,6).
flight(antalya,diyarbakir,4).
flight(istanbul,rize,4).
flight(ankara,van,4).
flight(ankara,rize,5).
flight(van,gaziantep,3).
flight(ankara,diyarbakir,8).


% rules


route(X,Y,C) :- flight(X,Y,C).
route(X,Z,C) :- flight(X,Y,C1), route(Y,Z,C2), C is C1+C2.

