/*
 * PixelArrayExt.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#include "PixelArrayExt.hpp"

PixelArrayExt::PixelArrayExt() {
    // TODO Auto-generated constructor stub

}
PixelArrayExt::PixelArrayExt(string newAddress):PixelArray::PixelArray(newAddress){
    this->setFileAddress(newAddress);
}

PixelArrayExt::~PixelArrayExt() {
    cout << "You are destroying a PixelArrayExt." << endl;
}

string PixelArrayExt::extractMessage() {

    string hidenMessage = "";
    char tempChar;

    this->reader.open(this->pFileHeader->getFileAddress().c_str(), ios::binary);


    // check if the bmparray was setup properly
    if( this->valid == false){
        // indicates failure
        return "";
    }
    // check if the file was open properly
    else if (not reader.is_open()){
        // indicates failure
        return "";
    }
    // throws an exception if there is no padding avaiable to read a message.
    else if (this->pFileHeader->getPaddingAvailable() == 0 ){
        // indicates failure
        return "No padding available, there cannot be any message in this file.";
    }
    else{

        // stores the addresses of the beginning of the padding bytes of each line.
        int lineAddress [this->pFileHeader->getImageHeight()];
        lineAddress[0] = this->pFileHeader->getBeginningOfArray() + (this->pFileHeader->getImageWidth())*this->pFileHeader->getBytesPerPixel();
        for (int i = 1; i < this->pFileHeader->getImageHeight(); i++){
            lineAddress[i] = this->pFileHeader->getBeginningOfArray() + (this->pFileHeader->getImageWidth())*this->pFileHeader->getBytesPerPixel()*(i+1) + this->pFileHeader->getPaddingPerLine()*i;
        }

        for (int j = 0; j < this->pFileHeader->getImageHeight() ; j++){
            // Keeps track of the current padding byte within the current line
            for (int k = 0; k < this->pFileHeader->getPaddingPerLine(); k++){
                // places the writing position at the current line (j), at the current padding byte (k)
                reader.seekg(lineAddress[j] + (k) );
                // reads the current character and stores it temporary.
                reader.get(tempChar);
                // Adds the char to the message
                if (tempChar == 1){
                    // Stop reading at the ends of the message.
                    return hidenMessage;
                }
                else{
                    hidenMessage += tempChar;
                }
            } // end of for
        } // end of for
    }

    return hidenMessage;
}
