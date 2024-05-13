#include "board.h"
#include "piece.h"
#include "race.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include "strategy.h"
#include "items/normalPile.h"
#include "items/smallPile.h"
#include "items/dragonHoard.h"
#include "items/merchantHoard.h"
#include "enemies/dwarf.h" 
#include "enemies/elf.h"
#include "enemies/halfling.h"
#include "enemies/human.h"
#include "enemies/merchant.h"
#include "enemies/orc.h"
#include "races/drow.h"
#include "races/goblin.h"
#include "races/shade.h"
#include "races/troll.h"
#include "races/vampire.h"
#include "dragon.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Constructor
Board::Board(bool fileIncluded, string file, bool dlc) 
    : level{1}, frozen{false}, DLC{dlc}, fileIncluded{fileIncluded}, file{file} {};

// Sets player pointer
void Board::setPlayer(char race) {
    pair<int, int> pos;
    if (!fileIncluded) {
        pos = producePos(true);
        pieces[pos.first][pos.second] = '@';
    } else {
        pos = getPlayerPos();
    }
    if ((race == 'd') || (race == 'D')) {
        auto newPlayer = make_shared<Drow>(pos.first, pos.second); 
        player = newPlayer;
    } else if ((race == 'g') || (race == 'G')) {
        auto newPlayer = make_shared<Goblin>(pos.first, pos.second);
        player = newPlayer; 
    } else if ((race == 's') || (race == 'S')) {
        auto newPlayer = make_shared<Shade>(pos.first, pos.second);
        player = newPlayer; 
    } else if ((race == 't') || (race == 'T')) {
        auto newPlayer = make_shared<Troll>(pos.first, pos.second);
        player = newPlayer; 
    } else {
        auto newPlayer = make_shared<Vampire>(pos.first, pos.second); 
        player = newPlayer;
    }
}

void Board::setPlayerPos(int i, int j) { playerPos = make_pair(i, j); }

void Board::setLevel(int i) { level = i; }

// Sets the strategy for the random potion given
void Board::setStrategy(shared_ptr<Strategy> potion) { strategy = potion; }

// Sets frozen to be true if false, and sets it to be false if true
void Board::toggleFrozen() { frozen = !frozen; }

void Board::setWon(bool update) { won = update; }

void Board::setLose(bool update) { lose = update; }

void Board::setDLC(bool dlc) { DLC = dlc; }

void Board::changeDragonHoard(int i) { DragonHoards += i; }

// Returns the player pointer
shared_ptr<Race> Board::getPlayer() { return player; }

pair<int, int> Board::getPlayerPos() const { return playerPos; }

int Board::getLevel() const { return level; }

bool Board::isWon() const { return won; }

bool Board::isLose() const { return lose; }

bool Board::getDLC() const { return DLC; }

// Returns the name of the inputted file
string Board::getFile() const { return file; }

int Board::getNumDHs() const { return DragonHoards; }

string Board::getAction() const { return action; }

// Returns true if Board is frozen and false otherwise
bool Board::isFrozen() const { return frozen; }

bool Board::PCinBlock(int x, int y) { 
    const char charPlayer = '@';
    if ((pieces[x - 1][y - 1] == charPlayer) || (pieces[x - 1][y] == charPlayer) ||
        (pieces[x - 1][y + 1] == charPlayer) || (pieces[x][y - 1] == charPlayer) || 
        (pieces[x][y + 1] == charPlayer) || (pieces[x + 1][y - 1] == charPlayer) ||
        (pieces[x + 1][y] == charPlayer) || (pieces[x + 1][y + 1] == charPlayer)) {
            return true;
        }
    return false;
}

bool Board::isOccupied(int x, int y) {
    char tile = pieces[x][y];
    if (tile == '.' || tile == '+' || tile == '#') return false;
    return true;
}

// Returns the coordinates of a piece that is in the direction, dir, of playerPos
pair<int, int> dirToPos(string dir, pair<int, int> playerPos) {
    int x = playerPos.first;
    int y = playerPos.second;
    if (dir == "no") return make_pair(x - 1, y);
    else if (dir == "so") return make_pair(x + 1, y);
    else if (dir == "ea") return make_pair(x, y + 1);
    else if (dir == "we") return make_pair(x, y - 1);
    else if (dir == "ne") return make_pair(x - 1, y + 1);
    else if (dir == "nw") return make_pair(x - 1, y - 1);
    else if (dir == "se") return make_pair(x + 1, y + 1);
    return make_pair(x + 1, y - 1);
}

