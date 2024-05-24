#pragma once
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
};


