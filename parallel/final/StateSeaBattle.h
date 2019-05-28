#pragma once

#include "RenderMap.h"

using point = std::pair<unsigned, unsigned>;

class StateSeBattle {
 public:
  StateSeBattle() {}

  void prepare();
  point fire();
  void result_fire(Shoot);
  Shoot attack(point);


  bool isFinish() { return isEnd; }

 private:
  unsigned countShip = 5;
  RenderMap renderMap;
  SeaBattleMap map;
  point last_fire;
  bool isEnd = false;

  void setShip();

};