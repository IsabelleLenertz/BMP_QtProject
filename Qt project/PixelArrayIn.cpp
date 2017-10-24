/*
 * PixelArrayIn.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#include "PixelArrayIn.hpp"

PixelArrayIn::PixelArrayIn() {
}

PixelArrayIn::PixelArrayIn(string newAddress):PixelArray::PixelArray(newAddress) {
    // No need to call set file address, the address is set by the parent class constructor.
    // The validity is also set by the base class constructor.
}
PixelArrayIn::~PixelArrayIn() {
    cout << "You are destroying a PixelArrayIn." << endl;
}

/**
 * Insert a message inside the image.
 * returns true to indicates success, false to indicate failure
 * throws an exception if the message was too long, indicating the size of the message and the maximum room available inside the padding bytes.
 */
bool PixelArrayIn::insertMessage(string message){

    // Adds a specific characters at the end of the string (ascii 1)
    // The reader will stop reading data if it encounters that number.
    int length = message.length();
    message[length] = 1;

    // does not execute the function if the file was not setup properly
    if (this->valid == false){
        return false;
    }
    // throws an exception if the message is too long
    else if (this->pFileHeader->getPaddingAvailable() < (int)message.size() ){
        throw MessageTooLong((int)message.size(), this->pFileHeader->getPaddingAvailable());
        return false;
    }
    // attempts inserting the message
    else{

        // stores the addresses of the beginning of the padding bytes of each line.
        int lineAddress [this->pFileHeader->getImageHeight()];
        lineAddress[0] = this->pFileHeader->getBeginningOfArray() + (this->pFileHeader->getImageWidth())*this->pFileHeader->getBytesPerPixel();
        for (int i = 1; i < this->pFileHeader->getImageHeight(); i++){
            lineAddress[i] = this->pFileHeader->getBeginningOfArray() + (this->pFileHeader->getImageWidth())*this->pFileHeader->getBytesPerPixel()*(i+1) + this->pFileHeader->getPaddingPerLine()*i;
        }
        // Opens the writer using the address stored inside the header (has to be converted into a c-string)
        this->writer.open(this->pFileHeader->getFileAddress().c_str(), ios::out | ios::in | ios::binary);

        // if the file could be opened
        if (this->writer.is_open() == true){
            int charCounter = 0; // keeps track of the number of characters inserted

            // Goes trough all the line available in the bmp file
            for (int j = 0; j < this->pFileHeader->getImageHeight(); j++){

                // Goes trough all the pabbying bytes in each line.
                for (int k = 0; k < this->pFileHeader->getPaddingPerLine(); k++){

                    // Check if the end of the message is reached
                    if ( charCounter <= (int)message.size()+1 ){
                    // places the writing position at the current line (j), at the current padding byte (k)
                    this->writer.seekp(lineAddress[j] + (k) );
                    // write the current character (i)
                    this->writer.write(&message[charCounter], 1);
                    // moves on to the next character.
                    charCounter++;

                    } // if
                }// for (padding bytes)
            }// for (line)
        }// if (file was open)

        // If the file could not be opened
        else{
            // Exists and returns false to indicate failure.
            this->writer.close();
            return false;
        } // else
    }// else

    //Closes the writer
    this->writer.close();

    // the end of the function has been reached
    // indicate success
    return true;

}// end of insertMessage
