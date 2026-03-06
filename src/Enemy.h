#ifndef ENEMY_H
#define ENEMY_H

#include <utility>

class GameField;
class Player;

class Enemy {
private:
    int hp;
    int damage;
    int maxHp;
    int x, y;

public:
    Enemy(int hp, int damage, int startX, int startY);
    int getX() const { return x; }
    int getY() const { return y; }
    int getHp() const { return hp; }
    
    void takeDamage(int amount);
    bool isAlive() const { return hp > 0; }
    int getMaxHp() const { return maxHp; }
    void moveTowardsPlayer(Player& player, const GameField& field);
};

#endif