#include "Player.h"

Player::Player(int startHp) 
    : hp(startHp), damage(15), score(0), mode(CombatMode::MELEE), hand(3) {
    position = {1, 1};
}

int Player::getHp() const { 
    return hp; 
}

int Player::getDamage() const { 
    return damage; 
}

int Player::getScore() const { 
    return score; 
}

std::pair<int, int> Player::getPosition() const { 
    return position; 
}

CombatMode Player::getMode() const { 
    return mode; 
}

void Player::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Player::addScore(int points) {
    score += points; 
    if (score < 0) score = 0; 
}

void Player::setPosition(int x, int y) {
    position = {x, y};
}

void Player::setHp(int hpoint){
    hp = hpoint;
}

void Player::switchMode() {
    if (mode == CombatMode::MELEE) {
        mode = CombatMode::RANGED;
        damage = 5; 
    } else {
        mode = CombatMode::MELEE;
        damage = 15;
    }
}

Hand& Player::getHand() {
    return hand;
}