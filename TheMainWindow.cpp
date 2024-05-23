#include "TheMainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <Qstring>
#include <QAbstractButton>
#include <QKeyEvent>




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

}




MainWindow::~MainWindow() {}




void MainWindow::addFishka()
{
    bool ok;
    QString front = QInputDialog::getText(this, tr("Nowa Fiszka"), tr("Podaj slowo po polsku:"), QLineEdit::Normal, QString(), &ok).trimmed();  
    if (!ok || front.isEmpty())
        return; 

    QString back = QInputDialog::getText(this, tr("Nowa Fiszka"),
        tr("Podaj slowo w innym jezyku:"), QLineEdit::Normal,
        QString(), &ok).trimmed();  
    if (!ok || back.isEmpty())
        return; 


    Fishcard newCard(front, back);
    fishcards.append(newCard);
    ui.Fishka_list_Box->addItem(QString::number(ui.Fishka_list_Box->currentIndex() + 2) + ". " + newCard.front); 


   
    QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(newCard.front);
    ui.fishcard_Box->setHtml(text);

    ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1); }




void MainWindow::displaySelectedFishka(int index)
{
    if (index >= 0 && index < fishcards.size()) 
    {
        Fishcard selectedCard = fishcards[index];
        QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(selectedCard.front);
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
    }
}




void MainWindow::flipFishka()
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    if (currentIndex != -1)
    {
        fishcards[currentIndex].flip();
        QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(fishcards[currentIndex].front);
        ui.fishcard_Box->setHtml(text);
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
    if (editFront) 
    {
        QString newFront = QInputDialog::getText(this, tr("Edycja fiszki"), tr("Nowy front:"), QLineEdit::Normal, card.front, &ok).trimmed();
        if (ok && !newFront.isEmpty()) card.front = newFront;
    }
    if (editBack) 
    {
        QString newBack = QInputDialog::getText(this, tr("Edycja fiszki"), tr("Nowy back:"), QLineEdit::Normal, card.back, &ok).trimmed();
        if (ok && !newBack.isEmpty()) card.back = newBack;
    }

    ui.Fishka_list_Box->setItemText(index, card.front);
    displaySelectedFishka(index); 
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

    case Qt::Key_F:  //do obrotu fiszki
        flipFishka();
        break;

    default:
        QMainWindow::keyPressEvent(event);
    }
}






