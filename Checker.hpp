#include<SDL.h>
#include "Board.hpp"
#include "redChecker.hpp"
#include "blackChecker.hpp"
#include<vector>
#include<list>
using namespace std;

class Checker : public Board {

    //Right now we're creating one pigeon, just for practice. for details follow the guidlines 
    // Pigeon p1;
    // Pigeon1 p2;
    //Create your list here
    public:

    void ValidMove (int x, int y);
    void drawObjects(); 
    void createObject(int x, int y);
    
    // create destructor which deletes all dynamic objects
};