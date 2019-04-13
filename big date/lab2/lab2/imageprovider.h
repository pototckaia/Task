#pragma once

#include <QObject>
#include <QString>
#include <QtCore>
#include <QImage>
#include <QVector>
#include <fstream>

class ImageProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage img MEMBER img NOTIFY imageChanged)

public:
    ImageProvider(QObject *parent = nullptr);

    Q_INVOKABLE void changeFrame();
    QImage img;

signals:
    void imageChanged();

private:
    int rows;
    int cols;
    int frame_count;

    const std::string fileName = "file1_400_400.json";
    long long beginkg = 0;

    bool isEnd = false;
    std::ifstream file;

    QColor getColor();
    void skipSpace(char c = ' ');

};
