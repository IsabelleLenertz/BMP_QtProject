#include "InsertWindow.hpp"

InsertWindow::InsertWindow(QWidget *parent) : QWidget(parent)
{
    // Sets the attributs
    this->message = "";
    this->imageAddress = "";
    this->pInsert = nullptr;

    // Creats a layout to display all the widgets
    this->pLayout = new QGridLayout;

    // Creats a uniform font for the entire window
    this->pFont = new QFont;
    this->pFont->setPixelSize(17);
    this->pFont->setFamily("Calibri");


    // Creates an introduction label
    pIntro = new QLabel();
    pIntro->setFont(*(this->pFont));
    pIntro->setText("You may hidde a message into a BMP image. \n The text message will be saved into the padding bytes, and will not affect the image. \n 36 bytes and 16 bytes BMP do not have any padding bytes.\n Please, be aware that if you open the file in a image editor and save it, the text may be erased by your editor. ");


    // Creates a button to select the BMP file
    this->pSelectBmp = new QPushButton("Select a picture");
    this->pSelectBmp->setFont(*(this->pFont));
    this->pSelectBmp->setCursor((Qt::PointingHandCursor));


    // Creates a label "Enter message"
    pSelect = new QLabel();
    pSelect->setFont(*(this->pFont));
    pSelect->setText("How do you want to enter the message to hide?");

    // Creates a button "Write a message"
    this->pEnterMessage = new QPushButton("Enter message manually");
    this->pEnterMessage->setFont(*(this->pFont));
    this->pEnterMessage->setCursor((Qt::PointingHandCursor));


    // Creates a button "Select a .txt file"
    this->pSelectTxt = new QPushButton("Select a text file (.txt)");
    this->pSelectTxt->setFont(*(this->pFont));
    this->pSelectTxt->setCursor((Qt::PointingHandCursor));


    // Creates a button "Go!"
    this->pGo = new QPushButton("Go!");
    this->pGo->setFont(*(this->pFont));
    this->pGo->setCursor((Qt::PointingHandCursor));


    // Adds the label to the layout
    pLayout->addWidget(pIntro, 0, 0, 1, 3);
    pLayout->addWidget(pSelectBmp, 1, 1);
    pLayout->addWidget(pSelect,2, 0, 1, 2 );
    pLayout->addWidget(pEnterMessage, 3, 0);
    pLayout->addWidget(pSelectTxt, 3, 2);
    pLayout->addWidget(pGo, 5, 0, 1, 3);


    this->setLayout(this->pLayout);


    // Connects the button to their action

    // When the Go! button is pressed, creates an insertion objects and hides the message into a BMP.
    // It gives feeback to the user showing succes or faillure hrow a message/error window.
    QObject::connect(pGo, SIGNAL( clicked()), this, SLOT(hideMessage()));

    // When the "Select a picture button is pressed", opens a selection window
    // Asks the user for a .bmp file
    // Sotrs the address into this->imageAddress
    QObject::connect(pSelectBmp, SIGNAL(clicked()), this, SLOT(selectImage()));

    // When the "Enter a message manual" button is clicked, opens a message window asking the user to enter a message to hide.
    // Stors the message into this->message;
    // Does not change the this->message if the user did not enter any message.
    QObject::connect(pEnterMessage, SIGNAL(clicked()), this, SLOT(getMessage()));

    // When the button "Select a text file" is clicked, opens a window asking for a file location.
    // If the user gives a valide file location, copies the content of the file into this->message.
    QObject::connect(pSelectTxt, SIGNAL(clicked()), this, SLOT(getMessageFile()));


}

InsertWindow::~InsertWindow(){

    // Deletes all the dynamically allocated objects.
    if (this->pIntro != nullptr){
        delete this->pIntro;
    }

    if (this->pLayout != nullptr){
        delete this->pLayout;
    }
    if (this->pInsert != nullptr){
        delete this->pInsert;
    }
    if (this->pFont != nullptr){
        delete this->pFont;
    }
    if (this->pSelect != nullptr){
        delete this->pSelect;
    }
    if (this->pSelectBmp != nullptr){
        delete this->pSelectBmp;
    }
    if (this->pEnterMessage != nullptr){
        delete this->pEnterMessage;
    }
    if (this->pSelectTxt != nullptr){
        delete this->pSelectTxt;
    }
    if (this->pGo != nullptr){
        delete this->pGo;
    }
}

