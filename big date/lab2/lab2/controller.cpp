#include "controller.h"

#include <QColor>
#include <QtCore>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cctype>

DataObject::DataObject(QObject *parent)
  : QObject(parent), file(fileName) {
  skipSpace('{'); // begin - {

  file.seekg(int(file.tellg()) + 7); // "width" - 7
  skipSpace(':');
  file >> rows;
  skipSpace(',');

  file.seekg(int(file.tellg()) + 8); // "height" - 8
  skipSpace(':');
  file >> cols;
  skipSpace(',');

  file.seekg(int(file.tellg()) + 8); // "frames" - 8
  skipSpace(':');
  file >> frame_count;
  skipSpace(',');

  file.seekg(int(file.tellg()) + 11); // "animation" - 11
  skipSpace(':');

  skipSpace();
  file.get(); // [

  beginkg = file.tellg();
}

QVariantList DataObject::getNextFrame() { // [...]
  QVariantList f;
  skipSpace(); // begin frame -'['
  file.get(); // '['

  while (file.peek() != ']') {
    f << QVariant::fromValue(getColor());
    skipSpace(',');
  }

  file.get(); // end frame - ']'
  skipSpace(',');

  isEnd = file.peek() == ']';
  if (isEnd) {
    isEnd = false;
    file.seekg(beginkg);
  }

  return f;
}

QColor DataObject::getColor() {
  skipSpace();
  if (file.peek() != '[') {
    throw std::logic_error("ArrayInt begin not [");
  }
  file.get(); // '['

  std::vector<int> rgb;
  while(file.peek() != ']') {
    skipSpace(',');
    int number;
    file >> number;
    rgb.push_back(number);
  }

  QColor color(rgb.at(0), rgb.at(1), rgb.at(2));
  file.get(); // ']'
  return color;
}

void DataObject::skipSpace(char c) {
    while (std::isspace(file.peek()) || file.peek() == c) {
      file.get();
    }
}

