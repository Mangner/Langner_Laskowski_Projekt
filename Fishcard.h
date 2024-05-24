#ifndef FISHCARD_H
#define FISHCARD_H
#include <QString>


class Fishcard
{

private:
    QString front;
    QString back;

public:
    Fishcard(const QString& front, const QString& back);
    QString getFront();
    QString getBack();
    void addFishcard();
};

#endif
#pragma once
