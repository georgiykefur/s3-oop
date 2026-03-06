#ifndef TRAPSPELL_H
#define TRAPSPELL_H

#include "ISpell.h"

class TrapSpell : public ISpell {
public:
    bool apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) override;
    std::string getName() const override;
};

#endif