#include "window.hpp"

Window::Window() : QWidget()
{
    this->resize(875, 350);

    // Creats the tables
    this->pTable = new QTabWidget(this);
    this->pInsertW = new InsertWindow;
    this->pRetrieveW = new RetrieveWindow;

    // inserts the insertion window into the first table
    this->pTable->addTab(this->pInsertW, "Hidding a message");
    this->pTable->addTab(this->pRetrieveW, "Retrieve a message");
}

Window::~Window(){
    // Deletes all the dynamically allocated objects.
    delete this->pTable;
}

void Window::retrieveMessage(){
    QMessageBox::information(this, "Message", "There is the message hidden inside your BMP file.");
    QMessageBox::warning(this, "Error", "The file could not be open.");
}

void Window::hideMessage(){
    QString fileAddress = QFileDialog::getOpenFileName(this, "Selectioner un BMP", QString(), "Images (*.bmp)");
    QMessageBox::information(this, "File", "You selected :\n" + fileAddress);
}

void Window::getMessage(){
    bool ok = false;
    QString secretMessage = QInputDialog::getText(this, "Message", "Enter the messge you want to hide.", QLineEdit::Normal, QString(), &ok);

    if (ok && !secretMessage.isEmpty()){
        QMessageBox::information(this, "Message", "Your message is: " + secretMessage);
    }
    else{
        QMessageBox::critical(this, "Message", "You did not enter a message");
    }
}

