#include "Fishcard.h"
#include "TheMainWindow.h"
#include "InputError.h"


Fishcard::Fishcard(const QString& front, const QString& back)
{
	char wrongSign = ':';
	
	std::string frontAsStdString = front.toStdString();

	if (frontAsStdString.find(':') != std::string::npos)
	{
		throw InputError();
	}
	

	std::string backAsStdString = back.toStdString();
	if (backAsStdString.find(':') != std::string::npos)
	{
		throw InputError();
	}


	this->front = front;
	this->back = back;
}



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