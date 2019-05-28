#pragma once

#include "SeaBattleMap.h"

class RenderMap {
 public:
  RenderMap();
  std::string toString(const std::vector<Cell>&, unsigned, unsigned);
  std::string toString(SeaBattleMap& map);

 private:

  const unsigned betweenCol = 2;
  const unsigned betweenMap = 5;
  const std::string str_betweenCol;
  const std::string str_betweenMap;

  char cellToChar(Cell);
  std::vector<std::string> lineX(unsigned);

  std::string indexY(unsigned);
  std::vector<std::string> mapToString(const std::vector<Cell>&, unsigned, unsigned);
};
