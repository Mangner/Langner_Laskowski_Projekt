#include "TheMainWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication Application(argc, argv);
    MainWindow Window;

    Window.show();
    return Application.exec();
}
