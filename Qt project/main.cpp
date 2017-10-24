#include <QApplication>
#include <QPushButton>
#include <QFont>
#include "window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Creats and sets up the main window
    Window mainWindow;
    mainWindow.show();

    return app.exec();
}
