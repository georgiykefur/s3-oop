#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "GameField.h"
#include "GameCell.h"
#include "Enums.h"
#include "DirectDamageSpell.h"
#include "AreaDamageSpell.h"
#include "TrapSpell.h"
#include "GameExceptions.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Game::Game() : field(15, 15), player(100), currentLevel(1), isRunning(true), inMenu(true) {
    // initLevel(currentLevel);
}

void Game::initLevel(int levelNum) {
    // Новое поле 
    int size = 15 + levelNum;
    if (size > 25) size = 25;
    field = GameField(size, size); 

    // Игрок
    player.setPosition(1, 1);
    player.setHp(100); 

    if (levelNum == 1) {
        if (player.getHand().getSpells().empty()) {
            int r = std::rand() % 3;
            if (r == 0) player.getHand().addSpell(std::make_unique<DirectDamageSpell>());
            else if (r == 1) player.getHand().addSpell(std::make_unique<AreaDamageSpell>());
            else player.getHand().addSpell(std::make_unique<TrapSpell>());
        }
    } else {
        player.getHand().removeHalfSpells();
        addLog("Level UP! HP restored, half spells lost.");
    }

    // Враги 
    enemies.clear();
    for (int i = 0; i < 1 + levelNum; ++i) {
        enemies.push_back(Enemy(30 + levelNum * 10, 5 + levelNum * 2, 5 + i * 2, 5 + i));
    }

    // Башни
    towers.clear();
    towers.push_back(EnemyTower(size - 3, size - 3, 10 + levelNum, 3, 2));
}

void Game::saveGame(const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) throw FileException(filename);

    // Уровень, HP, Score
    ofs.write(reinterpret_cast<char*>(&currentLevel), sizeof(int));
    int hp = player.getHp();
    ofs.write(reinterpret_cast<char*>(&hp), sizeof(int));
    int score = player.getScore();
    ofs.write(reinterpret_cast<char*>(&score), sizeof(int));

    // Координаты игрока
    auto pos = player.getPosition();
    int px = pos.first;
    int py = pos.second;
    ofs.write(reinterpret_cast<char*>(&px), sizeof(int));
    ofs.write(reinterpret_cast<char*>(&py), sizeof(int));

    // Параметры поля
    int w = field.getWidth();
    int h = field.getHeight();
    ofs.write(reinterpret_cast<char*>(&w), sizeof(int));
    ofs.write(reinterpret_cast<char*>(&h), sizeof(int));

    // Клетки поля
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            CellType type = field.getCell(x, y).getType();
            ofs.write(reinterpret_cast<char*>(&type), sizeof(CellType));
        }
    }

    // Враги
    size_t eCount = enemies.size();
    ofs.write(reinterpret_cast<char*>(&eCount), sizeof(size_t));
    for (const auto& e : enemies) {
        int ex = e.getX();
        int ey = e.getY();
        int ehp = e.getHp();
        ofs.write(reinterpret_cast<char*>(&ex), sizeof(int));
        ofs.write(reinterpret_cast<char*>(&ey), sizeof(int));
        ofs.write(reinterpret_cast<char*>(&ehp), sizeof(int));
    }
    
    addLog("Game saved successfully!");
}

void Game::loadGame(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) throw FileException(filename);

    // Читаем базовые параметры
    int level, hp, score, px, py;
    ifs.read(reinterpret_cast<char*>(&level), sizeof(int));
    ifs.read(reinterpret_cast<char*>(&hp), sizeof(int));
    ifs.read(reinterpret_cast<char*>(&score), sizeof(int));
    ifs.read(reinterpret_cast<char*>(&px), sizeof(int));
    ifs.read(reinterpret_cast<char*>(&py), sizeof(int));
    
    currentLevel = level;

    // Читаем и восстанавливаем поле
    int w, h;
    ifs.read(reinterpret_cast<char*>(&w), sizeof(int));
    ifs.read(reinterpret_cast<char*>(&h), sizeof(int));

    field = GameField(w, h); 
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            CellType type;
            ifs.read(reinterpret_cast<char*>(&type), sizeof(CellType));
            field.setCellType(x, y, type);
        }
    }

    // Применяем данные игрока 
    player.setHp(hp);
    player.addScore(score - player.getScore());
    player.setPosition(px, py); 

    // Загрузка врагов
    size_t eCount;
    ifs.read(reinterpret_cast<char*>(&eCount), sizeof(size_t));
    enemies.clear();
    for (size_t i = 0; i < eCount; ++i) {
        int ex, ey, ehp;
        ifs.read(reinterpret_cast<char*>(&ex), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&ey), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&ehp), sizeof(int));
        enemies.push_back(Enemy(ehp, 5 + currentLevel * 2, ex, ey));
    }

    // Восстанавливаем башни
    towers.clear();
    towers.push_back(EnemyTower(w - 3, h - 3, 10 + currentLevel, 3, 2));

    addLog("Game loaded from file!");
}

