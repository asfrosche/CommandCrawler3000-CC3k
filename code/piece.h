#ifndef PIECE_H
#define PIECE_H
#include <utility>

class Piece {
    char type;
    std::pair<int, int> position; 
 public:
    Piece(char type, int x, int y);
    char getType() const;
    std::pair<int, int> getPos() const;
    void setPos(int x, int y);
    ~Piece();
};

#endif
