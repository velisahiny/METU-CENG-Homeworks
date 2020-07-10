#include "Pacifist.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include<iostream>
Pacifist::Pacifist(uint id, int x, int y):Player(id,x,y){
  name = "Pacifist";
  PriorityList = {UP, LEFT, DOWN, RIGHT};
  armor = METAL;
  weapon = NOWEAPON;
  HP = 100;
}
// Name     : Pacifist
// Priority : { UP, LEFT, DOWN, RIGHT }

// Armor    : METAL
// Weapon   : NOWEAPON
// HP       : 100
Armor Pacifist::getArmor() const{
  return armor;
}
Weapon Pacifist::getWeapon() const{
  return weapon;
}
std::vector<Move> Pacifist::getPriorityList() const {
  return PriorityList;
}
const std::string Pacifist::getFullName() const {
  return name + this->getBoardID();
}
Color::Code Pacifist::getColorID() const{
  return Color::FG_GREEN;
}
Pacifist::~Pacifist(){
  PriorityList.clear();
}
