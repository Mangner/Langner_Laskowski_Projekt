#include "MainWindow.h"
#include <qmessagebox.h>




MainWindowClass::MainWindowClass(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}



MainWindowClass::~MainWindowClass()
{}



void MainWindowClass::addButton_clicked()
{
    auto numberOne = ui.enter_A->toPlainText().toStdString();
    auto numberTwo = ui.enter_B->toPlainText().toStdString();

    double convertedNumberA;
    double convertedNumberB;

    bool conversionCorrect = true;

    try
    {
        convertedNumberA = stod(numberOne);
    }
    catch(std::invalid_argument&)
    {
        QMessageBox msgBox;
        msgBox.setText("Blad konwersji pierwszej liczby");
        msgBox.setWindowTitle("Blad konwersji pierwszej liczby");
        msgBox.exec();
        conversionCorrect = false;
    }

    try
    {
        convertedNumberB = stod(numberTwo);
    }
    catch (std::invalid_argument&)
    {
        QMessageBox msgBox;
        msgBox.setText("Blad konwersji drugiej liczby");
        msgBox.setWindowTitle("Blad konwersji drugiej liczby");
        msgBox.exec();
        conversionCorrect = false;
    }


    if (conversionCorrect)
    {
        auto result = convertedNumberA + convertedNumberB;
        ui.result_Box->setText(QString::number(result));
    }


}


void MainWindowClass::subbButton_clicked()
{
    auto numberOne = ui.enter_A->toPlainText().toStdString();
    auto numberTwo = ui.enter_B->toPlainText().toStdString();

    double convertedNumberA;
    double convertedNumberB;

    bool conversionCorrect = true;

    try
    {
        convertedNumberA = stod(numberOne);
    }
    catch (std::invalid_argument&)
    {
        QMessageBox msgBox;
        msgBox.setText("Blad konwersji pierwszej liczby");
        msgBox.setWindowTitle("Blad konwersji pierwszej liczby");
        msgBox.exec();
        conversionCorrect = false;
    }

    try
    {
        convertedNumberB = stod(numberTwo);
    }
    catch (std::invalid_argument&)
    {
        QMessageBox msgBox;
        msgBox.setText("Blad konwersji drugiej liczby");
        msgBox.setWindowTitle("Blad konwersji drugiej liczby");
        msgBox.exec();
        conversionCorrect = false;
    }

    if (conversionCorrect)
    {
        auto result = convertedNumberA - convertedNumberB;
        ui.result_Box->setText(QString::number(result));
    }

}