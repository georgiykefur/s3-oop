#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include "GameCell.h"

class GameField {
private:
    int width, height;
    std::vector<std::vector<GameCell>> cells;

public:
    GameField(int w, int h);
    
    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;
    ~GameField() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
   
    const GameCell& getCell(int x, int y) const;
    void setCellType(int x, int y, CellType type);
    bool isObstacle(int x, int y) const;
};

#endif