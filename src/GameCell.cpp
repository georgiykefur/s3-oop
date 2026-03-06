#include "GameCell.h"

GameCell::GameCell() : type(CellType::EMPTY) {}

void GameCell::setType(CellType newType) {
    type = newType;
}

CellType GameCell::getType() const {
    return type;
}