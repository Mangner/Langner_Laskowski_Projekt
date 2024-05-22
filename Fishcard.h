#ifndef FISHCARD_H
#define FISHCARD_H

#include <QString>

class Fishcard 
{
public:
    QString front;
    QString back;

    Fishcard(const QString& front, const QString& back);
    void flip();
};

#endif
#pragma once
