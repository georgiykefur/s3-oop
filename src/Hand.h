#ifndef HAND_H
#define HAND_H

#include <vector>
#include <memory>
#include "ISpell.h"

class Hand {
private:
    std::vector<std::unique_ptr<ISpell>> spells;
    size_t maxSize;

public:
    Hand(size_t size);
    bool addSpell(std::unique_ptr<ISpell> spell);
    bool castSpell(size_t index, int x, int y, GameField& field, std::vector<Enemy>& enemies);
    void removeHalfSpells();
    
    const std::vector<std::unique_ptr<ISpell>>& getSpells() const { return spells; }
};

#endif