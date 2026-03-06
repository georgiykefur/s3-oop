#include "AreaDamageSpell.h"
#include "Enemy.h"
#include "GameField.h"

bool AreaDamageSpell::apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) {
    (void)field;
    for (auto& e : enemies) {
        if ((e.getX() == targetX || e.getX() == targetX + 1) &&
            (e.getY() == targetY || e.getY() == targetY + 1)) {
            e.takeDamage(30);
        }
    }
    return true;
}

std::string AreaDamageSpell::getName() const {
    return "Blizzard (Area 2x2)";
}