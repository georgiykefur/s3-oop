#include "TrapSpell.h"
#include "GameField.h"
#include "Enums.h"

bool TrapSpell::apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) {
    (void)enemies;
    if (targetX >= 0 && targetX < field.getWidth() && targetY >= 0 && targetY < field.getHeight()) {
        if (field.getCell(targetX, targetY).getType() == CellType::EMPTY) {
            field.setCellType(targetX, targetY, CellType::TRAP);
            return true;
        }
    }
    return false;
}

std::string TrapSpell::getName() const {
    return "Spike Trap";
}