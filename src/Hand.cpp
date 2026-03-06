#include "Hand.h"

#include <random>

Hand::Hand(size_t size) : maxSize(size) {}

bool Hand::addSpell(std::unique_ptr<ISpell> spell) {
    if (spells.size() < maxSize) {
        spells.push_back(std::move(spell));
        return true;
    }
    return false;
}

bool Hand::castSpell(size_t index, int x, int y, GameField& field, std::vector<Enemy>& enemies) {
    if (index < spells.size()) {
        if (spells[index]->apply(x, y, field, enemies)) {
            spells.erase(spells.begin() + index);
            return true; 
        }
    }
    return false; 
}

void Hand::removeHalfSpells() {
    if (spells.empty()) return;
    size_t countToRemove = spells.size() / 2;
    for (size_t i = 0; i < countToRemove; ++i) {
        int idx = std::rand() % spells.size();
        spells.erase(spells.begin() + idx);
    }
}