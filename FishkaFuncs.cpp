#include "TheMainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QAbstractButton>
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "InputError.h"
#include <string>



void MainWindow::addFishka()
{
    bool ok;
    QString front = QInputDialog::getText(this, tr("New Fishcard"), tr("Input word in polish:"), QLineEdit::Normal, QString(), &ok).trimmed();
    if (!ok || front.isEmpty())
        return;

    QString back = QInputDialog::getText(this, tr("New Fishcard"), tr("Input word in other language:"), QLineEdit::Normal, QString(), &ok).trimmed();
    if (!ok || back.isEmpty())
        return;

    Fishcard newCard;


    try
    {
        newCard = Fishcard(front, back);
    }
    catch (const InputError& error)
    {
        std::string communicate = std::string(error.what());
        QMessageBox::warning(this, tr("Invalid Input."), QString::fromStdString(communicate));
        return;
    }
    catch (const std::exception& error)
    {
        QMessageBox::warning(this, tr("Unknown Error"), tr("Unknown Error."));
        return;
    }



    fishcards.append(newCard);
    ui.Fishka_list_Box->addItem(QString::number(ui.Fishka_list_Box->currentIndex() + 2) + ". " + newCard.getFront());


    QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(newCard.getFront());
    ui.fishcard_Box->setHtml(text);

    ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1);


    std::ofstream FishCardsSet("fishCards.txt", std::ios::app);
    FishCardsSet << (newCard.getFront()).toStdString() << ":" << (newCard.getBack()).toStdString() << std::endl;
    FishCardsSet.close();

    for (int i = 0; i < fishcards.size(); ++i)
    {
        QString displayText = QString::number(i + 1) + ". " + fishcards[i].getFront();
        ui.Fishka_list_Box->setItemText(i, displayText);
    }
}




void MainWindow::displaySelectedFishka(int index)
{
    if (index >= 0 && index < fishcards.size())
    {
        Fishcard selectedCard = fishcards[index];
        QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(selectedCard.getFront());
        ui.fishcard_Box->setHtml(text);
    }
}




void MainWindow::removeFishka()
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    if (currentIndex != -1)
    {
        Fishcard currentFishCard = fishcards[currentIndex];
        std::string lineToRemove = currentFishCard.getFront().toStdString() + ":" + currentFishCard.getBack().toStdString();


        fishcards.removeAt(currentIndex);
        ui.Fishka_list_Box->removeItem(currentIndex);

       
        for (int i = currentIndex; i < fishcards.size(); ++i)
        {
            std::string displayText = std::to_string(i + 1) + ". " + fishcards[i].getFront().toStdString();
            ui.Fishka_list_Box->setItemText(i, QString::fromStdString(displayText));
        }


        if (currentIndex < fishcards.size())
        {
            ui.Fishka_list_Box->setCurrentIndex(currentIndex);
        }
        else if (!fishcards.isEmpty())
        {
            ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1);
        }


        std::vector<std::string> lines;
        std::string lineToWrite;
        std::ifstream inFile("fishCards.txt");


        while (std::getline(inFile, lineToWrite))
            lines.push_back(lineToWrite);
        inFile.close();


        auto lineToRemoveIterator = std::find(lines.begin(), lines.end(), lineToRemove);
        if (lineToRemoveIterator != lines.end())
        {
            *lineToRemoveIterator = "";
        }


        std::ofstream outFile("fishCards.txt");
        for (auto& line : lines)
        {
            if (!line.empty())
            {
                outFile << line << std::endl;
            }
        }
        outFile.close();
    }
}





void MainWindow::flipFishka()
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    if (currentIndex != -1)
    {
        if (ui.fishcard_Box->toPlainText() == fishcards[currentIndex].getBack())
        {
            QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(fishcards[currentIndex].getFront());
            ui.fishcard_Box->setHtml(text);
        }
        else
        {
            QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(fishcards[currentIndex].getBack());
            ui.fishcard_Box->setHtml(text);
        }
    }
}




void MainWindow::fishkaEdit()
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    if (currentIndex == -1)
    {
        QMessageBox::warning(this, tr("Fishcard edition."), tr("No fishcard has been selected."));
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Edit fishcard"));
    msgBox.setText(tr("Choose what you desire to edit:"));
    msgBox.addButton(tr("Edit front"), QMessageBox::ActionRole);
    msgBox.addButton(tr("Edit back"), QMessageBox::ActionRole);
    msgBox.addButton(tr("Edit both"), QMessageBox::ActionRole);

    int result = msgBox.exec();

    switch (result)
    {
    case 0:
        editFishkaPart(currentIndex, true, false);
        break;
    case 1:
        editFishkaPart(currentIndex, false, true);
        break;
    case 2:
        editFishkaPart(currentIndex, true, true);
        break;
    }
}




void MainWindow::editFishkaPart(int index, bool editFront, bool editBack)
{
    if (index < 0 || index >= fishcards.size()) return;


    Fishcard& card = fishcards[index];
    std::string lineToChange = card.getFront().toStdString() + ":" + card.getBack().toStdString();

    bool ok;


    if (editFront)
    {
        QString newFront = QInputDialog::getText(this, tr("Fishcard edition"), tr("New front:"), QLineEdit::Normal, card.getFront(), &ok).trimmed();
        if (ok && !newFront.isEmpty())
        {
            try
            {
                card.setFront(newFront);
            }
            catch (const InputError& error)
            {
                std::string communicate = std::string(error.what());
                QMessageBox::warning(this, tr("Invalid Input."), QString::fromStdString(communicate));
                return;
            }
            catch (const std::exception& error)
            {
                QMessageBox::warning(this, tr("Unknown Error"), tr("Unknown Error."));
                return;
            }
        }

    }


    if (editBack)
    {
        QString newBack = QInputDialog::getText(this, tr("Fishcard edition"), tr("New back:"), QLineEdit::Normal, card.getBack(), &ok).trimmed();
        if (ok && !newBack.isEmpty())
        {
            try
            {
                card.setBack(newBack);
            }
            catch (const InputError& error)
            {
                std::string communicate = std::string(error.what());
                QMessageBox::warning(this, tr("Invalid Input."), QString::fromStdString(communicate));
                return;
            }
            catch (const std::exception& error)
            {
                QMessageBox::warning(this, tr("Unknown Error"), tr("Unknown Error."));
                return;
            }
        }
    }
        

    std::vector<std::string> lines;
    std::string lineToWrite;
    std::ifstream inFile("fishCards.txt");


    while (std::getline(inFile, lineToWrite))
        lines.push_back(lineToWrite);
    inFile.close();


    auto lineToChangeIterator = std::find(lines.begin(), lines.end(), lineToChange);
    if (lineToChangeIterator != lines.end())
    {
        *lineToChangeIterator = card.getFront().toStdString() + ":" + card.getBack().toStdString();
    }


    std::ofstream outFile("fishCards.txt");
    for (auto i = lines.begin(); i != lines.end(); i++)
        outFile << *i << std::endl;
    outFile.close();


    ui.Fishka_list_Box->setItemText(index, card.getFront());
    for (int i = 0; i < fishcards.size(); ++i)
    {
        QString displayText = QString::number(i + 1) + ". " + fishcards[i].getFront();
        ui.Fishka_list_Box->setItemText(i, displayText);
    }

    displaySelectedFishka(index);
}
