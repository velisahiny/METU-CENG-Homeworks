#include "GameEngine.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE

*/
#include<iostream>
/*class GameEngine {
private:
uint currentRound;
Board board;*/
/**
 * Constructor.
 *
 * GameEngine "owns" these players.
 * GameEngine also "owns" the vector.
 *
 * @param boardSize The side length of the board.
 * @param players All players to participate in the game.
 */
GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players):board(boardSize,players){
  currentRound=1;
  id_list = new int[players->size()];
  int i=0;
  for(Player *p: *players ){
    id_list[i] = p->getID();
    i++;
  }

}
GameEngine::~GameEngine(){
  delete[] id_list;
  std::vector<Player *> * players = board.getplayers();
  for(Player * p : *players) {
      delete p;
    }
  players->clear();
  delete players;

}

const Board& GameEngine::getBoard() const{
    return board;
}

    /**
     * Indexing.
     *
     * Find the player with given ID.
     *
     * nullptr if not exists.
     *
     * @param id ID of the player.
     * @return The player with given ID.
     */
Player* GameEngine::operator[](uint id) const{
  return board.find(id);
}

    /**
     * Decide whether the game is finished.
     *
     * @return true if there is only 1 player (alive), on top of the hill; or there are 0 players. False otherwise.
     */
bool GameEngine::isFinished() const{
  if(board.Size()==0){
    return true;
  }
  Coordinate coord = Coordinate(board.getHill(),board.getHill());
  if(board.Size()==1){
    Player* p = board[coord];
    if (p){
        return true;
    }
  }
  return false;
}

    /**
     * Take turn for every player.
     *
     * How-to:
     * - Announce turn start (cout).
     * Example: -- ROUND 1 START --
     * - board.updateStorm(currentRound)
     * - For every player (sorted according to their IDs) that isn't dead (HP <= 0):
     *      - takeTurnForPlayer(player).
     * - Announce turn end (cout).
     * Example: -- ROUND 1 END --
     */
void GameEngine::takeTurn(){
  std::cout << "-- START ROUND "<<currentRound<<" --" << '\n';
  //std::cout << "-- ROUND "<<currentRound<<" START --" << '\n';
  board.updateStorm(currentRound);
  std::vector<Player*>* players = board.getplayers();
  //std::cout << "SİZE: "<<players->size() << '\n';
  Player * p;
  /*for(Player *player : *players){
    p = player;
    takeTurnForPlayer(p->getID());
  }*/
  int k=0;
  int current;
  int size = players->size();
  for(int i=0; i<size ; i++ ){
    current =id_list[i];
    k = i;
    if(k >= players->size()){
      k = players->size()-1;
    }
    p =  (*players)[k];
    while(  (*players)[k]->getID() != current ){
      if(k==0){
        break;
      }
      k--;
    }
    if( (*players)[k]->getID() == current ){
        p =  (*players)[k];
        takeTurnForPlayer(p->getID());
      }
  }//for ends here
  delete[] id_list;
  id_list = new int[players->size()];
  int m=0;
  for(Player *p: *players ){
    id_list[m] = p->getID();
    m++;
  }
      //indexi küçült bak esk indexe bulursan ya da 0 sa eşitle

  std::cout << "-- END ROUND "<<currentRound<<" --" << '\n';

  //std::cout << "-- ROUND "<<currentRound<<" END --" << '\n';
  currentRound++;
}

    /**
     * The most important (algorithm-wise) method.
     *
     * How-to:
     * - Get player with ID. Return NOOP if not exists.
     * - Get player's priority list.
     * - Get player's visibility from the board (visibleCoordsFromCoord).
     *
     * - If the player is in the storm (isStormInCoord), announce the damage and give player stormDamage.
     * - Example: Tracer01(10) is STORMED! (-10)
     *
     * - If dead, announce the death, remove player from the board/list/anywhere, and return NOOP.
     * - Example: Tracer01(0) DIED.
     *
     * - For MOVE in player's priority list:
     *          - If the MOVE is NOOP:
     *              - return NOOP.
     *          - Else if the MOVE is ATTACK:
     *              - Get all players that this player can attack (board[coord] for each in visibilityCoords).
     *              - If none, continue.
     *              - Else:
     *                  - Pick the one with most priority (lowest ID).
     *                  - isPlayerDead = player.attackTo(thatPlayer).
     *                  - if isPlayerIsDead:
     *                      - announce the death.
     *                      - remove thatPlayer from the board/list/anywhere.
     *                  - return ATTACK.
     *          - Else (UP/DOWN/LEFT/RIGHT):
     *              - calculateCoordWithMove(move).
     *              - If the new coordinate is different than the player's (meaning it's able to do that move)
     *              AND the player is getting closer to the hill;
     *                  - player.executeMove(MOVE).
     *                  - return MOVE.
     *              - Else:
     *                  - continue.
     *
     * // If the priority list is exhausted;
     * return NOOP.
     *
     * @param player Player ID to move.
     * @return move Decided move.
     */