string whichGold(int i) {
    if (i == 1) return " moved onto a Small Pile of gold! ";
    if (i == 2) return " moved onto a Normal Pile of gold! ";
    if (i == 4) return " moved onto a Merchant Hoard! ";
    return " successfully acquired a Dragon Hoard! ";
}

string whichPotion(int i) {
    if (i == 0) return ": Restore Health. ";
    if (i == 1) return ": Boost Attack. ";
    if (i == 2) return ": Boost Defence. ";
    if (i == 3) return ": Poison Health. ";
    if (i == 4) return ": Wound Attack. ";
    return ": Wound Defence";
}

string whichDir(string dir) {
    if (dir == "no") return " North. ";
    if (dir == "so") return " South. ";
    if (dir == "ea") return " East. ";
    if (dir == "we") return " West. ";
    if (dir == "ne") return " North-East. ";
    if (dir == "nw") return " North-West. ";
    if (dir == "se") return " South-East. ";
    return " South-West. ";
}

void Board::movePC(string dir) {
    auto newPos = dirToPos(dir, getPlayer()->getPos());
    int x = newPos.first;
    int y = newPos.second;
    auto curPos = getPlayer()->getPos();
    char nextTile = pieces[x][y];
    if (nextTile == 'G') {
        int i = 0;
        for (auto &gold : treasures) {
            if (newPos == gold->getPos()) {
                int value = gold->getValue();
                if ( (value != 6) || (getNumDHs() != (int)dragons.size()) ) {
                    getPlayer()->addGold(value);
                    action = "Player has";
                    action += whichGold(value);
                    pieces[curPos.first][curPos.second] = oldTile;
                    oldTile = '.';
                    pieces[x][y] = '@';
                    getPlayer()->setPos(x, y);
                    treasures.erase(treasures.begin()+i);
                    if (value == 6) changeDragonHoard(-1);
                    moveEnemies();
                    break;
                }     
            } else {
                action = "Player attempted to move onto a guarded Dragon Hoard.";
            }
            ++i;
        }
        if (!isLose()) {
            printFloor();
        } 
    } else if (nextTile == '\\') {
        if (getLevel() == 5) {
            int winAmount = getPlayer()->getGold();
            if (getPlayer()->getRace() == "Shade") {
                winAmount *= 1.5;
            } 
            cout << "Your total Score = " << winAmount << endl;
            printTextfile("win.txt");
            setWon(true);
        } else {
            action = "PC moved up to floor ";
            getPlayer()->resetStats();
            setLevel(getLevel() + 1);
            action += to_string(getLevel());
            action += "!";
            if (fileIncluded) {
                clear();
                readFile(getFile());
                getPlayer()->setPos(getPlayerPos().first, getPlayerPos().second);
            } else {
                clear();
                pieces = createEmptyBoard();
                newFloor();
            }
            printFloor();
        }
    } else if (!isOccupied(x, y)) {
        action = "PC moved";
        action += whichDir(dir);
        pieces[curPos.first][curPos.second] = oldTile;
        oldTile = pieces[x][y];
        pieces[x][y] = '@';
        getPlayer()->setPos(x, y);
        moveEnemies();
        if (getPlayer()->isDead()) {
            setLose(true);
        } else {
            printFloor();
        }
    } else {
        cout << "\033[1;31mInvalid move.\033[0m\n";
    }
}

void Board::moveEnemy(int r, int c) {
    vector<pair<int, int>> unOccupied;
    for (auto &enemy : enemies) {
        if ((enemy->getPos().first == r) && (enemy->getPos().second == c)) {
            if ((PCinBlock(r, c) && (enemy->getType() != 'M')) || 
                (PCinBlock(r, c) && ((enemy->getType() == 'M') && enemy->isHostile()))) {
                // attack instead of move
                // enemy i is the shared ptr for the enemy present
                int oldHealth = getPlayer()->getHP(); 
                enemy->attack(*getPlayer());
                int newHealth = getPlayer()->getHP(); 
                int damageDealt = oldHealth - newHealth;
                if (damageDealt) {
                    action += enemy->getType();
                    action += " attacked PC dealing ";
                    action += to_string(damageDealt);
                    action += "HP damage. ";
                    if (getPlayer()->isDead()) {
                        setLose(true);
                    }
                } else {
                    action += enemy->getType();
                    action += " missed! ";
                }
                break;
            } else if ((!isFrozen()) && (!enemy->hasMoved())) {
                for(int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int x = r + i;
                        int y = c + j;
                        if (pieces[x][y] == '.') {
                            unOccupied.emplace_back(make_pair(x, y));
                        }        
                    }
                }
                if (unOccupied.size() != 0) {
                    int newPos = (rand() % unOccupied.size()) ;
                    int x = unOccupied[newPos].first;
                    int y = unOccupied[newPos].second;
                    enemy->setPos(x, y);
                    // update pieces
                    pieces[x][y] = enemy->getType();
                    pieces[r][c] = '.';
                    enemy->setMoved(true);
                }
                break;
            }
        } 
    }
}

