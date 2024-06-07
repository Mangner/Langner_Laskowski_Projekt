#pragma once
#include <QString>


class Fishcard
{

private:
    QString front;
    QString back;

public:
    Fishcard() {};
    Fishcard(const QString& front, const QString& back);
    QString getFront() const;
    QString getBack() const;
    void setFront(QString newFront);
    void setBack(QString newBack);
};


