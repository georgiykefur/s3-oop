#include "GameField.h"
#include <ctime>
#include <cstdlib>

GameField::GameField(int w, int h) {
    width = (w < 10) ? 10 : (w > 25 ? 25 : w);
    height = (h < 10) ? 10 : (h > 25 ? 25 : h);
    cells.resize(height, std::vector<GameCell>(width));

    std::srand(std::time(0));
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            if (std::rand() % 8 == 0)
                cells[y][x].setType(CellType::OBSTACLE);
        }
    }
    cells[1][1].setType(CellType::EMPTY); 
}

bool GameField::isObstacle(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return true;
    return cells[y][x].getType() == CellType::OBSTACLE;
}

const GameCell& GameField::getCell(int x, int y) const { return cells[y][x]; }
void GameField::setCellType(int x, int y, CellType type) { cells[y][x].setType(type); }

GameField::GameField(const GameField& other) : width(other.width), height(other.height), cells(other.cells) {}
GameField::GameField(GameField&& other) noexcept : width(other.width), height(other.height), cells(std::move(other.cells)) {}
GameField& GameField::operator=(const GameField& other) {
    if (this != &other) { width = other.width; height = other.height; cells = other.cells; }
    return *this;
}
GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) { width = other.width; height = other.height; cells = std::move(other.cells); }
    return *this;
}