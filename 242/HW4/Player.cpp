#include "Player.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include <iostream>
/*class Player {
protected:
    const uint id;
    Coordinate coordinate;

    int HP;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PROTECTED METHODS/PROPERTIES BELOW

public:*/
/**
 * Main Constructor.
 *
 * @param id The ID of the player. [0-100).
 * @param x X-coordinate of the player.
 * @param y Y-coordinate of the player.
 */
Player::Player(uint id, int x, int y):coordinate(x,y), id(id) {
}
Player::~Player(){
  PriorityList.clear();

}

uint Player::getID() const{
    return id;
}
const Coordinate& Player::getCoord() const{
    return coordinate;
}
int Player::getHP() const{
    return HP;
}
/**
 * Board ID is two-decimal ID for the Player.
 *
 * Player ID = 0, 91
 * Board ID = "00", "91"
 *
 * @return BoardID of the user.
 */
std::string Player::getBoardID() const{
    if(id>9)
        return std::to_string(id);
    else
        return "0"+std::to_string(id);
}
//Armor Player::getArmor() const {return armor;}
//Weapon Player::getWeapon() const{return weapon;}
/**
 * Every player has a different priority move list.
 * It's explained in the Players' header.
 *
 * @return The move priority list for the player.
 */
//std::vector<Move> Player::getPriorityList() const {return PriorityList;}

/**
 * Get the full name of the player.
 *
 * Example (Tracer with ID 92) = "Tracer92"
 * Example (Tracer with ID 1)  = "Tracer01"
 *
 * @return Full name of the player.
 */
//const std::string Player::getFullName() const {return name + this->getBoardID();}
/**
 * Decide whether the player is dead.
 *
 * @return true if the player's hp <= 0, false otherwise.
 */
bool Player::isDead() const{
    return HP<=0;
}
/**
 * Execute the given move for the player's coordinates.
 *
 * Important note: Priority list does NOT matter here.
 *
 * NOOP and ATTACK are no-op.
 *
 * Do not forget to print the move.
 * "-playerFullName(playerHP)- moved UP/DOWN/LEFT/RIGHT."
 *
 * "Tracer00(100) moved UP."
 *
 * @param move Move to make.
 */
void Player::executeMove(Move move){
    coordinate = coordinate+move;
    switch(move){
        case NOOP:
            break;
        case ATTACK:
            break;
        case UP:
            std::cout<<this->getFullName()<<"("<<this->getHP()<<") moved "<<"UP.\n";
            break;
        case DOWN:
            std::cout<<this->getFullName()<<"("<<this->getHP()<<") moved "<<"DOWN.\n";
            break;
        case LEFT:
            std::cout<<this->getFullName()<<"("<<this->getHP()<<") moved "<<"LEFT.\n";
            break;
        case RIGHT:
            std::cout<<this->getFullName()<<"("<<this->getHP()<<") moved "<<"RIGHT.\n";
            break;
    }
}

/**
 * Attack the given player, and decide whether the attacked player is dead.
 *
 * Important note: Priority list does NOT matter here.
 *
 * Formulae : RHS's HP -= max((LHS's damage - RHS's armor), 0)
 *
 * Do not forget to print the attack.
 *
 * "-lhsFullName(lhsHP)- attacked -rhsFullName(rhsHP)-! (-damageDone-)
 *
 * "Tracer00(100) attacked Tracer01(100)! (-10)"
 *
 * @param player Player to be attacked.
 * @return true if attacked player is dead, false otherwise.
 */
bool Player::attackTo(Player *player){
    if(player->getID() == this->getID() ){
      return false;
    }
    int damageDone = - std::max( Entity::damageForWeapon(weapon) - Entity::damageReductionForArmor(player->getArmor()), 0) ;
    std::cout<<this->getFullName()<<"("<<this->HP<<") ATTACKED "<<player->getFullName()<<"("<<player->getHP()<<")! ("<<damageDone<<")\n";
    player->setHP(player->getHP() + damageDone);

    return player->isDead();
}

/**
 * Return different colors for different Player classes (override!).
 *
 * Note: This method is optional. You may leave this as-is.
 *
 * @return The associated color code with the class.
 */
//Color::Code Player::getColorID() const { return Color::FG_DEFAULT; }


void Player::setHP(int hp){
    HP = hp;
}
