#include "Koin.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include <iostream>
#include <iomanip>
#include "Utilizer.h"
Koin::Koin(double value){
  this->value = value;
  this->next = NULL;
}
Koin::Koin(const Koin& rhs){
  this->value = rhs.getValue();
  this->next = rhs.getNext();
}
Koin& Koin::operator=(const Koin& rhs){
  this->value = rhs.getValue();
  this->next = rhs.getNext();
  return *this;
}
Koin::~Koin(){/*
  next=nullptr;*/
}
double Koin::getValue() const {
  return this->value;
}
Koin* Koin::getNext()const{
  return this->next;
}
void Koin::setNext(Koin *next) {
  this->next = next;
}
bool Koin::operator==(const Koin& rhs) const{
  int difference = (this-> value) - rhs.getValue();
  int absdifference = difference > 0 ? difference : (-difference);
  if ( absdifference > Utilizer::doubleSensitivity()   )
      return false;
  else if(this->next == rhs.getNext()) {
    if (this->next == NULL)
      return true;
    return  (*(this->next)) == *(rhs.getNext());
  }
  else {
    return false;
  }
}

bool Koin::operator!=(const Koin& rhs) const{
  if (*this == rhs)
    return false;
  else
    return true;
}
Koin& Koin:: operator*=(int multiplier){
  this->value *= multiplier;
  return *this;
}
Koin& Koin:: operator/=(int multiplier){
  this->value /= multiplier;
  return *this;
}
std::ostream& operator<<(std::ostream& os, const Koin& koin){

  Koin* temp = koin.getNext();
  os<<std::setprecision(Utilizer::koinPrintPrecision())<<std::fixed<<koin.getValue();
  os<<"--";
  if (temp!=NULL){
    while(temp!= NULL){
      os <<std::setprecision(Utilizer::koinPrintPrecision())<<std::fixed<<temp->getValue();
      os<<"--";
      temp = temp->getNext();
  }
}
    os<< "|";
  return os;
}
