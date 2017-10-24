/*
 * PixelArray.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#include "PixelArray.hpp"

PixelArray::PixelArray() {
    // Initialize the variables
    this->valid = false;
    this->pFileHeader = new Header();
}

PixelArray::PixelArray(string newAddress) {
    // Initialize the variables
    this->valid = false;

    // Initializes the header
    this->pFileHeader = new Header(newAddress);
    // Check if the header is valid and updates the validity of the BMPfile.
    if (this->pFileHeader->getValidity() == true){
        this->valid = true;
    }
    else{
        this->valid = false;
    }

}

PixelArray::~PixelArray() {
    // deletes dynamically allocated objects
    delete this->pFileHeader;

    // warn about the destruction of the object
    cout << "You are destroying a PixeArray." << endl;
}

bool PixelArray::setFileAddress(string newAddress){
    // Sends the new address to the header who sets up all its member variables.
    if (this->pFileHeader->setfileAddress(newAddress)){
        this->valid = this->pFileHeader->getValidity();
        // returns true to indicate the address was valid and the header has been setup.
        return true;
    }
    else{
        this->valid = false;
        // return false to indicate failure.
        return false;
    }
}
bool PixelArray::getValidity(){
    return this->valid;
}

int PixelArray::getMaxSizeMessage(){
    return this->pFileHeader->getPaddingAvailable();
}

