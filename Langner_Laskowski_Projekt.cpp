#include "Langner_Laskowski_Projekt.h"
#include <QMessageBox>
#include <QInputDialog>
#include <Qstring>




Langner_Laskowski_Projekt::Langner_Laskowski_Projekt(QWidget* parent)
    : QMainWindow(parent) 
{
    ui.setupUi(this);

    //czcionka QeditBoxa (mo¿e trzeba zmieniæ boxa na jakiegoœ innego? do wyœwietlania fiszek)
    ui.fishcard_Box->setStyleSheet("QTextEdit {"
        "font-size: 24pt;"
        "font-weight: bold;"
        "text-align: center;"
        "}");

    connect(ui.add_Fishka_Button, &QPushButton::clicked, this, &Langner_Laskowski_Projekt::addFishka);
    connect(ui.subb_Fishka_Button, &QPushButton::clicked, this, &Langner_Laskowski_Projekt::removeFishka);
    connect(ui.flip_Fishka_Button, &QPushButton::clicked, this, &Langner_Laskowski_Projekt::flipFishka);
    connect(ui.Fishka_list_Box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Langner_Laskowski_Projekt::displaySelectedFishka);
}




Langner_Laskowski_Projekt::~Langner_Laskowski_Projekt() {}




void Langner_Laskowski_Projekt::addFishka()
{
    bool ok;
    QString front = QInputDialog::getText(this, tr("Nowa Fiszka"),
        tr("Podaj slowo po polsku:"), QLineEdit::Normal,
        QString(), &ok).trimmed();  //Trim obs³uguje wpisanie kilku spacji (nie pozwala)
    if (!ok || front.isEmpty())
        return; //Przerywa przy anulowaniu albo pustym stringu

    QString back = QInputDialog::getText(this, tr("Nowa Fiszka"),
        tr("Podaj slowo w innym jezyku:"), QLineEdit::Normal,
        QString(), &ok).trimmed();  
    if (!ok || back.isEmpty())
        return; 

    // Tworzenie nowej fiszki i dodanie jej do listy
    Fishcard newCard(front, back);
    fishcards.append(newCard);
    ui.Fishka_list_Box->addItem(QString::number(ui.Fishka_list_Box->currentIndex() + 2) + ". " + newCard.front); //DO POPRAWY -> obliczanie indexu przy dodaniu fiszki np. w 2 miejscu gdzie jest 6 fiszek


    //format czcionki
    QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(newCard.front);
    ui.fishcard_Box->setHtml(text);

    ui.Fishka_list_Box->setCurrentIndex(fishcards.size() - 1); //index na najnowszy elem 
}




void Langner_Laskowski_Projekt::displaySelectedFishka(int index)
{
    if (index >= 0 && index < fishcards.size()) 
    {
        Fishcard selectedCard = fishcards[index];
        QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(selectedCard.front);
        ui.fishcard_Box->setHtml(text);
    }
}




void Langner_Laskowski_Projekt::removeFishka() 
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    if (currentIndex != -1) 
    {
        fishcards.removeAt(currentIndex);
        ui.Fishka_list_Box->removeItem(currentIndex);
    }
}




void Langner_Laskowski_Projekt::flipFishka()
{
    int currentIndex = ui.Fishka_list_Box->currentIndex();
    if (currentIndex != -1)
    {
        fishcards[currentIndex].flip();
        QString text = QString("<div align='center' style='font-size: 24pt; font-weight: bold;'>%1</div>").arg(fishcards[currentIndex].front);
        ui.fishcard_Box->setHtml(text);
    }
}
