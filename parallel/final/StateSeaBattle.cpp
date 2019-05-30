#include <iostream>
#include "StateSeaBattle.h"


void StateSeBattle::prepare() {
  std::cout << "Each ship occupies one cell. "
               "Ships should not touch "
               "(the minimum distance between ships is 1 square)" << std::endl;
  
  for (unsigned i = 0; i < countShip; ++i) {
    std::cout << "Player it's your fleet" << std::endl;
    std::cout << renderMap.toString(map.getMap(), map.sizeX, map.sizeY);
    std::cout << std::endl;
    setShip();
  }
}


void StateSeBattle::setShip() {
  PutShip state = PutShip::NotValidXY;
  unsigned x, y;

  while (state != PutShip::Put) {
    std::cout << "Enter coordinate to ship:" << std::endl;
    std::cout << "Target X coordinate: 1" << std::endl;
    std::cout << "Target Y coordinate: 2" << std::endl;
    std::cin >> x >> y;
    state = map.setShip(x, y);

    switch (state) {
      case PutShip::NotValidXY: {
        std::cout << "Coordinate to ship's abroad map" << std::endl;
        break;
      }
      case PutShip::TooClose: {
        std::cout << "Ships should not touch (the minimum distance between ships is 1 square)" << std::endl;
        break;
      }
      case PutShip::Busy: {
        std::cout << "The cell is already busy" << std::endl;
        break;
      }
      case PutShip::GameStart: {
        throw std::logic_error("set ship when game start");
      }
      default: {
        break;
      }
    }
    std::cout << std::endl;
  }
}

point StateSeBattle::fire() {
  bool valid = false;
  unsigned x, y;
  while (!valid) {
    std::cout << "Enter coordinate to fire:" << std::endl;
    std::cout << "Target X coordinate: 1" << std::endl;
    std::cout << "Target Y coordinate: 2" << std::endl;
    std::cin >> x >> y;
    if (x > map.sizeX || x > map.sizeY) {
      std::cout << "Coordinate to fire is abroad map" << std::endl;
      std::cout << std::endl;
      continue;
    }
    valid = true;
  }
  last_fire = std::make_pair(x, y);
  return last_fire;
}

void StateSeBattle::result_fire(Shoot s) {

  map.modifyEnemyMap(s, last_fire.first, last_fire.second);
  std::cout << renderMap.toString(map) << std::endl;
  std::cout << std::endl;

  switch (s) {
    case Shoot::Hit: {
      std::cout << "Player sank the ship in x : "
                << last_fire.first << " y : " << last_fire.second << std::endl;
      break;
    }
    case Shoot::Slip: {
      std::cout << "Player missed by in x : "
                << last_fire.first <<
                " y : " << last_fire.second << std::endl;
      break;
    }
    case Shoot::Win: {
      std::cout << "--- GAME END ---" << std::endl
                << "--- Player win --- " << std::endl;
      isEnd = true;
      break;
    }
    default: {
      break;
    }
  }
}

Shoot StateSeBattle::attack(point p) {
  auto r = map.shoot(p.first, p.second);
  std::cout << renderMap.toString(map) << std::endl;
  std::cout << std::endl;
  switch (r) {
    case Shoot::Hit: {
      std::cout << "Player lose ship under fire"
                << " in x : " << p.first
                << " y : " << p.second << std::endl;
      break;
    }
    case Shoot::Slip: {
      std::cout << "Player has been attacked"
                << " in x : " << p.first
                << " y : " << p.second
                << std::endl;
      break;
    }
    case Shoot::Win: {
      std::cout << "--- GAME END ---" << std::endl
                << "--- Player defeated, whole fleet destroyed--- " << std::endl;
      isEnd = true;
      break;
    }
    default: {
      break;
    }
  }
  return r;
}
