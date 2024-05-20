#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Langner_Laskowski_Projekt.h"


class MainWindowClass : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowClass(QWidget *parent = nullptr);
    ~MainWindowClass();

private:

    Ui::UiMainWindowClass ui;

    private slots:
 

};