// Goes through the entire board and randomly moves enemies one block from original position
// or attacks if there is a PC in range
void Board::moveEnemies() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 79; j++) {
            char enemyChar = pieces[i][j];
            if ((enemyChar == 'W') || (enemyChar == 'E') || (enemyChar == 'H') ||
                (enemyChar == 'L') || (enemyChar == 'O') || (enemyChar == 'M')) { 
                    moveEnemy(i, j);
            } else if (enemyChar == 'D') {
                for (auto p : dragons) {
                    if ((p->getPos().first == i) && (p->getPos().second == j)) {
                        if ((PCinBlock(i,j)) || (PCinBlock(p->getHoardLoc().first, p->getHoardLoc().second))) {
                            int oldHealth = getPlayer()->getHP(); 
                            p->attack(*getPlayer());
                            int newHealth = getPlayer()->getHP(); 
                            int damageDealt = oldHealth - newHealth;
                            if (damageDealt) {
                                action += "Dragon dealt ";
                                action += to_string(damageDealt);
                                action += "HP damage. ";
                                if (getPlayer()->isDead()) {
                                    setLose(true);
                                }
                            } else {
                                action += "Dragon missed! ";
                            }
                        }
                        break;
                    }
                }
            }
        }         
    }
    for (auto& enemy : enemies) {
        enemy->setMoved(false);
    }
}

void Board::spawnStair() {
    pair<int, int> pos;
    int val = (rand() % 5) + 1;
    while (val == playerChamber) {
        val = (rand() % 5) + 1;
    }
    if (val == 2) {
        // spawn in chamber 2
        int subChamber = (rand() % 181);
        if (subChamber < 26) pos = regularPos(val, 1);
        else if (subChamber < 57) pos = regularPos(val, 2);
        else if (subChamber < 91) pos = regularPos(val, 3);
        else pos = regularPos(val, 4);
    } else if (val == 5) {
        // spawn in chamber 5
        int subChamber = (rand() % 150);
        if (subChamber < 84) pos = regularPos(val, 1);
        else pos = regularPos(val, 2);
    } else {
        // spawn in chamber 1/3/4
        pos = regularPos(val, 1);
    }
    pieces[pos.first][pos.second] = '\\';
}

void Board::spawnPotions() {
        for (int i = 0; i < 10; ++i) {
        auto temp = producePos();
        int x = temp.first;
        int y = temp.second;
        pieces[x][y] = 'P';
        potions.emplace_back(make_shared<Potion>(x, y));
    }
}

void Board::spawnGold() {
    int totalGold = 10;
    if (getDLC()) {
        totalGold = (getLevel() * -2) + 12;
    } 
    //reduces one gold per level
    for (int i = 0; i < totalGold; ++i) {
        auto newGoldPos = producePos();
        int x = newGoldPos.first;
        int y = newGoldPos.second;
        pieces[x][y] = 'G';
        int num = randomTreasure();
        if (num == 6) {
            treasures.emplace_back(make_shared<NormalPile>(x, y));    
        } else if (num == 7) {
            treasures.emplace_back(make_shared<SmallPile>(x, y));
        } else {
            treasures.emplace_back(make_shared<DragonHoard>(x, y));
            changeDragonHoard(1);
            vector<pair<int, int>> dragonLocs;
            for(int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int a = x + i;
                    int b = y + j;
                    if (!isOccupied(a, b)) {
                        dragonLocs.emplace_back(make_pair(a, b)); 
                    }        
                }
            }
            if (dragonLocs.size() != 0) {
                int newDragonPos = rand() % dragonLocs.size();
                int x = dragonLocs[newDragonPos].first;
                int y = dragonLocs[newDragonPos].second;
                dragons.emplace_back(make_shared<Dragon>(newGoldPos, x, y));
                pieces[x][y] = 'D';
            }
        }
    }
}

