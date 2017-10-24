#ifndef INSERTWINDOW_H
#define INSERTWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include "MessageTooLong.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "InsertMessage.hpp"

using namespace std;


class InsertWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InsertWindow(QWidget *parent = 0);
    ~InsertWindow();

private:
    // Q Objects
    QLabel *pIntro;
    QLabel *pSelect;
    QGridLayout *pLayout;
    QPushButton *pSelectBmp;
    QPushButton *pEnterMessage;
    QPushButton *pSelectTxt;
    QPushButton *pGo;
    QFont *pFont;

    // Other attributs
    string imageAddress;
    string message;
    InsertMessage *pInsert;

signals:

public slots:
    // This function is launched when the Go! button is pressed. its creates an insertion objects and hides the message into a BMP.
    // It gives feeback to the user showing succes or faillure hrow a message/error window.
    void hideMessage();

    // When the "Select a picture button is pressed", opens a selection window
    // Asks the user for a .bmp file
    // Sotrs the address into this->imageAddress
    void selectImage();

    // When the "Enter a message manual" button is clicked, opens a message window asking the user to enter a message to hide.
    // Stors the message into this->message;
    // Does not change the this->message if the user did not enter any message.
    void getMessage();

    // When the button "Select a text file" is clicked, opens a window asking for a file location.
    // If the user gives a valide file location, copies the content of the file into this->message.
    void getMessageFile();




};

#endif // INSERTWINDOW_H
