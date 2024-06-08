#include "Fishcard.h"
#include "TheMainWindow.h"
#include "InputError.h"


Fishcard::Fishcard(const QString& front, const QString& back)
{
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
	std::string frontAsStdString = newFront.toStdString();


	if (frontAsStdString.find(':') != std::string::npos)
	{
		throw InputError();
	}

	this->front = newFront;
}




void Fishcard::setBack(QString newBack)
{
	std::string backAsStdString = newBack.toStdString();


	if (backAsStdString.find(':') != std::string::npos)
	{
		throw InputError();
	}

	this->back = newBack;
}