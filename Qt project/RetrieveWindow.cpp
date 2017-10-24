#include "RetrieveWindow.hpp"

RetrieveWindow::RetrieveWindow(QWidget *parent) : QWidget(parent){

    // Sets the attributs
    this->message = "";
    this->folderAddress = "";
    this->pRetrieve = nullptr;

    // Creats a layout to display all the widgets
    this->pLayout = new QGridLayout;

    // Creats a uniform font for the entire window
    this->pFont = new QFont;
    this->pFont->setPixelSize(17);
    this->pFont->setFamily("Calibri");

    // Creates an introduction label
    pIntro = new QLabel();
    pIntro->setFont(*(this->pFont));
    pIntro->setText(" You may retrieve a message from a BMP image. \n This software only looks at the file's padding bytes and converts them into characters. \n It is up to the user to make sens out of them. \n 36 bytes and 16 bytes BMP do not have any padding bytes.\n Please, be aware that if the filewas open in a image editor and saved, the message may have been erased by the editor. ");

    // Creates a button to select the BMP file
    this->pSelectBmp = new QPushButton("Select a picture");
    this->pSelectBmp->setFont(*(this->pFont));
    this->pSelectBmp->setCursor((Qt::PointingHandCursor));

    // Creates a label "You may choose a file location."
    pSaveLabel = new QLabel();
    pSaveLabel->setFont(*(this->pFont));
    pSaveLabel->setText("You may choose a file location to store the message. \n If you do not indicate a file location, the message will not be saved.");

    // Creates a button "Select a folder"
    this->pSelectFolder = new QPushButton("Select a folder");
    this->pSelectFolder->setFont(*(this->pFont));
    this->pSelectFolder->setCursor((Qt::PointingHandCursor));

    // Creates a button "Go!"
    this->pGo = new QPushButton("Go!");
    this->pGo->setFont(*(this->pFont));
    this->pGo->setCursor((Qt::PointingHandCursor));


    // Adds the widget to the layout
    pLayout->addWidget(pIntro, 0, 0, 1, 3);
    pLayout->addWidget(pSelectBmp, 1, 1);
    pLayout->addWidget(pSaveLabel, 2, 0, 1, 2);
    pLayout->addWidget(pSelectFolder, 3, 1);
    pLayout->addWidget(pGo, 4, 0, 1, 3);

    this->setLayout(this->pLayout);

    //
    // CONNECTS THE WIDGETS AND THE SLOTS
    //

    // When the "Select a picture button is pressed", opens a selection window
    // Asks the user for a .bmp file
    // Sotrs the address into this->imageAddress
    QObject::connect(pSelectBmp, SIGNAL(clicked()), this, SLOT(selectImage()));

    // When the "Select a folder" button is pressed, opens a selection window
    // Asks the user for an existing folder
    // Sotrs the address into this->imageAddress
    QObject::connect(pSelectFolder, SIGNAL(clicked()), this, SLOT(selectFolder()));

    // When the "Go" button is presser, extracts the message from a bmp file only if the user provided the image address.
    // Displays an error if the user forget to provide an address.
    // Saves the message to a file if the user provided a folder location.
    QObject::connect(pGo, SIGNAL(clicked()), this, SLOT(retrieveMessage()));

}

RetrieveWindow::~RetrieveWindow(){
    // Deletes the dynamycally allocated objects
    if (this->pRetrieve != nullptr){
        delete this->pRetrieve;
    }
}

// When the "Select a picture" button is pressed, opens a selection window
// Asks the user for a .bmp file
// Sotrs the address into this->imageAddress
void RetrieveWindow::selectImage(){
    QString fileAddress = QFileDialog::getOpenFileName(this, "Selectioner un BMP", QString(), "Images (*.bmp)");
    this->imageAddress = fileAddress.toStdString();
}

// When the "Select a folder" button is pressed, opens a selection window
// Asks the user for an existing folder
// Sotrs the address into this->imageAddress
void RetrieveWindow::selectFolder(){
    QString qFolder = QFileDialog::getExistingDirectory(this);
    this->folderAddress = qFolder.toStdString();
}

// When the "Go" button is presser, extracts the message from a bmp file only if the user provided the image address.
// Displays an error if the user forget to provide an address.
// Saves the message to a file if the user provided a folder location.
void RetrieveWindow::retrieveMessage(){

    // If the user initiated the image address.
    if(this->imageAddress!= ""){

        //Retrieves the message from the image.
        pRetrieve = new PixelArrayExt(this->imageAddress);
        this->message = pRetrieve->extractMessage();

        // Displays the message.
        string displayMessage = "The Message is: " + this->message;
        QString qMessage = QString::fromStdString(displayMessage);
        QMessageBox::information(this, "Success!", qMessage);


        // If the user provided a folder address
        // Saves the message into a .txt file
        if (this->folderAddress != ""){
            char ch;
            int lastChar = this->message.length() - 1;
            string fileLocation = this->folderAddress + "/secretMessage.txt";

            fstream newFile(fileLocation, ios::out | ios::app);

            // If the file was open, writes in it
            if (newFile.is_open()){
                for (int i = 0; i< lastChar; i++){
                    ch = message[i];
                    newFile.put(ch);
                }// for
                newFile.close();
                QMessageBox::information(this, "Success!", "The message was saved into a text file.");

            }// if

            else{
                QMessageBox::critical(this, "Faillure!", "The message was not saved into a text file.");
            }


        }// if

    }


    // If the user did not initiate the image address
    // Displays an error message
    else{
        // Displays an error message to the user
        QMessageBox::critical(this, "Faillure!", "You did not provide an image address");
    }


}
