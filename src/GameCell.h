#ifndef GAMECELL_H
#define GAMECELL_H

#include "Enums.h" 

class GameCell {
private:
    CellType type;
public:
    GameCell(); 
    void setType(CellType newType);
    CellType getType() const;
};

#endif