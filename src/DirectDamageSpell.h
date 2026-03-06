#ifndef DIRECTDAMAGESPELL_H
#define DIRECTDAMAGESPELL_H

#include "ISpell.h"

class DirectDamageSpell : public ISpell {
public:
    bool apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) override;
    std::string getName() const override;
};

#endif