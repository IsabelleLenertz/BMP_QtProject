#ifndef RETRIEVEWINDOW_H
#define RETRIEVEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "PixelArrayExt.hpp"

class RetrieveWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RetrieveWindow(QWidget *parent = 0);
    ~RetrieveWindow();

private:
    // Q Objects
    QLabel *pIntro;
    QLabel *pSaveLabel;
    QPushButton *pSelectFolder;
    QPushButton *pSelectBmp;
    QFont *pFont;
    QGridLayout *pLayout;
    QPushButton *pGo;


    // Other attributs
    string folderAddress;
    string imageAddress;
    string message;
    PixelArrayExt *pRetrieve;


public slots:
    // When the "Select a picture" button is pressed, opens a selection window
    // Asks the user for a .bmp file
    // Sotrs the address into this->imageAddress
    void selectImage();

    // When the "Select a folder" button is pressed, opens a selection window
    // Asks the user for an existing folder
    // Sotrs the address into this->imageAddress
    void selectFolder();

    void retrieveMessage();



};

#endif // RETRIEVEWINDOW_H
