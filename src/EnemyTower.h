#ifndef ENEMYTOWER_H
#define ENEMYTOWER_H

class Player;

class EnemyTower {
private:
    int x, y;
    int damage;
    int range;
    int cooldown;       
    int currentCooldown; 

public:
    EnemyTower(int x, int y, int dmg, int rng, int cd);
    int update(Player& player); 
    int getX() const { return x; }
    int getY() const { return y; }
};

#endif