/*
 * PixelArray.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#ifndef PIXELARRAY_HPP_
#define PIXELARRAY_HPP_

#include "Header.hpp"
#include <fstream>
#include <iostream>
#include "MessageTooLong.hpp"


using namespace std;

class PixelArray {

protected:
    Header *pFileHeader;
    bool valid;

public:
    PixelArray();
    PixelArray(string newAddress);
    virtual ~PixelArray();

    // Sends the new Address to the Header, who initializes all the variable
    // Changes the validity of the pixelArray
    bool setFileAddress(string newAddress);
    bool getValidity();
    int getMaxSizeMessage();
};

#endif /* PIXELARRAY_HPP_ */
