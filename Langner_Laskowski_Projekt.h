#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Langner_Laskowski_Projekt.h"

class Langner_Laskowski_Projekt : public QMainWindow
{
    Q_OBJECT

public:
    Langner_Laskowski_Projekt(QWidget *parent = nullptr);
    ~Langner_Laskowski_Projekt();

private:
    Ui::Langner_Laskowski_ProjektClass ui;
};
