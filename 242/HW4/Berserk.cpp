#include "Berserk.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include<iostream>

Berserk::Berserk(uint id, int x, int y):Player(id,x,y){
  name = "Berserk";
  PriorityList = {ATTACK, UP, LEFT, DOWN, RIGHT };
  armor = WOODEN;
  weapon = PISTOL;
  HP = 100;
}


Armor Berserk::getArmor() const{
  return armor;
}
Weapon Berserk::getWeapon() const {
  return weapon;
}

/**
 * Every player has a different priority move list.
 * It's explained in the Players' header.
 *
 * @return The move priority list for the player.
 */
std::vector<Move> Berserk::getPriorityList() const {
  return PriorityList;
}

/**
 * Get the full name of the player.
 *
 * Example (Tracer with ID 92) = "Tracer92"
 * Example (Tracer with ID 1)  = "Tracer01"
 *
 * @return Full name of the player.
 */
const std::string Berserk::getFullName() const {
  return name + this->getBoardID();
}

/**
 * Return different colors for different Player classes (override!).
 *
 * Note: This method is optional. You may leave this as-is.
 *
 * @return The associated color code with the class.
 */
Color::Code Berserk::getColorID() const { return Color::FG_YELLOW; }
Berserk::~Berserk(){
  PriorityList.clear();
}
