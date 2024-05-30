#pragma once
#include <QMainWindow>
#include <QList>
#include "ui_UiMainWindow.h"
#include "Fishcard.h"

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addFishka();
    void removeFishka();
    void flipFishka();
    void displaySelectedFishka(int index);
    void fishkaEdit();
    void editFishkaPart(int index, bool editFront, bool editBack);
    void loadFishCards();
    void checkIfDuplicate();
    void relax();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    

private:
    Ui::UiMainWindowClass ui;
    QList<Fishcard> fishcards;
};


