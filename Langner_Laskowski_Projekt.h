#ifndef LANGNER_LASKOWSKI_PROJEKT_H
#define LANGNER_LASKOWSKI_PROJEKT_H

#include <QMainWindow>
#include <QList>
#include "ui_Langner_Laskowski_Projekt.h"
#include "Fishcard.h"

class Langner_Laskowski_Projekt : public QMainWindow 
{
    Q_OBJECT

public:
    explicit Langner_Laskowski_Projekt(QWidget* parent = nullptr);
    ~Langner_Laskowski_Projekt();

private slots:
    void addFishka();
    void removeFishka();
    void flipFishka();
    void displaySelectedFishka(int index);

private:
    Ui::Langner_Laskowski_ProjektClass ui;
    QList<Fishcard> fishcards;
};

#endif 