void Game::showMenu() {
    system("clear");
    std::cout << "=== DUNGEONS AND DRAGONS (LOW COST) ===" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Choice: ";
    
    char choice;
    std::cin >> choice;
    if (choice == '1') {
        currentLevel = 1;
        initLevel(currentLevel);
        inMenu = false;
    } else if (choice == '2') {
        try {
            loadGame("save.dat");
            inMenu = false;
        } catch (const GameException& e) {
            std::cout << e.what() << " Press Enter..." << std::endl;
            std::cin.ignore(); std::cin.get();
        }
    } else {
        isRunning = false;
    }
}

void Game::render() {
    system("clear"); 

    // Шапка
    std::cout << "================ [ LEVEL " << currentLevel << " ] ================" << std::endl;
    std::cout << " [ PLAYER ] HP: " << player.getHp() << "/100 | Score: " << player.getScore() 
              << " | Mode: " << (player.getMode() == CombatMode::MELEE ? "MELEE" : "RANGED") << std::endl;
    
    // Список врагов
    std::cout << " [ ENEMIES ] " << std::endl;
    if (enemies.empty()) {
        std::cout << "  Area clear! Go to the next level." << std::endl;
    } else {
        for (size_t i = 0; i < enemies.size(); ++i) {
            int bars = (enemies[i].getHp() * 10) / enemies[i].getMaxHp();
            std::cout << "  E" << i+1 << ": " << enemies[i].getHp() << " HP [";
            for(int b=0; b<10; b++) std::cout << (b < bars ? "=" : " ");
            std::cout << "]" << std::endl;
        }
    }
    std::cout << "--------------------------------------------" << std::endl;

    // Отрисовка карты
    for (int y = 0; y < field.getHeight(); ++y) {
        std::cout << "  ";
        for (int x = 0; x < field.getWidth(); ++x) {
            // Приоритет: Игрок > Враг > Башня > Клетка поля
            if (x == player.getPosition().first && y == player.getPosition().second) {
                std::cout << "P ";
            } else {
                int enemyIdx = -1;
                for (size_t i = 0; i < enemies.size(); ++i) {
                    if (enemies[i].getX() == x && enemies[i].getY() == y) {
                        enemyIdx = i; break;
                    }
                }

                if (enemyIdx != -1) {
                    std::cout << "E" << enemyIdx + 1; 
                } else {
                    bool towerFound = false;
                    for (const auto& t : towers) {
                        if (t.getX() == x && t.getY() == y) {
                            std::cout << "T "; towerFound = true; break;
                        }
                    }

                    if (!towerFound) {
                        CellType t = field.getCell(x, y).getType();
                        if (t == CellType::TRAP) std::cout << "^ ";
                        else if (t == CellType::OBSTACLE) std::cout << "# ";
                        else std::cout << ". ";
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    // Лог событий
    std::cout << "---------- [ BATTLE LOG ] ----------" << std::endl;
    for (const auto& log : battleLog) {
        std::cout << " > " << log << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;

    // Управление
    auto& spells = player.getHand().getSpells();
    std::cout << " Spells: ";
    for (size_t i = 0; i < spells.size(); ++i) std::cout << "[" << i+1 << ":" << spells[i]->getName() << "] ";
    std::cout << "\n [WASD]-Move [F]-Attack [M]-Mode [1-3]-Spell [B]-Buy" << std::endl;
    std::cout << " [O]-Save [L]-Load [Q]-Quit" << std::endl;
}

void Game::handleInput() {
    char input;
    std::cout << "Command: ";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool turnTaken = false;

    try {
        if (input == 'q') { isRunning = false; return; }
        if (input == 'o') { saveGame("save.dat"); return; } 
        if (input == 'l') { loadGame("save.dat"); return; } 

        if (input == 'm') {
            player.switchMode();
            addLog("Switched combat mode.");
            turnTaken = false; 
        } 
        else if (input == 'w' || input == 's' || input == 'a' || input == 'd') {
            int nextX = player.getPosition().first;
            int nextY = player.getPosition().second;
            if (input == 'w') nextY--; if (input == 's') nextY++;
            if (input == 'a') nextX--; if (input == 'd') nextX++;

            if (nextX >= 0 && nextX < field.getWidth() && nextY >= 0 && nextY < field.getHeight()) {
                if (!field.isObstacle(nextX, nextY)) {
                    player.setPosition(nextX, nextY);
                    turnTaken = true; 
                } else addLog("Blocked by wall!");
            }
        }
        // Покупка
        else if (input == 'b') { 
            if (player.getScore() >= 50) {
                std::unique_ptr<ISpell> newSpell;
                int r = std::rand() % 3;
                if (r == 0) newSpell = std::make_unique<DirectDamageSpell>();
                else if (r == 1) newSpell = std::make_unique<AreaDamageSpell>();
                else newSpell = std::make_unique<TrapSpell>();

                if (player.getHand().addSpell(std::move(newSpell))) {
                    player.addScore(-50);
                    addLog("Bought new spell!");
                    turnTaken = true; 
                } else {
                    addLog("Hand is full! (Turn not wasted)");
                }
            } else {
                addLog("Not enough score! (Turn not wasted)");
            }
        }
        // Магия
        else if (input >= '1' && input <= '3') { 
            size_t idx = static_cast<size_t>(input - '1');
            if (idx < player.getHand().getSpells().size()) {
                std::cout << "Direction (WASD) for spell: ";
                char dir; std::cin >> dir;
                int tx = player.getPosition().first;
                int ty = player.getPosition().second;
                if (dir == 'w') ty--; if (dir == 's') ty++; if (dir == 'a') tx--; if (dir == 'd') tx++;
                
                if(player.getHand().castSpell(idx, tx, ty, field, enemies)) {
                    addLog("Magic applied!");
                    turnTaken = true; 
                } else {
                    addLog("Spell target invalid! (Turn not wasted)");
                }
            }
        }
        else if (input == 'f') {
            int px = player.getPosition().first, py = player.getPosition().second;
            bool hit = false;
            for (size_t i = 0; i < enemies.size(); ++i) {
                if (std::abs(enemies[i].getX() - px) <= 1 && std::abs(enemies[i].getY() - py) <= 1) {
                    enemies[i].takeDamage(player.getDamage());
                    addLog("Hit E" + std::to_string(i+1) + "!");
                    hit = true; 
                    break;
                }
            }
            if (!hit) addLog("Player swings at air...");
            
            turnTaken = true; 
        }
    } 
    catch (const GameException& e) {
        addLog(e.what());
    }

    // ВРАГИ ХОДЯТ ТОЛЬКО ЕСЛИ ИГРОК ПОТРАТИЛ ХОД
    if (turnTaken) {
        for (auto& e : enemies) {
            e.moveTowardsPlayer(player, field);
        }
    }
}

void Game::update() {
    // Атака башен 
    for (size_t i = 0; i < towers.size(); ++i) {
        int dmgTaken = towers[i].update(player);
        if (dmgTaken > 0) addLog("Tower T" + std::to_string(i+1) + " shot you! -" + std::to_string(dmgTaken) + " HP");
    }

    // Ловушки 
    for (auto& e : enemies) {
        if (field.getCell(e.getX(), e.getY()).getType() == CellType::TRAP) {
            e.takeDamage(40);
            field.setCellType(e.getX(), e.getY(), CellType::EMPTY);
            addLog("Enemy hit by TRAP!");
        }
    }

    // Обработка смертей врагов
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (it->getHp() <= 0) {
            player.addScore(100);
            addLog("Enemy defeated! +100 Score");
            it = enemies.erase(it);
        } else ++it;
    }

    // Условие победы
    if (enemies.empty()) {
        currentLevel++;
        initLevel(currentLevel); 
    }

    // Условие поражения
    if (player.getHp() <= 0) {
        render(); 
        std::cout << "\n[ YOU DIED ] 1. Restart Level  2. Exit to Menu" << std::endl;
        char choice; std::cin >> choice;
        if (choice == '1') {
            initLevel(currentLevel);
        } else {
            inMenu = true;
            currentLevel = 1;
        }
    }
}
void Game::run() {
    while (isRunning) {
        if (inMenu) {
            showMenu();
        } else {
            render();
            handleInput();
            update();
        }
    }
}

void Game::addLog(const std::string& msg) {
    battleLog.push_back(msg);
    if (battleLog.size() > 5) {
        battleLog.erase(battleLog.begin());
    }
}