Move GameEngine::takeTurnForPlayer(uint playerID){
  Player* p = (*this)[playerID];

  if(!p){
    return NOOP;
  }
  else{
    std::vector<Move> pList = p->getPriorityList();
    Coordinate pcoord = p->getCoord();
    std::vector<Coordinate> visible = board.visibleCoordsFromCoord(pcoord);
    if(board.isStormInCoord(pcoord)){
        int stormDamage= Entity::stormDamageForRound(currentRound);
        std::cout <<p->getFullName()<<"("<<p->getHP()<<")"<<" is STORMED! (-"<<stormDamage<< ")"<< '\n';
        p->setHP(p->getHP()-stormDamage);

    }
    if(p->isDead()){
      std::cout <<p->getFullName()<<"("<<p->getHP()<<") DIED."<<'\n';
      std::vector<Player* >* players = board.getplayers();
      std::vector<Player* >::iterator it;
      for(it = players->begin(); it != players->end();++it){
        if((*it)->getID()==p->getID()){
          players->erase(it);
          delete p;
          return NOOP;
        }
      }//for ends here

    }//dead ends here
    for(int i=0;i<pList.size();i++ ){
      if(pList[i] == NOOP){
        return NOOP;
      }
      else if(pList[i]==ATTACK){
          std::vector<Coordinate> visible = board.visibleCoordsFromCoord(p->getCoord());
          std::vector<Player* > visibleplayers ;
          for(int i = 0; i<visible.size();i++){
            if(board[visible[i]])
              visibleplayers.push_back(board[ visible[i] ]);
          }

          if(visibleplayers.size()==0){
              continue ;
          }
          int lowestid = visibleplayers[0]->getID();
          Player * lowestplayer = visibleplayers[0];

          for(int i = 0; i<visibleplayers.size();i++){
              if(lowestid>( visibleplayers[i]->getID() ) ){
                lowestid = visibleplayers[i]->getID();
                lowestplayer = visibleplayers[i];
              }
          }

          bool isPlayerDead = p->attackTo(lowestplayer);
          if(isPlayerDead){
            std::cout <<lowestplayer->getFullName()<<"("<<lowestplayer->getHP()<<") DIED."<<'\n';
            std::vector<Player* >* players = board.getplayers();
            std::vector<Player* >::iterator it ;
            for(it = players->begin(); it != players->end();++it){
              if((*it)->getID()==lowestplayer->getID()){
                players->erase(it);
                delete lowestplayer;
                return ATTACK;
              }
            }//for ends here
          }
          return ATTACK;
      }
    else{
      Coordinate calculatedcoord = board.calculateCoordWithMove(pList[i],pcoord);
      if(calculatedcoord != pcoord){
        Coordinate hillcoord = Coordinate(board.getHill(),board.getHill());
        if( (calculatedcoord-hillcoord) < (pcoord-hillcoord) ){
          p->executeMove(pList[i]);
          return pList[i];
        }
      }
      else{
        continue;
      }

    }

    }//for ends here

    return NOOP;
  }//else ends here
}

    /**
     * Find the winner player.
     *
     * nullptr if there are 0 players left, or the game isn't finished yet.
     *
     * @return The winner player.
     */
Player * GameEngine::getWinnerPlayer() const{
  std::vector<Player *> * players = board.getplayers();
  if(players->size()==0){
    return nullptr;
  }
  if(!isFinished()){
    return nullptr;
  }
  if(board.Size()==1){
    Player* p = ( *( board.getplayers() ) )[0];
    if (p){
        return p;
    }
    else{
      return nullptr;
    }
  }
}
