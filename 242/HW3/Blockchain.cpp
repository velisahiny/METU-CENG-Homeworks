#include "Blockchain.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include <iostream>
#include <iomanip>
#include "Utilizer.h"
#include "Koin.h"
#
/**
 * Constructor.
 *
 * @param id The ID of the Blockchain.
 */
Blockchain::Blockchain(int id):id(id){
  this->head = nullptr;
  this->sf = false;
  tail_id = -1;
  fork = NULL;
  forked=false;
}
/**
 * Secondary Constructor.
 *
 * Important: Blockchain "owns" this Koin.
 *
 * @param id The ID of the Blockchain.
 * @param head The starting point of the Blockchain.
 */
Blockchain::Blockchain(int id, Koin *head):id(id) {
  this->head = head;
  this->sf=false ;
  tail_id = -1;
  fork = NULL;
  forked=false;
}



/**
 * Copy Constructor.
 *
 * The head should be deep copied.
 *
 * @param rhs The blockchain to be copied.
 */
Blockchain::Blockchain(const Blockchain& rhs):id(rhs.id){
  this->head = new Koin  ( *(rhs.getHead() ) ) ;
  this->sf =false ;
  tail_id = -1;
  fork = NULL;
  forked=false;
}
/**
 * Move Operator.
 *
 * RHS will relinquish the rights of the headKoin to LHS.
 * LHS's ID will not (cannot) be changed.
 *
 * Careful about memory-leaks!
 *
 * @param rhs The blockchain to be moved into this blockchain.
 * @return The modified blockchain.
 */
Blockchain& Blockchain::operator=(Blockchain&& rhs) noexcept {
    Koin * prev= nullptr;
    fork = NULL;
    Koin * tmp = this->head;
    while(tmp!= NULL){
      prev = tmp;
      tmp = (*tmp).getNext();
      delete prev;
    }
    this->head = rhs.getHead();
    rhs.head = NULL;
    return *this ;

}
/**
 * No assignment with const rhs.
 *
 * @param rhs -noNeed-
 * @return -noNeed-
 */

Blockchain::~Blockchain(){
  if(this->head == NULL){
    return;
  }
  else{
    Koin* tmp = this->head;
    Koin* prev= NULL;
    tmp = tmp->getNext();
    delete head;
    head = NULL;
    while(tmp!=NULL){
      Koin* prev = tmp;
      tmp=tmp->getNext();
      delete prev;
    }
  }

  /*if(forked){//küçük blockchain ise

    while(head!= NULL){
      --(*this);

    return;
  }
  else{//büyük blockchain ise
  Koin * tmp = this->head;
  while(tmp!= NULL){
    Koin * prev = tmp;
    tmp = tmp->getNext();
    delete prev;
  }
  this->head = NULL ;
}*/
//burası sondu
/*  Koin* tmp = this->head;
  Koin*prev=NULL;
  while(tmp!=NULL) {
    prev = tmp;
    tmp=tmp->getNext();
    std::cout << "sildim"<<prev->getValue()<< '\n';
    delete prev;
  }
*/
}

int Blockchain::getID() const{
  return this->id;
}
Koin* Blockchain::getHead() const{
  return this->head;
}

/**
 * Calculate the value of the blockchain.
 *
 * @return Total value of the Koins in the blockchain.
 */
double Blockchain::getTotalValue() const{
  double sum =0;
  Koin * tmp = this->head;
  while(tmp!= NULL){
    sum += (*tmp).getValue();
    tmp = (*tmp).getNext();
  }
  return sum;
}

/**
 * Calculate the length of the koins end-to-end.
 *
 * @return The length of the blockchain.
 */
long Blockchain::getChainLength() const{
  long length = 0;
  Koin * tmp = this->head;
  while(tmp!= NULL){
    length++;
    tmp = (*tmp).getNext();
  }
  return length;
}

/**
 * Prefix addition.
 *
 * Mine and insert the mined Koin at the end of the chain.
 */
