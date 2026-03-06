#include "EnemyTower.h"
#include "Player.h"
#include <cmath>

EnemyTower::EnemyTower(int x, int y, int dmg, int rng, int cd) 
    : x(x), y(y), damage(dmg), range(rng), cooldown(cd), currentCooldown(0) {}

int EnemyTower::update(Player& player) {
    if (currentCooldown > 0) {
        currentCooldown--;
        return 0;
    }

    int px = player.getPosition().first;
    int py = player.getPosition().second;
    double dist = std::sqrt(std::pow(x - px, 2) + std::pow(y - py, 2));

    if (dist <= range) {
        player.takeDamage(damage);
        currentCooldown = cooldown;
        return damage; 
    }
    return 0;
}