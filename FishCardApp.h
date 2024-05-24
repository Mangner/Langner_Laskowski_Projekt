#pragma once
#include <QString>
#include "TheMainWindow.h"

class Fishcard
{

private:
    QString front;
    QString back;

public:
    Fishcard(const QString& front, const QString& back);
    QString getFront();
    QString getBack();

    void addFishcard(MainWindow& window);

};