void Board::spawnEnemies() {
    int enemyNum = 20;
    if (getDLC()) {
        enemyNum = 18 + (getLevel() * 2);
    } 
    for (int i = 0; i < enemyNum; ++i) {
        auto temp = producePos();
        char enemy = randomEnemy();
        pieces[temp.first][temp.second] = enemy;
        if (enemy == 'W') {
            enemies.emplace_back(std::make_shared<Dwarf>(temp.first, temp.second));
        } else if (enemy == 'E') {
            enemies.emplace_back(std::make_shared<Elf>(temp.first, temp.second));
        } else if (enemy == 'L') {
            enemies.emplace_back(std::make_shared<Halfling>(temp.first, temp.second)); 
        } else if (enemy == 'H') {
            enemies.emplace_back(std::make_shared<Human>(temp.first, temp.second));
        } else if (enemy == 'O') {
            enemies.emplace_back(std::make_shared<Orc>(temp.first, temp.second)); 
        } else {
            enemies.emplace_back(std::make_shared<Merchant> (temp.first, temp.second));
        }
    }
}

// Returns a random enemy charecter with the probabilities defined below
// (H)uman:2/9, d(W)arf:3/18, Half(L)ing:5/18, (E)lf:1/9,
// (O)rc,:1/9, (M)erchant:1/9, (D)ragon = 0;  
char Board::randomEnemy() {
    int val = (rand() % 18);
    if (val < 4) return 'H'; // Human
    if (val < 7) return 'W'; // Dwarf
    if (val < 12) return 'L'; // Halfling
    if (val < 14) return 'E'; // Elf
    if (val < 16) return 'O'; // Orc
    return 'M'; // Merchant
}

// Returns a random number representing a pile of gold
// 6 - normal gold pile, 7 - small hoard, 9 - dragon hoard.
int Board::randomTreasure() { 
    int val = (rand() % 8);
    if (val == 0) return 9; // dragon
    if (val > 5) return 7; // small
    return 6; // normal
}

// Returns a position in a rectangle 
pair<int, int> Board::regularPos(int idx, int rec) {
    //cout << "in regularpos() with val = " << idx << " and rec = " << rec << endl;
    int x = (rand() % (chambers[idx - 1][rec - 1].second.first - chambers[idx - 1][rec - 1].first.first + 1)) + chambers[idx - 1][rec - 1].first.first;
    int y = (rand() % (chambers[idx - 1][rec - 1].second.second - chambers[idx - 1][rec - 1].first.second + 1)) + chambers[idx - 1][rec - 1].first.second;
    
    //cout << "x = " << x << ", y = " << y << endl;
    if (!isOccupied(x, y)) return make_pair(x, y);
    return producePos();
}

void Board::printTextfile(string fileName) {
    std::ifstream f(fileName);
    if (f.is_open()) cout << f.rdbuf();
}

// Returns a position to spawn into
pair<int, int> Board::producePos(bool forPlayer) {
     // choose chamber
    int val = (rand() % 5) + 1;
    if (forPlayer) {
        playerChamber = val;
    }
    if (val == 2) {
        // spawn in chamber 2
        int subChamber = rand() % 181;
        if (subChamber < 26) return regularPos(val, 1);
        if (subChamber < 57) return regularPos(val, 2);
        if (subChamber < 91) return regularPos(val, 3);
        return regularPos(val, 4);
    } else if (val == 5) {
        // spawn in chamber 5
        int subChamber = rand() % 150;
        if (subChamber < 84) return regularPos(val, 1);
        return regularPos(val, 2);
    } else return regularPos(val, 1);
}

