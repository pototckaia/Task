#include "RenderMap.h"


RenderMap::RenderMap()
  : str_betweenCol(betweenCol, ' '),
    str_betweenMap(betweenMap, ' ') {

}

char RenderMap::cellToChar(Cell c) {
  switch (c) {
    case Cell::Empty: {
      return '.';
    }
    case Cell::Ship: {
      return '#';
    }
    case Cell::DeadShip: {
      return 'X';
    }
    case Cell::SlipCell: {
      return '*';
    }
    case Cell::NotValid: {
      throw std::logic_error("Not valid cell");
    }
    default: {
      return ' ';
    }
  }
}

std::vector<std::string> RenderMap::lineX(unsigned sizeX) {
  std::string l(2, ' ');
  l += "X ";
  for (unsigned i = 0; i < sizeX; ++i) {
    l += std::to_string(i);
    if (i != sizeX - 1) {
      l += str_betweenCol;
    }
  }
  std::string sep(l.size(), '-');

  return {sep, l};
}

std::string RenderMap::indexY(unsigned pos) {
  std::string s = std::to_string(pos) + "|  ";
  return s;
}

std::vector<std::string> RenderMap::mapToString(const std::vector<Cell>& map,
                                                unsigned sizeX, unsigned sizeY) {
  std::vector<std::string> result;

  auto xx = lineX(sizeX);
  result.insert(result.begin(), xx.rbegin(), xx.rend());

  for (unsigned y = 0; y < sizeY; ++y) {
    std::string str_x(indexY(y));
    for (unsigned x = 0; x < sizeX; ++x) {
      str_x += cellToChar(map[x*sizeX+y]);
      if (x != sizeX - 1) str_x += str_betweenCol;
    }
    result.push_back(str_x);
  }
  std::string white(result.front().size() - 1, ' ');
  result.push_back("Y" + white);

  return result;
}

std::string RenderMap::toString(const std::vector<Cell>& map, unsigned sizeX, unsigned sizeY) {
  std::string s;
  auto v = mapToString(map, sizeX, sizeY);
  for (auto i = v.rbegin(); i != v.rend(); ++i) {
    s += *i + "\n";
  }

  return s;
}

std::string RenderMap::toString(SeaBattleMap& map) {
  auto v1 = mapToString(map.getMap(), map.sizeX, map.sizeY);
  auto v2 = mapToString(map.getEnemyMap(), map.sizeX, map.sizeY);

  std::string title1 = "Battlefield of Player";
  std::string title2 = "Battlefield of Govern";
  std::string sep(v1.back().size() - title1.size(), ' ');

  std::string result = title1 + sep + str_betweenMap + title2 + sep + "\n";

  for (auto i1 = v1.rbegin(), i2 = v2.rbegin(); i1 != v1.rend(); ++i1, ++i2) {
    result += *i1 + str_betweenMap + *i2 + "\n";
  }

  return result;
}