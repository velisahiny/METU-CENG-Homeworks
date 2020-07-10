#include "TestableBoard.h"
#include "Board.h"
#include "BoardPrinter.h"
#include "Tracer.h"

#include <algorithm>

void TestableBoard::runInternal() {
    // Phase 1 : Mocking GameEngine
    uint boardSize = 3;

    Player *tracer1 = new Tracer(0, 0, 0);
    Player *tracer2 = new Tracer(1, 2, 1);

    // Summary:
    // 00----
    // --HH01
    // ------

    std::vector<Player *> *players = new std::vector<Player *>{ tracer1, tracer2 };

    Board board = Board(boardSize, players);

    if(board.getSize() != boardSize){
      std::cout << "0" << '\n';
        currentGrade -= 1;
      }
    // Phase 2 : isCoordInBoard

    Coordinate outOfBounds1 = Coordinate(-1, -1);
    Coordinate outOfBounds2 = Coordinate(3, 3);

    if(board.isCoordInBoard(outOfBounds1)){
      std::cout << "1" << '\n';
        currentGrade -= 1;
      }
    if(board.isCoordInBoard(outOfBounds2)){
      std::cout << "2" << '\n';
        currentGrade -= 1;
      }

    Coordinate inbound1 = Coordinate(0, 1);
    Coordinate inbound2 = Coordinate(2, 2);

    if(!board.isCoordInBoard(inbound1)){
      std::cout << "3" << '\n';
        currentGrade -= 1;
      }
    if(!board.isCoordInBoard(inbound2)){
      std::cout << "4" << '\n';
        currentGrade -= 1;
      }

    // Phase 3 : Indexing

    Player *shouldNotBeThere = board[Coordinate(0, 1)];
    Player *shouldBeOutOfBounds = board[Coordinate(100, 100)];

    if(shouldNotBeThere != nullptr){
      std::cout << "5" << '\n';
        currentGrade -= 1;
      }
    if(shouldBeOutOfBounds != nullptr){
      std::cout << "6" << '\n';
        currentGrade -= 1;
      }

    Player *findFirstTracer = board[tracer1->getCoord()];
    Player *findSecondTracer = board[tracer2->getCoord()];

    if(findFirstTracer == nullptr){
      std::cout << "7" << '\n';
        currentGrade -= 1;
      }
    if(findSecondTracer == nullptr){
      std::cout << "8" << '\n';
        currentGrade -= 1;
      }

    // Phase 4 : calculateCoordWithMove

    Coordinate tracer1CanDown = board.calculateCoordWithMove(DOWN, tracer1->getCoord());
    // tracer1 -> (0, 0)
    if (tracer1CanDown != Coordinate(0, 1)){
      std::cout << "9" << '\n';
        currentGrade -= 2;
      }

    Coordinate tracer1CannotUp = board.calculateCoordWithMove(UP, tracer1->getCoord());
    // tracer1 -> (0, 0)
    if (tracer1CannotUp != Coordinate(0, 0)){
      std::cout << "10" << '\n';
        currentGrade -= 2;
      }

    Coordinate attackCoord = board.calculateCoordWithMove(ATTACK, tracer1->getCoord());
    Coordinate noopCoord = board.calculateCoordWithMove(NOOP, tracer1->getCoord());
    if (attackCoord != tracer1->getCoord() || noopCoord != tracer1->getCoord()){
      std::cout << "11" << '\n';
        currentGrade -= 2;
      }

    // Phase 5 : visibleCoordsFromCoord

    auto shouldBeEmpty = board.visibleCoordsFromCoord(Coordinate(-1, 0));

    if(!shouldBeEmpty.empty()){
      std::cout << "12" << '\n';
        currentGrade -= 2;
      }

    auto firstTracerVisibility = board.visibleCoordsFromCoord(tracer1->getCoord());
    auto firstTracerActualVisibility = std::vector<Coordinate> {
                                // First tracer is on (0, 0)
            Coordinate(0, 1),   // (DOWN)
            Coordinate(1, 0)    // (RIGHT)
    };

    // visibleCoordsFromCoord doesn't need to be sorted.
    // But to compare, Coordinate's < and == will be used in sort below.
    // So we can compare two vectors without hassle.
    std::sort(firstTracerVisibility.begin(), firstTracerVisibility.end());
    std::sort(firstTracerActualVisibility.begin(), firstTracerActualVisibility.end());

    if(firstTracerVisibility != firstTracerActualVisibility){
      std::cout << "13" << '\n';
        currentGrade -= 3;
      }

    auto secondTracerVisibility = board.visibleCoordsFromCoord(tracer2->getCoord());
    auto secondTracerActualVisibility = std::vector<Coordinate> {
                                // Second tracer is on (2, 1)
            Coordinate(2, 0),   // (UP)
            Coordinate(2, 2),   // (DOWN)
            Coordinate(1, 1)    // (LEFT)
    };

    // Explained on the upper part.
    std::sort(secondTracerVisibility.begin(), secondTracerVisibility.end());
    std::sort(secondTracerActualVisibility.begin(), secondTracerActualVisibility.end());

    if(secondTracerVisibility != secondTracerActualVisibility){
      std::cout << "14" << '\n';
        currentGrade -= 3;
      }

    // Phase 6 : Storm

    // Initially, no storm should be around.
    // The storm rules are explained in PDF in detail.

    if(board.isStormInCoord(Coordinate(0, 0))){
      std::cout << "15" << '\n';
        currentGrade -= 1;
      }
    if(board.isStormInCoord(Coordinate(1, 1))){
      std::cout << "16" << '\n';
        currentGrade -= 1;
      }
    if(board.isStormInCoord(Coordinate(100, 100))){
      std::cout << "17" << '\n';
        currentGrade -= 1;
      }

    // Let's see the board without the storm.
    std::cout << std::endl;
    BoardPrinter::printBoard(board);
    std::cout << std::endl;

    // Now let's mock the GameEngine again.
    // The first layer of storm should be around.
    board.updateStorm(STORM_WIDTH_COEFF + 1);

    std::cout << std::endl;
    BoardPrinter::printBoard(board);
    std::cout << std::endl;

    if(!board.isStormInCoord(Coordinate(0, 0))){
      std::cout << "18" << '\n';
        currentGrade -= 1;
      }
    if(!board.isStormInCoord(Coordinate(2, 2))){
      std::cout << "19" << '\n';
        currentGrade -= 1;
      }

    board.updateStorm(100);
    // Hill cannot be stormed in any case.

    if(board.isStormInCoord(Coordinate(1, 1))){
      std::cout << "20" << '\n';
        currentGrade -= 1;
      }

    // Removing memory manually...
    // Normally GameEngine will/should do this.

    for(Player *player : *players) {
        delete player;
    }

    players->clear();

    delete players;

}
