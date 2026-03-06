#ifndef GAME_H
#define GAME_H

#include <vector> 
#include <string>
#include "GameField.h"
#include "Player.h"
#include "Enemy.h" 
#include "EnemyTower.h"
#include <iostream>

class Game {
private:
    GameField field;
    Player player;
    std::vector<Enemy> enemies; 
    std::vector<std::string> battleLog;
    std::vector<EnemyTower> towers;

    int currentLevel;
    bool isRunning;
    bool inMenu;

    void addLog(const std::string& msg);
    void render();
    void handleInput();
    void update();
    void initLevel(int levelNum);
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);
    void showMenu(); 

public:
    Game();
    void run();
};

#endif