#include "TheMainWindow.h"
#include <iostream>
#include <fstream>
#include <algorithm>



void MainWindow::loadFishCards()
{
	std::ifstream fishCardSet("fishCards.txt");

	if (!fishCardSet)
	{
		std::cout << "Nie mozna otworzyc pliku." << std::endl;
		return;
	}

	std::string line;
	char devider = ':';

	while (std::getline(fishCardSet, line))
	{
		auto deviderPosition = std::find(line.begin(), line.end(), devider);
		std::string file_front(line.begin(), deviderPosition);
		std::string file_back(deviderPosition + 1, line.end());

		QString front = QString::fromStdString(file_front);
		QString back = QString::fromStdString(file_back);

		Fishcard newCard(front, back);
		fishcards.append(newCard);
		ui.Fishka_list_Box->addItem(QString::number(ui.Fishka_list_Box->currentIndex() + 2) + ". " + newCard.getFront());

		QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(newCard.getFront());
		ui.fishcard_Box->setHtml(text);

		ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1);
	}

	fishCardSet.close();
}




void MainWindow::checkIfDuplicate()
{

}