//Creates a 2D vector for empty board 
vector<vector<char>> Board::createEmptyBoard() { 
  string line;
  ifstream myfile;
  myfile.open("floor.txt");
  vector<vector<char>> mapOutline; //2D vector of chars
  while (getline(myfile, line)) {
    vector<char> row;
    for (char &c : line) {
        row.push_back(c);
    }
    mapOutline.push_back(row);
  }
  return mapOutline;
}
// Sets the contents of floor accorading to file read in
// 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD, 6 - normal gold pile, 
//7 -  small  hoard,  8  -  merchant hoard, 9 -  dragon hoard.
void Board::readFile(string fileName) {
    for (auto &row : pieces) row.clear();
    pieces.clear();
    string line;
    ifstream myfile;
    myfile.open(fileName);
    int i = 0;
    vector<shared_ptr<Treasure>> dragHoards;
    int lineCounter = 0;
    int floorLineStart = (getLevel() - 1) * 25;
    int floorLineEnd = getLevel() * 25;
    changeDragonHoard(0);
    while (getline(myfile, line)) {
        if (lineCounter < floorLineStart){
            ++lineCounter;
        } else {
            ++lineCounter;
            int j = 0;
            vector<char> row;
            for (char &c : line) {
                if (c == '0') {
                    row.push_back('P');
                    potions.emplace_back(make_shared<Potion>(i, j, 0));
                } else if (c == '1') {
                    row.push_back('P');
                    potions.emplace_back(make_shared<Potion>(i, j, 1));
                } else if (c == '2') {
                    row.push_back('P');
                    potions.emplace_back(make_shared<Potion>(i, j, 2));
                } else if (c == '3') {
                    row.push_back('P');
                    potions.emplace_back(make_shared<Potion>(i, j, 3));
                } else if (c == '4') {
                    row.push_back('P');
                    potions.emplace_back(make_shared<Potion>(i, j, 4));
                } else if (c == '5') {
                    row.push_back('P');
                    potions.emplace_back(make_shared<Potion>(i, j, 5));
                } else if (c == '6') {
                    row.push_back('G');
                    treasures.emplace_back(make_shared<NormalPile>(i, j));
                } else if (c == '7') {
                    row.push_back('G');
                    treasures.emplace_back(make_shared<SmallPile>(i, j));
                } else if (c == '8') {
                    row.push_back('G');
                    treasures.emplace_back(make_shared<MerchantHoard>(i, j));
                } else if (c == '9') {
                    row.push_back('G');
                    treasures.emplace_back(make_shared<DragonHoard>(i, j));
                    changeDragonHoard(1);
                    dragHoards.emplace_back(treasures[treasures.size()-1]);
                } else if (c == '@') {
                    row.push_back(c);
                    setPlayerPos(i, j);
                } else if (c == '\\') row.push_back(c);
                else if (c == 'H') {
                    row.push_back(c);
                    enemies.emplace_back(make_shared<Human>(i, j));
                } else if (c == 'W') {
                    row.push_back(c);
                    enemies.emplace_back(make_shared<Dwarf>(i, j));
                } else if (c == 'E') {
                    row.push_back(c);
                    enemies.emplace_back(make_shared<Elf>(i, j));
                } else if (c == 'O') {
                    row.push_back(c);
                    enemies.emplace_back(make_shared<Orc>(i, j));
                } else if (c == 'M') {
                    row.push_back(c);
                    enemies.emplace_back(make_shared<Merchant>(i, j));
                } else if (c == 'L') {
                    row.push_back(c);
                    enemies.emplace_back(make_shared<Halfling>(i, j));
                } else if (c == 'D') {
                    row.push_back(c);
                    dragons.emplace_back(make_shared<Dragon>(make_pair(0,0), i, j));
                } else {
                    row.push_back(c);
                }
                ++j;
            }
                
            pieces.push_back(row);
            ++i;
            if (lineCounter == floorLineEnd) {
                break;
            }
        }
        for (auto dragon : dragons) { 
            for(int i = -1; i <= 1; i++) {
                if ((dragon->getHoardLoc().first != 0) && (dragon->getHoardLoc().second != 0)) {
                    break;
                }
                for (int j = -1; j <= 1; j++) {
                    if ((dragon->getHoardLoc().first != 0) && (dragon->getHoardLoc().second != 0)) {
                        break;
                    }
                    int x = dragon->getPos().first + i;
                    int y = dragon->getPos().second + j;
                    if (pieces[x][y] == 'G') {
                        int counter = 0;
                        for (auto hoard : dragHoards) {
                            if (hoard->getPos() == make_pair(x,y)) {
                                dragon->setHoardLoc(make_pair(x,y));
                                dragHoards.erase(dragHoards.begin() + counter);
                                break;
                            }
                            ++counter;
                        } 
                    }
                }       
            }
       }
    }
}

