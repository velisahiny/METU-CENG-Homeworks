#include "Miner.h"
#include <iomanip>
#include "Utilizer.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

/**
 * Find the next ID for a newly created/forked blockchain.
 * Blockchain IDs are unique belonging to Miner, and strictly increasing (started from 0).
 *
 * @return The next available ID for a new blockchain.
 */

int Miner::getNextAvailableBlockchainID() const{
  return nextID;
}

/**
 * Constructor.
 *
 * @param name Name of the miner.
 */
Miner::Miner(std::string name){
  this->name = name;
  size=0;
  nextID=0;
}
Miner::~Miner(){
  long i = 0;
  Blockchain* tmp= nullptr;
  while(i<size){
    tmp= BCvector[i];
    delete tmp;
    i++;
    //BCvector.pop_back();
  }
  BCvector.clear();
}

/**
 * Create a new blockchain with the next available ID.
 */
void Miner::createNewBlockchain(){
  Blockchain* BC = new Blockchain(nextID);
  BCvector.push_back(BC);
  size +=1;
  nextID+=1;
}

/**
 * Start mining with the given count.
 * For every count, a single Koin will be produced in each blockchain.
 *
 * Operations must be ordered according to the blockchainIDs.
 *
 * @param cycleCount The count which the blockchains will be run for.
 */
void Miner::mineUntil(int cycleCount){
  for (int i = 0; i < cycleCount; i++) {
    for(int y =0; y<size; y++){
      ++(*BCvector[y]);
    }
  }
  return;
}

/**
 * Start de-mining with the given count.
 * For every count, the last Koin in the blockchain must be destroyed.
 * no-op for Blockchain if it doesn't have any (left).
 *
 * Operations must be ordered according to the blockchainIDs.
 *
 * @param cycleCount The count which the blockchains will be run for.
 */
void Miner::demineUntil(int cycleCount){
  for (int i = 0; i < cycleCount; i++){
    for(int y =0; y<size; y++){
      --(*BCvector[y]);
    }
  }
  return;
}

/**
 * Calculate the value of the miner, which is the sum of the blockchains' value.
 *
 * Soft-forks DO NOT constitute for the total value of the miner.
 *
 * @return Total value of the miner.
 */
double Miner::getTotalValue() const{
  double sum = 0;
  for(int i = 0 ; i<size ; i++){
    sum += (*BCvector[i]).getTotalValue();
  }

}

/**
 * Return the count of the blockchains.
 *
 * @return Total count of the blockchains.
 */
long Miner::getBlockchainCount() const{
  return size;
}

/**
 * Indexing.
 *
 * Find the blockchain with the given id.
 *
 * @return The blockchain with the given id. nullptr if not exists.
 */
Blockchain* Miner:: operator[](int id) const{
  if(id<size){
    return BCvector[id];
  }
  else{
    return nullptr;
  }
}

/**
 *  Shallow-copy the blockchain with given ID.
 *
 *  How-To:
 *  1) Fetch the blockchain in the miner with given ID.
 *  2) If not exists, no-op.
 *  3) Fetch the next available ID for the blockchain.
 *  4) Create a new blockchain with the new ID, and with the head as the original of the last Koin of the blockchain.
 *  5) Hence, a modification to the newly created blockchain will also affect the old blockchain, but only ...
 *  6) ... after the head (head included). And vice versa.
 *  7) Save the newly created blockchain in the miner.
 *
 *  @param blockchainID The blockchain ID to be forked.
 *
 *  @return true if the blockchain with given ID exists, otherwise false.
*/
bool Miner::softFork(int blockchainID){
  Blockchain* fetchedBC = BCvector[blockchainID];
  if (fetchedBC){
    Koin* newhead = fetchedBC->tail();
    fetchedBC->setTail_id(newhead->getValue());
    Blockchain* newBC = new Blockchain(nextID,newhead);
    fetchedBC->setSF();
    newBC->setforked();
    newBC->forkedBC(fetchedBC);
    BCvector.push_back(newBC);
    size+=1;
    nextID+=1;
    return true;
  }
  else{
    return false;
  }
  return false;
}

/**
 *  Deep-copy the blockchain with given ID.
 *
 *  How-To:
 *  1) Fetch the blockchain in the miner with given ID.
 *  2) If not exists, no-op.
 *  3) Else, fetch the next available ID for the blockchain.
 *  4) Create a new blockchain with the new ID, and with the head as a copy of the last Koin of the blockchain.
 *  5) Any changes made in the new blockchain will NOT affect the old blockchain. And vice versa.
 *  6) Save the newly created blockchain in the miner.
 *
 *  @param blockchainID The blockchain ID to be forked.
 *
 *  @return true if the blockchain with given ID exists, otherwise false.
*/
bool Miner::hardFork(int blockchainID){
  Blockchain* fetchedBC = BCvector[blockchainID];
  if(fetchedBC){
    Koin* newhead = new Koin( fetchedBC->tail()->getValue() );
    newhead->setNext(nullptr);
    Blockchain* newBC = new Blockchain(nextID,newhead);
    BCvector.push_back(newBC);
    size+=1;
    nextID+=1;
    return true;
  }
  else{
    return false;
  }
}

/**
 * Stream overload.
 *
 * What to stream:
 *
 * -- BEGIN MINER --
 * Miner name: -minerName-
 * Blockchain count: -getBlockchainCount()-
 * Total value: -getTotalValue()-
 *
 * Block -blockchainID-: headKoin (see Blockchain for stream example)
 * .
 * .
 * .
 * Block -lastBlockchainID-: headKoin (see Blockchain for stream example)
 *
 * -- END MINER --
 *
 * Example:
 *
 * -- BEGIN MINER --
 * Miner name: BTCMiner
 * Blockchain count: 5
 * Total value: 2.519
 *
 * Block 0: 0.491--0.103--0.529--|(1.123)
 * Block 1: Empty.
 * Block 2: Empty.
 * Block 3: Empty.
 * Block 4: 0.400--0.924--0.072--|(1.396)
 *
 * -- END MINER --
 *
 * @param os Stream to be used.
 * @param miner Miner to be streamed.
 * @return The current stream.
 */
std::ostream& operator<<(std::ostream& os, const Miner& miner){
  os<<"-- BEGIN MINER --"<<"\n";
  os<<"Miner name: "<<miner.name <<"\n";
  os<<"Blockchain count: "<<miner.size<<"\n";
  os<<"Total value: "<<std::setprecision(Utilizer::koinPrintPrecision())<<std::fixed<<miner.getTotalValue()<<"\n";
  os<<"\n";

  for (long i = 0; i < miner.size; i++) {
    os<<*(miner.BCvector[i]);
    os<<"\n";
  }
os<<"\n";
os<<"-- END MINER --"<<"\n";
return os;
}
