CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = game

OBJS = main.o Game.o GameField.o Player.o Enemy.o GameCell.o Hand.o \
       DirectDamageSpell.o AreaDamageSpell.o TrapSpell.o EnemyTower.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Game.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h GameField.h Player.h Enemy.h GameExceptions.h DirectDamageSpell.h AreaDamageSpell.h TrapSpell.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

GameField.o: GameField.cpp GameField.h GameCell.h Enums.h
	$(CXX) $(CXXFLAGS) -c GameField.cpp

Player.o: Player.cpp Player.h Enums.h Hand.h
	$(CXX) $(CXXFLAGS) -c Player.cpp

Enemy.o: Enemy.cpp Enemy.h Player.h GameField.h
	$(CXX) $(CXXFLAGS) -c Enemy.cpp

GameCell.o: GameCell.cpp GameCell.h Enums.h
	$(CXX) $(CXXFLAGS) -c GameCell.cpp

Hand.o: Hand.cpp Hand.h ISpell.h
	$(CXX) $(CXXFLAGS) -c Hand.cpp

DirectDamageSpell.o: DirectDamageSpell.cpp DirectDamageSpell.h ISpell.h Enemy.h GameField.h
	$(CXX) $(CXXFLAGS) -c DirectDamageSpell.cpp

AreaDamageSpell.o: AreaDamageSpell.cpp AreaDamageSpell.h ISpell.h Enemy.h GameField.h
	$(CXX) $(CXXFLAGS) -c AreaDamageSpell.cpp

TrapSpell.o: TrapSpell.cpp TrapSpell.h ISpell.h GameField.h Enums.h
	$(CXX) $(CXXFLAGS) -c TrapSpell.cpp

EnemyTower.o: EnemyTower.cpp EnemyTower.h Player.h
	$(CXX) $(CXXFLAGS) -c EnemyTower.cpp

clean:
	rm -f $(OBJS) $(TARGET)