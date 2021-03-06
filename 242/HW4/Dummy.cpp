#include "Dummy.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include<iostream>
Dummy::Dummy(uint id, int x, int y):Player(id,x,y){
  name = "Dummy";
  PriorityList = { NOOP };
  armor = NOARMOR;
  weapon = NOWEAPON;
  HP = 1000;
}
// Name     : Dummy
// Priority : { NOOP }

// Armor    : NOARMOR
// Weapon   : NOWEAPON
// HP       : 1000
Armor Dummy::getArmor() const{
  return armor;
}
Weapon Dummy::getWeapon() const{
  return weapon;
}
std::vector<Move> Dummy::getPriorityList() const {
  return PriorityList;
}
const std::string Dummy::getFullName() const {
  return name + this->getBoardID();
}
Color::Code Dummy::getColorID() const{
  return Color::FG_DEFAULT;
}
Dummy::~Dummy(){
  PriorityList.clear();
}
