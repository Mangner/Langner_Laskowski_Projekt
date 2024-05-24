#include "Fishcard.h"
#include "TheMainWindow.h"


Fishcard::Fishcard(const QString& front, const QString& back) : front(front), back(back) {}


QString Fishcard::getFront() const
{
	return this->front;
}




QString Fishcard::getBack() const
{
	return this->back;
}




void Fishcard::setFront(QString newFront)
{
	this->front = newFront;
}




void Fishcard::setBack(QString newBack)
{
	this->back = newBack;
}