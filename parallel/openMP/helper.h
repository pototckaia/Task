#pragma once
#include <iomanip>
#include <iostream>

void n(int n) {
  std::cout << std::endl;
  std::cout << "Часть " << n << std::endl;
}

template<typename T> void printElement(T t) {
  const long width = 15;
  const char separator = ' ';
  const char barrier = '|';
  std::cout << std::right << std::setw(width) << std::setfill(separator) << t << barrier ;
}

void printNewLine() {
  std::cout << std::endl;
}


void printHeader() {
  printElement("Thread");
  printElement("Result");
  printElement("Duration (ms)");
  printNewLine();
}


template <typename T, typename D>
void printLine(long j, T result, D duration) {
  printElement(j);
  printElement(result);
  printElement(duration);
  printNewLine();
}