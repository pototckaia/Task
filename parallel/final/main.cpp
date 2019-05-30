#include <iostream>
#include <random>

#include "StateSeaBattle.h"


unsigned getRandom(std::mt19937& mt) {
  std::uniform_int_distribution<int> dist(0, 9);
  return (unsigned) dist(mt);
}

Shoot getRandomShoot(std::mt19937& mt) {
  static Shoot sh[3] = {Shoot::Hit, Shoot::Slip, Shoot::Win};
  std::uniform_int_distribution<int> dist(-10000, 10000);

  int i = dist(mt);
  int res = i % 3;
  return sh[res];
}


int main() {
  StateSeBattle s;

  std::random_device rd;
  std::mt19937 mt(rd());

  s.prepare();

  while (!s.isFinish()) {
    s.attack(std::make_pair(getRandom(mt), getRandom(mt)));

    if (s.isFinish()) break;

    s.fire();
    s.result_fire(getRandomShoot(mt));
  }


  return 0;
}