#pragma once

#include <QImage>
#include <QQuickPaintedItem>
#include <QPainter>

class LiveImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image MEMBER m_image WRITE setImage)

    // Just storage for the image
    QImage m_image;

public:
    explicit LiveImage(QQuickItem *parent = nullptr);
    void setImage(const QImage &image);
    void paint(QPainter *painter) override;
};
