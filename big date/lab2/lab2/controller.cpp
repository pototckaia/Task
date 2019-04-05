#include "controller.h"

#include <QtCore>
#include <algorithm>
#include <iostream>
#include <stdexcept>


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
    auto rgb = getArrayInt();

    double lowest = std::min(std::min(rgb.at(0).toDouble(), rgb.at(1).toDouble()), rgb.at(2).toDouble());// red, green, blue
    double a = (255 - lowest) / 255;
    double r = (rgb.at(0).toDouble() - lowest) / a;
    double g = (rgb.at(1).toDouble() - lowest) / a;
    double b = (rgb.at(2).toDouble() - lowest) / a;

    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    rgb << QVariant::fromValue(a);

    f << QVariant::fromValue(rgb);

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

QVariantList DataObject::getArrayInt() {
  QVariantList array;
  skipSpace();
  if (file.peek() != '[') {
    throw std::logic_error("ArrayInt begin not [");
  }
  file.get(); // '['

  while(file.peek() != ']') {
    skipSpace(',');
    int number;
    file >> number;
    array << QVariant::fromValue(number);
  }

  file.get(); // ']'
  return array;
}

void DataObject::skipSpace(char c) {
    while (std::isspace(file.peek()) || file.peek() == c) {
      file.get();
    }
}

