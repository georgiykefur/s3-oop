#ifndef ISPELL_H
#define ISPELL_H

#include <string>
#include <vector>

class GameField;
class Enemy;

class ISpell {
public:
    virtual ~ISpell() = default;
    virtual bool apply(int targetX, int targetY, GameField& field, std::vector<Enemy>& enemies) = 0;
    virtual std::string getName() const = 0;
};

#endif