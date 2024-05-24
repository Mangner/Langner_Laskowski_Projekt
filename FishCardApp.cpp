#include "Fishcard.h"
#include "qinputdialog.h"

Fishcard::Fishcard(const QString& front, const QString& back) : front(front), back(back) {}


QString Fishcard::getFront()
{
	return this->front;
}


QString Fishcard::getBack()
{
	return this->back;
}