// Creates a new floor and places pieces on the floor
void Board::newFloor() {    
    if (getLevel() != 1) {
        auto newPos = producePos(true);
        getPlayer()->setPos(newPos.first, newPos.second);
        pieces[newPos.first][newPos.second] = '@';
    }
    spawnStair();
    spawnPotions();
    spawnGold();
    spawnEnemies();
}

// Clears the board
void Board::clear() {
    setWon(false);
    setLose(false);
    changeDragonHoard(-getNumDHs());
    enemies[0]->setHostile(false);
    if (isFrozen()) toggleFrozen();
    for (auto &col : pieces) col.clear();
    pieces.clear();
    treasures.clear();
    potions.clear();
    enemies.clear();
    dragons.clear();
}

void Board::usePotion(string dir) {
    auto newPos = dirToPos(dir, getPlayer()->getPos());
    int x = newPos.first;
    int y = newPos.second;
    auto curPos = getPlayer()->getPos();
    int i = 0;
    for (auto &potion : potions) {
        if (newPos == potion->getPos()) {
            action = "Player used potion";
            int idx = potion->getIdx();
            if (idx == -1) {
                int itemNum = rand() % potionStrat.size();
                action += whichPotion(itemNum);
                setStrategy(potionStrat[itemNum]);
                strategy->usePotion(*getPlayer());
            } else {
                action += whichPotion(idx);
                setStrategy(potionStrat[idx]);
                strategy->usePotion(*getPlayer());
            }
            pieces[curPos.first][curPos.second] = oldTile;
            oldTile = '.';
            pieces[x][y] = '@';
            getPlayer()->setPos(x, y);
            potions.erase(potions.begin()+i);
            if (getPlayer()->isDead()) {
                setLose(true);
            }
            break;
        }
        ++i;
    }
}
// shade4 that has starting stats (125 HP, 25 Atk, 25 Def). However, players have the option 
// of choosing an alternate (but no less heroic) race: drow (150 HP, 25 Atk , 15 Def, all potions have their effect magniﬁed by 
// 1.5), vampire (50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP), troll (120 HP, 25 Atk, 
// 15 Def, regains 5 HP every turn; HP is capped at 120 HP), and goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain 
// enemy)






// Prints the current floor and its pieces
void Board::printFloor() {
     if (getPlayer()->getRace() == "Troll") {
         if (getPlayer()->getHP() + 5 > getPlayer()->getMaxHP() ) {
            getPlayer()->changeHP(getPlayer()->getMaxHP() - getPlayer()->getHP());
         } else {
             getPlayer()->changeHP(5); // special ability to heal 5HP after every turn
         }
    }

    for (auto &row : pieces) {
        for (auto &col : row) {
            if (col == 'P') {
                cout << "\033[1;35m";
                cout << col; 
                cout << "\033[0m";
            } else if (col == 'G') {
                cout << "\033[1;33m";
                cout << col; 
                cout << "\033[0m";
            } else if (col == 'H' || col == 'L' || col == 'O' || col == 'W' ||
                        col == 'E' || col == 'M' || col == 'D') {
                cout << "\033[1;32m";
                cout << col; 
                cout << "\033[0m";
            } else if (col == '#') {
                cout << "\033[2;37m";
                cout << col; 
                cout << "\033[0m";
            } else if (col == '@') {
                cout << "\033[1;36m";
                cout << col; 
                cout << "\033[0m";
            } else if (col == '.') {
                cout << "\033[2;32m";
                cout << col; 
                cout << "\033[0m";
            } else if (col == '-' || col == '|') {
                cout << "\033[0;31m";
                cout << col; 
                cout << "\033[0m";
            } else {
                cout << col;
            }
        }
        cout << endl;
    }
    string first = "Race: ";
    first += player->getRace();
    first += " Gold: ";
    first += to_string(player->getGold());
    cout << setw(70) << left << first << "Floor " << level << endl;
    cout << "HP: " << player->getHP() << endl;
    cout << "Atk: " << player->getAtk() << endl;
    cout << "Def: " << player->getDef() << endl;
    cout << "Action: " << getAction() << endl;
}

