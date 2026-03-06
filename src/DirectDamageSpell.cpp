#include "DirectDamageSpell.h"
#include "Enemy.h"
#include "GameField.h"

bool DirectDamageSpell::apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) {
    (void)field;
    for (auto& e : enemies) {
        if (e.getX() == targetX && e.getY() == targetY) {
            e.takeDamage(50);
            return true;
        }
    }
    return false;
}

std::string DirectDamageSpell::getName() const {
    return "Fireball (Direct)";
}