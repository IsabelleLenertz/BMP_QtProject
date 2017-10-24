#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include "InsertWindow.hpp"
#include <QTabWidget>
#include <QFont>
#include "RetrieveWindow.hpp"


class Window : public QWidget
{
    Q_OBJECT
public:
    // Defaults constructor and destructor
    Window();
    virtual ~Window();
public slots:
    void retrieveMessage();
    void hideMessage();
    void getMessage();

private:
    // Q objects
    QTabWidget *pTable;

    // Other attributs
    InsertWindow *pInsertW;
    RetrieveWindow *pRetrieveW;


};

#endif // WINDOW_H
