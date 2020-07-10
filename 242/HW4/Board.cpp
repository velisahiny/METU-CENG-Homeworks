#include "Board.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
/*class Board {
private:
    const uint boardSize;
    std::vector<Player *> *players;*/
Board::Board(uint boardSize, std::vector<Player *> *players):boardSize(boardSize){
  this->players = players;
  Hill = boardSize/2 ;
  Storm = boardSize/2;
}
Board::~Board(){
  /*for(Player *player : *players) {
      delete player;
  }

  players->clear();

  delete players;*/
  //No need for destructor
  /*
  for (int i = 0; i < (*players).size(); i++) {
    Player* tmp = (*players)[i];
    delete tmp;
  }
  (*players).clear();
  delete players;*/
}

uint Board::getSize() const{
  return boardSize;
}

bool Board::isCoordInBoard(const Coordinate& coord) const{
  Coordinate bottom_limit = Coordinate(0,0);
  Coordinate upper_limit = Coordinate(boardSize-1,boardSize-1);
  if(coord<bottom_limit)
    return false;
  else if(coord < upper_limit || coord == upper_limit )
    return true;
}

bool Board::isStormInCoord(const Coordinate &coord) const{
  if(Storm + Hill + 1 ==boardSize){
    return false;
  }
  Coordinate bottom_limit = Coordinate(Hill-Storm,Hill-Storm);
  Coordinate upper_limit = Coordinate(Hill+Storm,Hill+Storm);
  if (coord.x<=upper_limit.x && coord.y <= upper_limit.y){
    if(coord.x>=bottom_limit.x && coord.y >= bottom_limit.y ){
      return false;
    }
  }
  return true;
  /*if(coord<bottom_limit)
    return true;
  else if( !(coord < upper_limit) && coord !=upper_limit )
    return true;
  else
    return false;*/
}

bool Board::isCoordHill(const Coordinate& coord) const{
  return coord == Coordinate(Hill,Hill);
}

Player * Board::operator[](const Coordinate& coord) const{
  Player* tmp = nullptr;
  for(int i = 0; i<(*players).size(); i++ ){
    if( (*players)[i]->getCoord() == coord)
        return (*players)[i];
  }
  return nullptr;
}

Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const{
  Coordinate newcoord = coord+move;
  if(isCoordInBoard(newcoord) && coord != newcoord && !( (*this)[newcoord] ) )
      return newcoord;
  return coord;
}


std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const{
  std::vector<Coordinate> v;
  if(isCoordInBoard(coord)){
    Coordinate upcoord = coord+UP;
    Coordinate downcoord = coord + DOWN;
    Coordinate leftcoord = coord + LEFT;
    Coordinate rightcoord = coord + RIGHT;
    if(isCoordInBoard(upcoord))
      v.push_back(upcoord);
    if(isCoordInBoard(downcoord))
      v.push_back(downcoord);
    if(isCoordInBoard(leftcoord))
      v.push_back(leftcoord);
    if(isCoordInBoard(rightcoord))
      v.push_back(rightcoord);
  }
  return v;
}


void Board::updateStorm(uint currentRound){
  Storm = Hill - Entity::stormWidthForRound(currentRound);
  if(Storm < 0)
    Storm = 0;
  }

Player * Board::find(uint id) const {
  Player* tmp = nullptr;
  for(int i = 0; i<(*players).size(); i++ ){
    if( (*players)[i]->getID() == id)
        return (*players)[i];
  }
  return nullptr;
}

int Board::Size() const {
  return players->size();
}
int Board::getHill() const {
  return Hill;
}
  std::vector<Player*>* Board::getplayers() const {
  return players;
}
