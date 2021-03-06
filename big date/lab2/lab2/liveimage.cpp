#include "liveimage.h"

LiveImage::LiveImage(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_image() {}

void LiveImage::paint(QPainter *painter) {
    painter->drawImage(0, 0, m_image);
}

void LiveImage::setImage(const QImage &image) {
    m_image = image;
    update();
}
