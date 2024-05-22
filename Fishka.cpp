#include "Fishcard.h"

Fishcard::Fishcard(const QString& front, const QString& back)
    : front(front), back(back) {}

void Fishcard::flip() 
{
    QString temp = this->front;
    this->front = this->back;
    this->back = temp;
}
