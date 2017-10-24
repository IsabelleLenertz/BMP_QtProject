/*
 * InsertMessage.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: Isabelle
 */

#include "InsertMessage.hpp"

InsertMessage::InsertMessage() {
    this->message = "";
    this->imageAddress = "";
    this->insertionObject = nullptr;
}

InsertMessage::InsertMessage(string newAddress, string newMessage) {
    this->message = newMessage;
    this->imageAddress = newAddress;
    this->insertionObject = new PixelArrayIn(this->imageAddress);
}
InsertMessage::~InsertMessage() {
    delete this->insertionObject;
    cout << "You are deleting an InsertMessage Object" << endl;
}

bool InsertMessage::setImageAddress(string newAddress) {
    bool returnvalue = false;

    // Deletes the PixelArrayIn objects and creates a new one with the new address
    if (this->insertionObject != nullptr){
        delete this->insertionObject;
    }
    this->insertionObject = new PixelArrayIn(newAddress);

    // Check if the new insertionObject was properly initialized
    if (this->insertionObject->getValidity() == true ){
        returnvalue = true;
    }

    // Returns true for success, false for failure.
    return returnvalue;
}


bool InsertMessage::insertMessage(){
    bool returnvalue = false;

    // Check if the object was initialized
    if ( (this->message != "") || (this->message != "") || (this->insertionObject != nullptr) ){
        try{
            // Inserts the message into the BMP file.
            returnvalue = this->insertionObject->insertMessage(this->message);
        }
        // Catches the error thrown by the insertMessage function, the error class indicates the max size the image can hold.
        catch (MessageTooLong & error){
            // send the error to the user of the insertMessage class.
            throw error;
        }
    }

    // Returns true for success, false for failure.
    return returnvalue;
}
int InsertMessage::maxMessageSize(){
    int maxSize = 0;

    if(this->insertionObject != nullptr){
        maxSize =  this->insertionObject->getMaxSizeMessage();
    }

    return maxSize;
}