void Blockchain::operator++(){
  Koin* minedKoin =  new Koin(Utilizer::fetchRandomValue());
  //Koin * tmp = this->head;
  Koin* tmp = this->tail();
  if(tmp == NULL){
    this->head = minedKoin;
    head->setNext(NULL);
    return;
  }
  else{
    /*while((*tmp).getNext() != NULL){
      tmp = (*tmp).getNext();
    }*/
    tmp->setNext(minedKoin);
    tmp->getNext()->setNext(NULL);
  }
}

/**
 * Prefix decrement.
 *
 * Remove/destroy the last inserted Koin to the chain.
 * no-op if the head is nullptr.
 *
 * Important note:
 *
 * If a blockchain is created by a soft fork, its head cannot be deleted.
 */
void Blockchain::operator--(){
  if (this->head == nullptr){
    return;
  }
  Koin* tmp = this->head;
  Koin* prev = NULL;
  while((*tmp).getNext()!=NULL){
    prev = tmp;
    tmp = (*tmp).getNext();
  }
  if(sf == true){/*büyük blockchain*/
    if(tmp->getValue() == tail_id){
      return;
    }
  }
  if(tmp == this->head ){
    if(forked){/*küçük chain*/
      fork->resetsf();
    }
    delete head;
    //delete tmp;
    fork = NULL ;
    //tmp =nullptr;
    this->head=nullptr;
    return;
  }
  if(prev){
    prev->setNext(NULL);
  }
  delete tmp;
  return;

}

/**
 * Multiplication overload.
 *
 * Multiply the value of every Koin in the blockchain.
 *
 * @param multiplier The value to be multiplied with the values of the Koins.
 * @return The current blockchain.
 */
Blockchain& Blockchain::operator*=(int multiplier){
    Koin* tmp = this->head;
    while(tmp!= NULL ){
      (*tmp) *= multiplier;
      tmp = (*tmp).getNext();
    }
    return *this;
}

/**
 * Division.
 *
 * Divide the value of every Koin in the blockchain.
 *
 * @param divisor The value to divide the values of the Koins.
 * @return The current blockchain.
 */
Blockchain& Blockchain::operator/=(int divisor){
  Koin* tmp = this->head;
  while(tmp!= NULL ){
    (*tmp) /= divisor;
    tmp = (*tmp).getNext();
  }
  return *this;
}

/**
 * Stream overload.
 *
 * What to stream:
 *
 * Block -blockchainID-: headKoinStream (see Koin for stream example) (-totalValue-)
 *
 * Example:
 *
 * Block 6: 0.707--0.390--0.984--|(2.080)
 *
 * Edge case : Blockchain without head
 *
 * Block -blockchainID-: Empty.
 *
 * @param os Stream to be used.
 * @param blockchain Blockchain to be streamed.
 * @return The current stream.
 */
 std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain){
   if(blockchain.getHead()==NULL){
     os<<"Block "<< blockchain.getID()<<": Empty.";
     return os;
   }
   os<<"Block "<< blockchain.getID()<<": ";
     os <<*(blockchain.getHead() );
   os<<"(";
   os<<std::setprecision(Utilizer::koinPrintPrecision())<<std::fixed<<blockchain.getTotalValue()<<")";

   return os;
 }
 void Blockchain::setSF(){
   sf = true;
 }
 Koin* Blockchain::tail(){

   Koin* tmp = this->head;
   if (this->head== NULL){
     return head;
   }
   else{
     while(tmp->getNext()!=NULL){
       tmp = tmp->getNext();
     }
     return tmp;
   }
 }
 void Blockchain::setTail_id(double val){
   this->tail_id = val;
   return;
 }
 void Blockchain::setforked(){
   forked =true;
 }
 void Blockchain::forkedBC(Blockchain* BC){
   fork = BC;
   return;
 }
 void Blockchain::resetsf(){
   sf= false;
   return;
 }
