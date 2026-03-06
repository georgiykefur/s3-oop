#ifndef PLAYER_H
#define PLAYER_H

#include "Enums.h"
#include "Hand.h"
#include <utility>

class Player {
private:
    int hp;
    int damage;
    int score;
    std::pair<int, int> position;
    CombatMode mode;
    Hand hand; 

public:
    Player(int startHp); 

    int getHp() const;
    int getDamage() const;
    int getScore() const;
    std::pair<int, int> getPosition() const;
    CombatMode getMode() const;
    Hand& getHand(); 

    void takeDamage(int amount);
    void addScore(int points);
    void setPosition(int x, int y);
    void setHp(int hp);
    void switchMode();
};

#endif