#include "SeaBattleMap.h"

#include <algorithm>

SeaBattleMap::SeaBattleMap()
  :
  sizeX(10), sizeY(10),
  gameStart(false),
  myMap(sizeX * sizeY, Cell::Empty),
  enemyMap(sizeX * sizeY, Cell::Empty) {

}


Cell SeaBattleMap::getCell(std::vector<Cell>& map, unsigned x, unsigned y) {
  if (x >= sizeX || y >= sizeY)
    return Cell::NotValid;
  return map[x * sizeX + y];
}


PutShip SeaBattleMap::setShip(unsigned x, unsigned y) {
  if (gameStart) {
    return PutShip::GameStart;
  }

  auto cell = getCell(myMap, x, y);
  if (cell == Cell::Ship) {
    return PutShip::Busy;
  } else if (cell == Cell::NotValid) {
    return PutShip::NotValidXY;
  }

  for (auto& e: maskCheckShip) {
    unsigned x_ = x + e.first, y_ = y + e.second;
    auto closeCell = getCell(myMap, x_, y_);
    if (closeCell == Cell::Ship) {
      return PutShip::TooClose;
    }
  }

  myMap[x * sizeX + y] = Cell::Ship;
  ship.emplace_back(x, y);
  return PutShip::Put;
}


Shoot SeaBattleMap::shoot(unsigned x, unsigned y) {
  gameStart = true;
  auto cell = getCell(myMap, x, y);
  switch (cell) {
    case Cell::NotValid: {
      return Shoot::NotValidXY;
    }
    case Cell::Empty: {
      myMap[x * sizeX + y] = Cell::SlipCell;
    }
    case Cell::SlipCell:
    case Cell::DeadShip: {
      return Shoot::Slip;
    }
    case Cell::Ship: {
      ship.erase(std::remove(ship.begin(), ship.end(), std::make_pair(x, y)), ship.end());
      myMap[x * sizeX + y] = Cell::DeadShip;
      if (ship.empty()) {
        return Shoot::Win;
      } else {
        return Shoot::Hit;
      }
    }
  }
}


void SeaBattleMap::modifyEnemyMap(Shoot s, unsigned x, unsigned y) {
  switch (s) {
    case Shoot::Hit: {
      enemyMap[x * sizeX + y] = Cell::DeadShip;
      return;
    }
    case Shoot::Slip: {
      enemyMap[x * sizeX + y] = Cell::SlipCell;
    }
    default: {
      return;
    }
  }
}

