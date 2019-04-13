#pragma once

#include <QObject>
#include <QString>
#include <QtCore>

#include <QVector>
#include <fstream>


class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rows MEMBER rows CONSTANT)
    Q_PROPERTY(int cols MEMBER cols CONSTANT)
    Q_PROPERTY(int frame_count MEMBER frame_count CONSTANT)
    Q_PROPERTY(QVariantList frame READ getNextFrame)

public:
    DataObject(QObject *parent = nullptr);

    QVariantList getNextFrame();
    bool end() { return isEnd; }


private:
    int rows;
    int cols;
    int frame_count;
    const std::string fileName = "file1_50_50.json";
    long long beginkg = 0;

   private:
    bool isEnd = false;
    std::ifstream file;

    QColor getColor();
    void skipSpace(char c = ' ');

};
