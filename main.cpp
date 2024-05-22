#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication Application(argc, argv);
    MainWindowClass MainWindow;
    
    MainWindow.show();
    return Application.exec();
}
