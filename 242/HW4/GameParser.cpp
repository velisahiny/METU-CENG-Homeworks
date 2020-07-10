#include "GameParser.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include "Tracer.h"
#include "Dummy.h"
#include "Berserk.h"
#include "Ambusher.h"
#include "Pacifist.h"
#include<fstream>
#include <iostream>
#include <sstream>
#include<string>
/**
 * Parse the file with given name and create players accordingly.
 *
 * GameParser DOES NOT have any responsibility over these Players.
 *
 * Note: The file will always exists, and there will be no erroneous input.
 *
 * @param filename The name of the file to be parsed.
 * @return  pair.first: Board size.
 *          pair.second: The vector of the constructed players.
 */
  std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string& filename){
  std::ifstream myfile;
  myfile.open(filename.c_str());
  std::string newline, boardsize_str, playercount_str;
  //boardsize
  int playercount,boardsize;
  getline(myfile,newline);
  boardsize_str = newline.substr(12);
  //playercount
  getline(myfile,newline);
  playercount_str = newline.substr(14);




  std::istringstream ( playercount_str ) >> playercount;

  std::istringstream ( boardsize_str ) >> boardsize;


  //pair  and vector
  static std::pair<int,std::vector<Player * > * > mypair;
  mypair.first = boardsize;

  std::vector<Player* >* myvector = new std::vector<Player* >() ;

  myvector->reserve(playercount);
  mypair.second = myvector;





  while(!myfile.eof()){
    getline(myfile,newline);

    if(newline==""){break;}

    else{
      int firstdots = newline.find("::");
      int id ;
      std::istringstream ( newline.substr(0,firstdots)  ) >> id;

      newline = newline.substr(firstdots+2);
      int seconddots = newline.find("::");
      std::string playername = newline.substr(0,seconddots);
      std::string coordinates = newline.substr(seconddots+2);
      int thirddots = coordinates.find("::");
      int xcoord ;
      std::istringstream ( coordinates.substr(0,thirddots)  ) >> xcoord;
      int ycoord ;
      std::istringstream ( coordinates.substr(thirddots+2) ) >> ycoord;

        if( playername== "Tracer"){
            Tracer* t = new Tracer(id,xcoord,ycoord);
            myvector->push_back(t);
            }
        else if( playername== "Berserk"){
            Berserk* b = new Berserk(id,xcoord,ycoord);
            myvector->push_back(b);
            }
        else if( playername== "Ambusher"){
            Ambusher* a = new Ambusher(id,xcoord,ycoord);
            myvector->push_back(a);
            }
        else if( playername== "Pacifist"){
            Pacifist* p = new Pacifist(id,xcoord,ycoord);
            myvector->push_back(p);
            }
        else if( playername== "Dummy"){
            Dummy* d = new Dummy(id,xcoord,ycoord);
            myvector->push_back(d);
            }

        }
  }//while ends here
  myfile.close();

  return mypair;

}