// This function is launched when the Go! button is pressed. its creates an insertion objects and hides the message into a BMP.
// It gives feeback to the user showing succes or faillure hrow a message/error window.
void InsertWindow::hideMessage(){


    // Makes sure the user initiated the file address and the message
    if ( (this->message != "") && (this->imageAddress != "") ){
        // Creats a new insertion object
        pInsert = new InsertMessage(this->imageAddress, this->message);

        // Try to insert the message and gives feedback to the user
        try{
            if (pInsert->insertMessage() == true){
                QMessageBox::information(this, "Success!", "The message has been inserted. \n You may use a binary viewer to look at your file.");
            }
            else{
                // Displays an error message to the user
                QMessageBox::critical(this, "Faillure!", "You did not provide a valid image file address");
            }
        }
        catch (MessageTooLong & error){
            //Convertion streams use ton convert the maximum number of padding bytes available and the size of the message into string.
            ostringstream convertMaxPadding, convertMessageSize;
            string maxPaddingString, messageSizeString;

            // Converts the maxPadding into a string.
            convertMaxPadding << error.getMaxMessageSize();
            maxPaddingString = convertMaxPadding.str();

            // Converts the messageSize into a string.
            convertMessageSize << error.getMessageSize();
            messageSizeString = convertMessageSize.str();

            // Creates the error message.
            string errorMessage = "Your message is " + messageSizeString + " characters long. \n This image cannot hold more than " + maxPaddingString + " characters.";

            //Converts the errormessage string into a Qstring
            QString qErrorMessage = QString::fromStdString(errorMessage);

            // Displays an error message to the user
            QMessageBox::critical(this, "Faillure!", qErrorMessage);
        }

        // Deletes the insertion object
        delete this->pInsert;
    }// end if


    // If the user did not initiate the image address
    // Displays an error message
    else if (this->imageAddress == "" ){
        // Displays an error message to the user
        QMessageBox::critical(this, "Faillure!", "You did not provide an image address");
    }

    // If the user did not initiate the message
    // Displays an error message
    else {
        // Displays an error message to the user
        QMessageBox::critical(this, "Faillure!", "You did not provide a message to hide");
    }
}

// When the "Select a picture button is pressed", opens a selection window
// Asks the user for a .bmp file
// Sotrs the address into this->imageAddress
void InsertWindow::selectImage(){
    QString fileAddress = QFileDialog::getOpenFileName(this, "Selectioner un BMP", QString(), "Images (*.bmp)");
    this->imageAddress = fileAddress.toStdString();
}

// When the "Enter a message manual" button is clicked, opens a message window asking the user to enter a message to hide.
// Stors the message into this->message;
// Does not change the this->message if the user did not enter any message.
void InsertWindow::getMessage(){
    bool ok = false;
    QString secretMessage = QInputDialog::getText(this, "Message", "Enter the messge you want to hide:", QLineEdit::Normal, QString(), &ok);

    if (ok && !secretMessage.isEmpty()){
        this->message = secretMessage.toStdString();
    }
    else{
        QMessageBox::critical(this, "Message", "You did not enter a message.");
    }
}

// When the button "Select a text file" is clicked, opens a window asking for a file location.
// If the user gives a valide file location, copies the content of the file into this->message.
void InsertWindow::getMessageFile(){
    QString fileAddress = QFileDialog::getOpenFileName(this, "Selectioner un fichier txt (.txt)", QString(), "Images (*.txt)");
    string secretMessage = "";
    char ch;

    // If the user did specify a file
    if (!fileAddress.isEmpty()){

        // Opens the file and copies all its content into a string
        ifstream file(fileAddress.toStdString());
        if (file.is_open())
        {
            file.get(ch);
            while(file){
                secretMessage += ch;
                file.get(ch);
            }
        }
        file.close();

        // Stors the message into this->message
        this->message = secretMessage;

    } // if

    // If the user did not specify a file, displays an error message
    else{
        QMessageBox::critical(this, "Message", "You did not enter a message.");
    }
}
