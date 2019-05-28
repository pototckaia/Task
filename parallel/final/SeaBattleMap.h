#pragma once

#include <vector>
#include <array>

enum Shoot {
  Hit, // попал
  Slip, // промазал
  Win,
  NotValidXY
};

enum class Cell {
  Empty,
  Ship,
  DeadShip,
  SlipCell,
  NotValid
};

enum class PutShip {
  Put,
  Busy,
  TooClose,
  NotValidXY,
  GameStart
};

class SeaBattleMap {
 public:
  SeaBattleMap();

  PutShip setShip(unsigned x, unsigned y);
  Shoot shoot(unsigned x, unsigned y);
  void modifyEnemyMap(Shoot s, unsigned x, unsigned y);

  const unsigned sizeX;
  const unsigned sizeY;
  const std::vector<Cell>& getMap() { return myMap; }
  const std::vector<Cell>& getEnemyMap() { return enemyMap; }


 private:
  bool gameStart;

  std::vector<Cell> myMap;
  std::vector<Cell> enemyMap;

  Cell getCell(std::vector<Cell>& c, unsigned x, unsigned y);

  std::vector<std::pair<unsigned, unsigned>> ship;

  const std::vector<std::pair<int, int>> maskCheckShip =
    {{-1, 1},
     {0,  1},
     {1,  1},
     {-1, 0},
     {1,  0},
     {-1, -1},
     {0,  -1},
     {1,  -1}};
};
