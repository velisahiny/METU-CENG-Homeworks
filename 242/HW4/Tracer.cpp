#include "Tracer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include<iostream>
Tracer::Tracer(uint id, int x, int y):Player(id,x,y){
  name = "Tracer";
  PriorityList = {UP, LEFT, DOWN, RIGHT, ATTACK};
  armor = BRICK;
  weapon = SHOVEL;
  HP = 100;
}

// Name     : Tracer
// Priority : { UP, LEFT, DOWN, RIGHT, ATTACK }

// Armor    : BRICK
// Weapon   : SHOVEL
// HP       : 100

// DO NOT MODIFY THE UPPER PART
// ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
Armor Tracer::getArmor() const{
  return armor;
}
Weapon Tracer::getWeapon() const{
  return weapon;
}
std::vector<Move> Tracer::getPriorityList() const {
  return PriorityList;
}
const std::string Tracer::getFullName() const {
  return name + this->getBoardID();
}
Color::Code Tracer::getColorID() const{
  return Color::FG_YELLOW;
}
Tracer::~Tracer(){
  PriorityList.clear();
}