void Board::attackEnemy(string dir) {
    pair<int,int> pos = dirToPos(dir, getPlayer()->getPos());
    int idx = 0;
    for (auto &enemy : enemies) {
        int enemyX = enemy->getPos().first;
        int enemyY = enemy->getPos().second;
        if ((enemyX == pos.first) && (enemyY == pos.second)) {
            int oldHealth = enemy->getHP();
            getPlayer()->attack(*enemy);
            int newHealth = enemy->getHP();
            if (enemy->isDead()) {
                if (enemy->getType() == 'H') {
                    action = "The Human has been slain dropping 2 piles of gold!";
                    treasures.emplace_back(make_shared<NormalPile>(enemyX, enemyY));
                    pieces[enemyX][enemyY] = 'G';
                    vector<pair<int,int>> pileLocs;
                        for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            int x = enemyX + i;
                            int y = enemyY + j;
                            if (!isOccupied(x, y)) {
                                pileLocs.emplace_back(make_pair(x, y));
                            }        
                        }
                    }
                    if (pileLocs.size() != 0) {
                        int newPos = (rand() % pileLocs.size()) ;
                        treasures.emplace_back(make_shared<NormalPile>(pileLocs[newPos].first, pileLocs[newPos].second));
                        pieces[pileLocs[newPos].first][pileLocs[newPos].second] = 'G';
                    }
                } else if (enemy->getType() == 'M') {
                    action = "The Merchant has been slain and dropped his hoard!";
                    treasures.emplace_back(make_shared<MerchantHoard>(enemyX, enemyY));
                    pieces[enemyX][enemyY] = 'G';
                } else {
                    action = "PC has slain ";
                    action += enemy->getType();
                    action += " and gained ";
                    action += to_string(enemy->getGold()); 
                    action += " gold. ";
                    getPlayer()->addGold(enemy->getGold());
                    pieces[enemyX][enemyY] = '.';
                }
                if (getPlayer()->getRace() == "Goblin") {    // special ability for Goblin, steals 5 gold for every slain enemy
                    getPlayer()->addGold(5);
                }
                enemies.erase(enemies.begin()+idx);
                break;
            } else {
                int damage = oldHealth - newHealth;
                if (damage == 0) {
                    action = "PC missed! ";
                } else {
                    action = "PC dealt ";
                    action += enemy->getType();
                    action += " ";
                    action += to_string(damage);
                    action += "HP damage(";
                    action += to_string(enemy->getHP());
                    action += "HP). ";
                }
                break;
            }
        }
        ++idx;
    }
}

void Board::printLinesTextFile(string fileName, int end, int start) {
    fstream file;
    string line;
    file.open (fileName);
    int num_lines = 0;
    while (getline(file, line) && (num_lines < end)) {
        if(num_lines < start) {
            num_lines++;
        } else if(num_lines <= end) {
            std::string a = "|";
            std::string b = "_";
            std::string c = "-";
            if ((line.find('|')!= std::string::npos) ||
                (line.find('-')!= std::string::npos) ||
                (line.find('_')!= std::string::npos)) {
                cout << line << endl;  
            } else {
                //colour me
                cout << "\033[1;32m"; 
                cout << line << endl;  
                cout << "\033[0m";
            }
            num_lines++;
        }
    }
}

void Board::printWelcome() {
    cout<<"\t\t\t\033[1;32mWelcome to CommandCrawler3000 🤹‍♂️\n";
    cout <<"\tI am CommandMaster and I am here to get you started with my Dungeon\n";
    cout<<"\t     Are you a new player and want some detailed instructions\n";
    cout<<"\t              to see how my Chamber works? [y/n]\n\033[0m";
    char key;
    cin >> key;
    if (key == 'y' || key == 'Y') {
        cout<<"\n\033[1;31mYou will learn about Game Floor🌠 and Gold💰\n\033[0m";
        if(cin.get()) {
            printLinesTextFile("Instructions.txt", 22);  //gold
        }
        cout<< "\n\033[1;31mYou will now learn about Potions. (Maybe Potent or Powerful)🧪\n\033[0m";
        cout<< "Press any key to continue";
        if(cin.get()) {
            printLinesTextFile("Instructions.txt",34,22);  //potions
        }
        cout<< "\033[1;31mYou will now learn the 20 enemies spawned per floor.\n";
        cout<< "Each with its own charecteristics and powers!🧛‍♂️ \n\033[0m";
        cout<< "Press any key to continue \n";
        if(cin.get()) {
            printLinesTextFile("Instructions.txt",53,33); //enemies
        }
        cout<< "\nPress any key to continue \n";
        if(cin.get()) {
            printLinesTextFile("Instructions.txt",61,53); // more enemies
        }
        cout<< "\n\033[1;31mNows the Most important part - ⚙ Commands ⚙\033[0m \nPress any key to continue \n";
        if(cin.get()) {
            printLinesTextFile("Instructions.txt",73,61); // Commands
        }
        cout<< "\nYou are almost ready to begin\nPress any key to continue \n";
        if(cin.get()) {
        printTextfile("WelcomeText.txt");
        }
    } else {
    printTextfile("WelcomeText.txt");
    }
}

