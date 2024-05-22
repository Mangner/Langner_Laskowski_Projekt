#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindowClass.h"

class MainWindowClass : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowClass(QWidget *parent = nullptr);
    ~MainWindowClass();

private:
    Ui::MainWindowClass ui;

    private slots:
    void addButton_clicked();
    void subbButton_clicked();

};
