#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
#include <memory>
#include "items/ba.h"
#include "items/bd.h"
#include "items/ph.h"
#include "items/rh.h"
#include "items/wa.h"
#include "items/wd.h"
using namespace std;
class Race;
class Piece;
class Strategy;
class Treasure;
class Potion;
class Enemy;
class Dragon;


class Board {
    int level;
    bool frozen;
    bool won = false;
    bool lose = false;
    bool DLC;
    int playerChamber;
    bool fileIncluded;
    char oldTile = '.';
    int DragonHoards = 0;
    std::string file;
    std::string action;
    std::shared_ptr<Strategy> strategy;
    std::shared_ptr<Race> player;
    std::pair<int, int> playerPos;
    std::vector<std::vector<char>> pieces; 

  public:
    Board(bool fileIncluded, string file, bool dlc);
    std::vector<std::shared_ptr<Treasure>> treasures;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Dragon>> dragons;
    const vector<vector<pair<pair<int, int>, pair<int, int>>>> chambers {
        {make_pair(make_pair(3, 3), make_pair(6, 28))},         // chamber 1
        {make_pair(make_pair(3, 39), make_pair(4, 61)),         // chamber 2
            make_pair(make_pair(5, 39), make_pair(5, 69)),
            make_pair(make_pair(6, 39), make_pair(6, 72)),
            make_pair(make_pair(7, 61), make_pair(12, 75))},
        {make_pair(make_pair(10, 38), make_pair(12, 49))},      // chamber 3
        {make_pair(make_pair(15, 4), make_pair(21, 24))},       // chamber 4
        {make_pair(make_pair(19, 37), make_pair(21, 64)),       // chamber 5
            make_pair(make_pair(16, 65), make_pair(21, 75))}};
// 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD,
    const vector<shared_ptr<Strategy>> potionStrat{make_shared<RH>(), 
        make_shared<BA>(), make_shared<BD>(), make_shared<PH>(),
        make_shared<WA>(), make_shared<WD>()
    };
    void printTextfile(std::string file);
    void setLevel(int i);
    void toggleFrozen();
    void setWon(bool update);
    void setLose(bool update);
    void setDLC(bool dlc);
    void changeDragonHoard(int i);
    void setPlayer(char race);
    void setPlayerPos(int i, int j);
    void setStrategy(shared_ptr<Strategy> potion);
    
    int getLevel() const;
    bool isWon() const;
    bool isLose() const;
    bool getDLC() const;
    string getFile() const;
    int getNumDHs() const;
    string getAction() const;
    bool isFrozen() const;
    shared_ptr<Race> getPlayer();
    pair<int, int> getPlayerPos() const;
    
    bool PCinBlock(int x, int y);
    bool isOccupied(int x, int y);
    void usePotion(string dir);
    void attackEnemy(string dir);
    void movePC(string dir);
    void moveEnemy(int r, int c);
    void moveEnemies();
   
    void spawnStair();
    void spawnPotions();
    void spawnGold();
    void spawnEnemies();

    char randomEnemy();
    int randomTreasure();
    pair<int, int> regularPos(int idx, int rec);
    pair<int, int> producePos(bool forPlayer = false); 

    vector<vector<char>> createEmptyBoard();
    void readFile(string fileName);
    void newFloor();
    void printFloor();
    bool playGame();
    void clear();
    void printLinesTextFile(std::string str, int end, int start = 0);
    void printWelcome();
    ~Board();
};

#endif
