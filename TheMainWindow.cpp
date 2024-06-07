#include "TheMainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QAbstractButton>
#include <QKeyEvent>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <iostream>
#include <fstream>



MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    // Set scalable background image
    QPixmap background("C:\\Users\\Andrzej\\Desktop\\tlo_fiszki.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    this->setPalette(palette);

    // Ensure that buttons and other widgets do not have a transparent background
    this->setAutoFillBackground(true);

   // ui.fishcard_Box->setStyleSheet(
   //     "QTextEdit {"
   //     "font: 22pt 'Microsoft YaHei UI';"
   //     "border: 3px solid #000000;"
   //     "background-color: #808080;"
   //     "text-align: center;"  // Center text horizontally
   //     "}"
   // );
    connect(ui.add_Fishka_Button, &QPushButton::clicked, this, &MainWindow::addFishka);
    connect(ui.subb_Fishka_Button, &QPushButton::clicked, this, &MainWindow::removeFishka);
    connect(ui.flip_Fishka_Button, &QPushButton::clicked, this, &MainWindow::flipFishka);
    connect(ui.Fishka_list_Box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::displaySelectedFishka);
    connect(ui.edit_fishka_Button, &QPushButton::clicked, this, &MainWindow::fishkaEdit);

    this->loadFishCards();
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

        QString text = QString("<div align='center' style='font-size: 30pt; font-weight: bold;'>%1</div>").arg(newCard.getFront());
        ui.fishcard_Box->setHtml(text);

        ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1);
    }

    fishCardSet.close();
}



void MainWindow::checkIfDuplicate()
{

}



MainWindow::~MainWindow() {}
