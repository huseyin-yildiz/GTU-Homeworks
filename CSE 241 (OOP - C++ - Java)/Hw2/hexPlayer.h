// These functions is for computer ai
// and they commented on hexPlayer.cpp

 location goAhead(movement myMovement,location fromThis);							
 bridge findBridge(const location firsLocation,const location secondLocation);							
 moving move(game & myGame);
 bool isContainsDirection(std::list<movement> directions, movement direction);
 location firstMovement(game & myGame);								
std::list<location> findConnections(location myLocation,short boardSize);
