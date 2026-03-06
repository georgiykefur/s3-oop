#ifndef AREADAMAGESPELL_H
#define AREADAMAGESPELL_H

#include "ISpell.h"

class AreaDamageSpell : public ISpell {
public:
    bool apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) override;
    std::string getName() const override;
};

#endif