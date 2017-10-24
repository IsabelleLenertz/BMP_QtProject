/*
 * Header.hpp
 *
 *  Created on: Oct 6, 2015
 *      Author: Isabelle Delmas
 */

#ifndef HEADER_HPP_
#define HEADER_HPP_
#include <fstream>
#include <iostream>
#include "MessageTooLong.hpp"


using namespace std;

class Header {
private:
    // Stream use to read the header of a bmp file in binary mode
    ifstream reader;
    string fileAddress;

    // Data to be read from the file:
    int imageWidth;
    int imageHeight;
    int bytesPerPixel;
    unsigned int endAddress; // size of the bmp file (ie address of the last byte)

    // Data to be calculated from the previous ones.
    int beginningOfArray;
    int paddingAvailable;
    int paddingPerLine;

    // flag indicating if the header could read the information it needs from the file
    bool valid;

public:

    /*
     * Constructors and destructor
     */
    // Default constructor. sets the validity flag to false.
    Header();
    // Takes the address of the BMP file
    Header(string address);
    // Default destructor.
    virtual ~Header();

    /*
     * Reads the header of a bmp file, and sets up all relating the attributes.
     * Returns true if the reader was able to open the bmp file.
     * Returns true if the reader could not open the bmp file.
     */
    bool setup();

    /*
     * Takes the new Address of the bmp file the header is has to read.
     * returns true and sets all the attributes if the file was open.
     * returns false if the file could not be open
     */
    bool setfileAddress(string newAddress);

    /*
     * Accessors for the different attributes.
     */
    bool getValidity();
    string getFileAddress();
    int getImageWidth();
    int getImageHeight();
    int getBytesPerPixel();
    int getLengthOfHeader();
    int getBeginningOfArray();
    int getPaddingAvailable();
    int getPaddingPerLine();


};

#endif /* HEADER_HPP_ */
