#include "piece.h"

Piece::Piece(char type, int x, int y) 
            : type{type}, position{std::make_pair(x, y)} {}

char Piece::getType() const { return type; }

std::pair<int,int> Piece::getPos() const {
    return position;
}
void Piece::setPos(int x, int y) {
    position.first = x;
    position.second = y;
}

Piece::~Piece() {} 
