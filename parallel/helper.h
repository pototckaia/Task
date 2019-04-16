#pragma once
#include <iomanip>
#include <iostream>

void n(int n) {
  std::cout << std::endl;
  std::cout << "Часть " << n << std::endl;
}

template<typename T> void printElement(T t) {
  const long width = 20 ;
  const char separator = ' ';
  const char barrier = '|';
  std::cout << std::right << std::setw(width) << std::setfill(separator) << std::setprecision(4) 
            << t << barrier ;
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

void printHeader5() {
  printElement("Thread");
  printElement("Type");
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

template <typename T, typename D>
void printLine(long j, std::string type, T result, D duration) {
  printElement(j);
  printElement(type);
  printElement(result);
  printElement(duration);
  printNewLine();
}