#include "Ambusher.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include<iostream>
Ambusher::Ambusher(uint id, int x, int y):Player(id,x,y){
  name = "Ambusher";
  PriorityList ={ ATTACK };
  armor = NOARMOR;
  weapon = SEMIAUTO;
  HP = 100;
}

// Name     : Ambusher
// Priority : { ATTACK }

// Armor    : NOARMOR
// Weapon   : SEMIAUTO
// HP       : 100
Armor Ambusher::getArmor() const {
  return armor;
}
Weapon Ambusher::getWeapon() const {
  return weapon;
}
std::vector<Move> Ambusher::getPriorityList() const {
  return PriorityList;
}
const std::string Ambusher::getFullName() const {
  return name + this->getBoardID();
}
Color::Code Ambusher::getColorID() const{
  return Color::FG_BLUE;
}
Ambusher::~Ambusher(){
  PriorityList.clear();
}
