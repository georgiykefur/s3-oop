#include "Enemy.h"
#include "Player.h"
#include "GameField.h"

Enemy::Enemy(int hp, int damage, int startX, int startY) 
    : hp(hp), damage(damage), maxHp(hp), x(startX), y(startY) {}

void Enemy::moveTowardsPlayer(Player& player, const GameField& field) {
    int pX = player.getPosition().first;
    int pY = player.getPosition().second;

    int nextX = x;
    int nextY = y;

    if (x < pX) nextX++;
    else if (x > pX) nextX--;
    else if (y < pY) nextY++;
    else if (y > pY) nextY--;

    if (nextX == pX && nextY == pY) {
        player.takeDamage(damage);
        return; 
    }

    if (field.isObstacle(nextX, nextY)) {
        return;
    }

    x = nextX;
    y = nextY;
}

void Enemy::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}