// Controls a game of CC3K
bool Board::playGame() {
    if (fileIncluded) {
        readFile(getFile());
    } else {
        pieces = createEmptyBoard();
        newFloor();
    }
    printWelcome();
    char type;
    while (cin >> type) {
        //type sensitive
        if (type == 's' || type == 'g' || type == 'v' || type == 't' || type == 'd') {
            setPlayer(type);
            break;
        } else {
            cout << "\033[1;31mInvalid race selected.\033[0m" << endl;
        }
    }
    action = "PC has spawned.";
    printFloor();
    bool play = true;
    while (play) {
        string cmd;
        string dir;
        cin >> cmd; // reads no, so, ea, we, ne, nw, se, sw, u, a, f, r, q
        if (cin.eof()) return true;
        if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || 
            cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {  // MOVE PLAYER
            movePC(cmd);
            if (isWon()) {
                break;
            } else if (isLose()) {
                printTextfile("lose.txt");
                break;
            }
        } else if (cmd == "u") {                                         // USE POTION
            cin >> dir;
            pair<int,int> pos = dirToPos(dir, getPlayer()->getPos());
            if (pieces[pos.first][pos.second] == 'P') {
                usePotion(dir);
                if (isLose()) {
                    printTextfile("lose.txt");
                    break;
                }
                moveEnemies();
                if (isLose()) {
                    printTextfile("lose.txt");
                    break;
                }
                printFloor();
            } else {
                cout << "Oops! Looks like there's no potion there :(" << endl;
            }
        } else if (cmd == "a") {                                         // ATTACK ENEMY
            cin >> dir;
            pair<int,int> pos = dirToPos(dir, getPlayer()->getPos());
            if (pieces[pos.first][pos.second] == 'H' || pieces[pos.first][pos.second] == 'W' || pieces[pos.first][pos.second] == 'E' || 
                pieces[pos.first][pos.second] == 'O' || pieces[pos.first][pos.second] == 'M' || pieces[pos.first][pos.second] == 'L') {
                attackEnemy(dir);
                moveEnemies();
                if (isLose()) {
                    printTextfile("lose.txt");
                    break;
                }
                printFloor();
            } else if (pieces[pos.first][pos.second] == 'D') {
                int idx = 0;
                for (auto &dragon : dragons) {
                    if ((dragon->getPos().first == pos.first) && (dragon->getPos().second == pos.second)) {
                        int oldHealth = dragon->getHP();
                        getPlayer()->attack(*dragon);
                        int newHealth = dragon->getHP();
                        if (dragon->isDead()) {
                            action = "PC has slain the Dragon. ";
                            action += "The Dragon Hoard is free to claim! "; 
                            pieces[dragon->getPos().first][dragon->getPos().second] = '.';
                            dragons.erase(dragons.begin()+idx);
                            moveEnemies();
                            break;
                        } else {
                            action = "PC dealt Dragon ";
                            action += to_string(-newHealth + oldHealth);
                            action += "HP damage(";
                            action += to_string(dragon->getHP());
                            action += "HP). ";
                            moveEnemies();
                            break;
                        }
                    }
                    ++idx;
                }
                if (isLose()) {
                    printTextfile("lose.txt");
                    break;
                }
                printFloor();
            } else {
                cout << "\033[1;31mYou must be tripping, there's no enemy there.\033[0m" << endl;
            }
        }
        else if (cmd == "f") { toggleFrozen(); }                         // FREEZE BOARD
        else if (cmd == "r") {                                           // RESTART GAME
            clear(); 
            setLevel(1);
            return false;
        }
        else if (cmd == "q") {                                           // QUIT GAME
            cout << "The game has ended." << endl;
            break;
        } else {
            cout << "\033[1;31mInvalid command\033[0m" << endl;
        }
    }
    cout << "Would you like to play again? [y/n]" << endl;
    char res;
    cin >> res;
    if (res == 'y' || res == 'Y') {
        clear();
        setLevel(1);
        return false;
    }
    return true;
}
Board::~Board() {}
