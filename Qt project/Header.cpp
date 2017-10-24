/*
 * Header.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: Isabelle
 */

#include "Header.hpp"

Header::Header() {
    this->valid = false;

    // Sets all the attributes to 0
    this->imageWidth = 0;
    this->imageHeight = 0;
    this->bytesPerPixel = 0;
    this->beginningOfArray = 0;
    this->paddingAvailable = 0;
    this->paddingPerLine = 0;

}

Header::Header(string address){
    this->fileAddress = address;

    // reads the header of the BMP file and calculates the appropriate attributes
    if (this->setup() == true){
        // sets the validity flag to true if the file was open
        this->valid = true;
    }
    else{
        // sets the validity flag to false if the file was not open
        this->valid = false;

        // Sets all the attributes to 0
        this->imageWidth = 0;
        this->imageHeight = 0;
        this->bytesPerPixel = 0;
        this->beginningOfArray = 0;
        this->paddingAvailable = 0;
        this->paddingPerLine = 0;
    }
}

Header::~Header() {
    cout << "You are deleting a Header Object" << endl;
}

//
// Reads the header of a bmp file, and sets up all related the attributes.
// Returns true if the reader was able to open the bmp file.
// Returns true if the reader could not open the bmp file.
//

bool Header::setup(){
    // fstream.read needs a pointer, the data will be copied into the right attribute after reading
    int *pWidth = new int;
    int *pHeight = new int;
    int *pBitesPerPixel = new int;
    unsigned int *pEndAddress = new unsigned int;

    /*
     * EXCTRATIING USEFUL DATA FROM THE HEADER FILE
     */
    this->reader.open(fileAddress.c_str(), ios::binary);

    if( this->reader.is_open() == false ){
        // Does not set any data if the file could not be open
        // Changes the validity flag to false and exists the function
        this->valid = false;

        // deletes the pointer no longer in use.
        delete pWidth ;
        delete pHeight;
        delete pBitesPerPixel;
        delete pEndAddress;

        // returns false to indicate that the file could be open
        return false;
    }

    // Makes sure the file is a BMP file (ie starts with the characters BM)
    else{
        string checking = "";
        char tempChar;

        // Reads the first character
        this->reader.seekg(0);
        this->reader.get(tempChar);
        checking += tempChar;

        // Reads the second character
        this->reader.seekg(1);
        this->reader.get(tempChar);
        checking += tempChar;

        // If the file is not a BMP file, does not change valid to true and returns false to indicate failure.
        if (checking != "BM"){
            return false;
        }
    }

    //
    // Reading data from the file header (size, width, height, bites per pixel)
    //

    // Reads the total size of the file
    reader.seekg(2);
    reader.read(reinterpret_cast<char*>(pEndAddress), 4);
    // Sorts it in the appropriate attribute
    this->endAddress = *pEndAddress;

    // Reads the width of the image
    this->reader.seekg(18);
    this->reader.read(reinterpret_cast<char*>(pWidth), 4);
    // Sorts it in the appropriate attribute
    this->imageWidth = *pWidth;

    // Reads the height of the image
    reader.seekg(22);
    reader.read(reinterpret_cast<char*>(pHeight), 4);
    // Sorts it in the appropriate attribute
    this->imageHeight = *pHeight;

    // Reads the number of bites per pixel
    reader.seekg(28);
    reader.read(reinterpret_cast<char*>(pBitesPerPixel), 4);

    //
    // Calculating bytesPerLine, paddingBytesAvailable, and endAddress
    //

    // Calculates the number of Bytes per pixel
    this->bytesPerPixel = *pBitesPerPixel/8;

    // Calculates the number of padding bytes per line (a line has to end with a multiple of 4 bytes)
    if ((*pWidth)*bytesPerPixel%4 == 0){
        this->paddingPerLine = 0;
    }
    else {
        this->paddingPerLine = 4-(*pWidth)*(this->bytesPerPixel)%4;
    }

    // Calculates the number of padding bytes in the entire file.
    this->paddingAvailable = paddingPerLine*(*pHeight);

    // Calculates the address of the beginning of the pixel Array
    int totalBytesForPixelArray = ((*pWidth)*this->bytesPerPixel + this->paddingPerLine)*(*pHeight);
    this->beginningOfArray = *pEndAddress - totalBytesForPixelArray;

    //
    // Cleaning up before existing
    //

    // Closes the reader
    reader.close();

    // deletes the pointer no longer in use
    delete pWidth ;
    delete pHeight;
    delete pBitesPerPixel;
    delete pEndAddress;

    // returns true to signify the file was properly open
    return true;
}

/*
 * Takes the new Address of the bmp file the header is has to read.
 * returns true and sets all the attributes if the file was open.
 * returns false if the file could not be open
 */
bool Header::setfileAddress(string newAddress){

    this->fileAddress = newAddress;
    if ( this->setup() == true ) {
        return true;
    }
    else{
        return false;
    }
}

/*
 * Assessors for the different attributes.
 */
bool Header::getValidity(){
    return this->valid;
}
string Header::getFileAddress(){
    return this->fileAddress;
}
int Header::getImageWidth(){
    return this->imageWidth;
}
int Header::getImageHeight(){
    return this->imageHeight;

}
int Header::getBytesPerPixel(){
    return this->bytesPerPixel;
}
int Header::getBeginningOfArray(){
    return this->beginningOfArray;
}
int Header::getPaddingAvailable(){
    return this->paddingAvailable;
}
int Header::getPaddingPerLine(){
    return this->paddingPerLine;
}
