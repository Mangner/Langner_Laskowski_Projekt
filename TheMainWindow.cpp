#include "TheMainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QAbstractButton>
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <QUrl>
#include <QDesktopServices>




MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    ui.fishcard_Box->setStyleSheet(
        "QTextEdit {"
        "font-size: 24pt;"
        "font-weight: bold;"
        "text-align: center;"
        "}"
    );

    connect(ui.add_Fishka_Button, &QPushButton::clicked, this, &MainWindow::addFishka);
    connect(ui.subb_Fishka_Button, &QPushButton::clicked, this, &MainWindow::removeFishka);
    connect(ui.flip_Fishka_Button, &QPushButton::clicked, this, &MainWindow::flipFishka);
    connect(ui.Fishka_list_Box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::displaySelectedFishka);
    connect(ui.edit_fishka_Button, &QPushButton::clicked, this, &MainWindow::fishkaEdit);
    connect(ui.pedroButton, &QPushButton::clicked, this, &MainWindow::relax);

    this->loadFishCards();
}




MainWindow::~MainWindow() {}




void MainWindow::addFishka()
{
    bool ok;
    QString front = QInputDialog::getText(this, tr("Nowa Fiszka"), tr("Podaj wyraz po polsku."), QLineEdit::Normal, QString(), &ok).trimmed();
    if (!ok || front.isEmpty())
        return;

    QString back = QInputDialog::getText(this, tr("Nowa Fiszka"), tr("Podaj wyraz w innym jezyku."), QLineEdit::Normal, QString(), &ok).trimmed();
    if (!ok || back.isEmpty())
        return;

    Fishcard newCard(front, back);
    fishcards.append(newCard);
    ui.Fishka_list_Box->addItem(QString::number(ui.Fishka_list_Box->currentIndex() + 2) + ". " + newCard.getFront());

    QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(newCard.getFront());
    ui.fishcard_Box->setHtml(text);

    ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1);

    std::ofstream FishCardsSet("fishCards.txt", std::ios::app);
    FishCardsSet << newCard.getFront().toStdString() << ":" << newCard.getBack().toStdString() << std::endl;
    FishCardsSet.close();

    // Display success message
    QMessageBox::information(this, tr("Nowa Fiszka"), tr("Poprawnie dodano fiszke."));
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
        fishcards.removeAt(currentIndex);
        ui.Fishka_list_Box->removeItem(currentIndex);
        QMessageBox::information(this, tr("Usuwanie fiszek"), tr("Poprawnie unicestwiono fiszke."));
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
        QMessageBox::warning(this, tr("Edycja fiszki"), tr("Nie wybrano zadnej fiszki."));
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Edytuj fiszke"));
    msgBox.setText(tr("Wybierz co chcesz edytowac:"));
    msgBox.addButton(tr("Edytuj front"), QMessageBox::ActionRole);
    msgBox.addButton(tr("Edytuj back"), QMessageBox::ActionRole);
    msgBox.addButton(tr("Edytuj oba"), QMessageBox::ActionRole);

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
    bool ok;
    bool edited = false;  

    if (editFront)
    {
        QString newFront = QInputDialog::getText(this, tr("Edycja fiszki"), tr("Nowy front:"), QLineEdit::Normal, card.getFront(), &ok).trimmed();
        if (ok && !newFront.isEmpty())
        {
            card.setFront(newFront);
            edited = true;  
        }
    }

    if (editBack)
    {
        QString newBack = QInputDialog::getText(this, tr("Edycja fiszki"), tr("Nowy back:"), QLineEdit::Normal, card.getBack(), &ok).trimmed();
        if (ok && !newBack.isEmpty())
        {
            card.setBack(newBack);
            edited = true;  
        }
    }

    ui.Fishka_list_Box->setItemText(index, card.getFront());
    displaySelectedFishka(index);

    if (edited)
    {
        QMessageBox::information(this, tr("Edycja fiszki."), tr("Poprawnie edytowano fiszke."));
    }
}




void MainWindow::keyPressEvent(QKeyEvent* event)
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    int itemCount = ui.Fishka_list_Box->count();

    switch (event->key()) 
    {
    case Qt::Key_Left:
        if (currentIndex > 0) 
        {
            ui.Fishka_list_Box->setCurrentIndex(currentIndex - 1);
        }
        break;

    case Qt::Key_Right:
        if (currentIndex < itemCount - 1) 
        {
            ui.Fishka_list_Box->setCurrentIndex(currentIndex + 1);
        }
        break;

    case Qt::Key_F:  
        flipFishka();
        break;

    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::relax()
{
    QUrl fileUrl = QUrl::fromLocalFile("C:\\Users\\Andrzej\\Desktop\\Pedro.mp4"); //raw string lub podwojne slashe + swoja sciezka do pliku mp4

    if (!QDesktopServices::openUrl(fileUrl))
    {
        QMessageBox::critical(this, "Error", "Failed to open the file. Check file path and permissions.");
        return;
    }
}






