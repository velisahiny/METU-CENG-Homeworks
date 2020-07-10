#include <vector>
#include "TestablePlayer.h"
#include "Tracer.h"
#include "Berserk.h"
#include "Ambusher.h"
#include "Pacifist.h"
#include "Dummy.h"

void TestablePlayer::runInternal() {

    // Phase 1 : Common Player Methods

    // Phase 1-1 : ID/Coord/BoardID

    Player *berserk = new Berserk(0, 1, 2);
    if(berserk->getID() != 0){
      std::cout << "0" << '\n';
        currentGrade -= 1;
      }
    Coordinate berserkCoord = berserk->getCoord();
    if(berserkCoord.x != 1 || berserkCoord.y != 2){
      std::cout << "1" << '\n';
        currentGrade -= 1;
      }

    std::string berserkBoardID = berserk->getBoardID();

    if (berserkBoardID != "00"){
      std::cout << "2" << '\n';
        currentGrade -= 1;
      }

    // Phase 1-2 : executeMove

    // NOOP and ATTACK should not change the coordinates.
    berserk->executeMove(NOOP);
    berserk->executeMove(ATTACK);

    if(berserk->getCoord() != berserkCoord){
      std::cout << "3" << '\n';
        currentGrade -= 2;
      }

    // Print in executeMove.
    // Berserk00(100) moved DOWN.
    berserk->executeMove(DOWN);

    if(berserk->getCoord() != Coordinate(1, 3)){
      std::cout << "4" << '\n';
        currentGrade -= 2;
      }

    // Print in executeMove.
    // Berserk00(100) moved UP.
    berserk->executeMove(UP);

    if(berserk->getCoord() != berserkCoord){
      std::cout << "5" << '\n';
        currentGrade -= 2;
      }

    // Phase 1-3 : attackTo

    // Can a player attack itself?
    // Hope not! We do not condone suicide.
    berserk->attackTo(berserk);

    if(berserk->getHP() != 100){
      std::cout << "6" << '\n';
        currentGrade -= 1;
      }

    Player *anotherBerserk = new Berserk(1, 5, 6);

    // Print in attackTo.
    // Berserk00(100) attacked Berserk01(100)! (-15)
    berserk->attackTo(anotherBerserk);

    if(anotherBerserk->getHP() != 85){
      std::cout << "7" << '\n';
        currentGrade -= 2;
      }

    // Let's kill him.

    for(int i = 0; i < 6; i++) {
        if(anotherBerserk->isDead()){
          std::cout << "8" << '\n';
            currentGrade -= 1;
          }

        berserk->attackTo(anotherBerserk);
    }

    if(!anotherBerserk->isDead()){
      std::cout << "9" << '\n';
        currentGrade -= 1;
      }

    delete berserk;
    delete anotherBerserk;

    Player *playerToTest;

    // Phase 2 : Berserk

    playerToTest = new Berserk(1, 0, 0);
    this->checkPlayer(playerToTest, 100, WOODEN, PISTOL, "Berserk01", { ATTACK, UP, LEFT, DOWN, RIGHT });
    delete playerToTest;

    // Phase 3 : Tracer

    playerToTest = new Tracer(99, 0, 0);
    this->checkPlayer(playerToTest, 100, BRICK, SHOVEL, "Tracer99", { UP, LEFT, DOWN, RIGHT, ATTACK });
    delete playerToTest;

    // Phase 4 : Ambusher

    playerToTest = new Ambusher(42, 0, 0);
    this->checkPlayer(playerToTest, 100, NOARMOR, SEMIAUTO, "Ambusher42", { ATTACK });
    delete playerToTest;

    // Phase 5 : Pacifist

    playerToTest = new Pacifist(92, 0, 0);
    this->checkPlayer(playerToTest, 100, METAL, NOWEAPON, "Pacifist92", { UP, LEFT, DOWN, RIGHT });
    delete playerToTest;

    // Phase 6 : Dummy

    playerToTest = new Dummy(33, 0, 0);
    this->checkPlayer(playerToTest, 1000, NOARMOR, NOWEAPON, "Dummy33", { NOOP });
    delete playerToTest;
}

void TestablePlayer::checkPlayer(Player *player,
                                 int correctHP,
                                 Armor correctArmor,
                                 Weapon correctWeapon,
                                 const std::string& correctFullName,
                                 const std::vector<Move>& correctPriorityList) {
    if(player->getHP() != correctHP){
      std::cout << "10" << '\n';
        currentGrade -= 1;
      }

    if(player->getWeapon() != correctWeapon){
      std::cout << "11" << '\n';
        currentGrade -= 1;
      }
    if(player->getArmor() != correctArmor){
      std::cout << "12" << '\n';
        currentGrade -= 1;
      }

    if(player->getFullName() != correctFullName){
      std::cout << "13" << '\n';
        currentGrade -= 3;
      }
    if(player->getPriorityList() != correctPriorityList){
      std::cout << "14" << '\n';
        currentGrade -= 3;
      }
}
