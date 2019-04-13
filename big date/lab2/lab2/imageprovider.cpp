#include "imageprovider.h"

#include <QColor>
#include <QPoint>
#include <QImage>
#include <QtCore>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cctype>

ImageProvider::ImageProvider(QObject *parent)
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
  img = QImage(this->cols, this->rows, QImage::Format_RGB888);
}

void ImageProvider::changeFrame() { // [...]
  skipSpace(); // begin frame -'['
  file.get(); // '['

  int i = 0;
  while (file.peek() != ']') {
    auto color = getColor();
    int row = i % this->cols;
    int col = i / this->rows;
    this->img.setPixelColor(col, row, color);

    skipSpace(',');
    ++i;
  }

  file.get(); // end frame - ']'
  skipSpace(',');

  isEnd = file.peek() == ']';
  if (isEnd) {
    isEnd = false;
    file.seekg(beginkg);
  }

  emit imageChanged();
}

QColor ImageProvider::getColor() {
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

void ImageProvider::skipSpace(char c) {
    while (std::isspace(file.peek()) || file.peek() == c) {
      file.get();
    }
}

