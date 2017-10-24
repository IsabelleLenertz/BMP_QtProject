/*
 * PixelArrayIn.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#ifndef PIXELARRAYIN_HPP_
#define PIXELARRAYIN_HPP_

#include "PixelArray.hpp"
#include "MessageTooLong.hpp"
#include "MessageTooLong.hpp"


class PixelArrayIn: public PixelArray {
private:
    ofstream writer;
public:
    PixelArrayIn();
    PixelArrayIn(string newAddress);
    virtual ~PixelArrayIn();

    /**
     * Insert a message inside the image.
     * returns true to indicates success, false to indicate failure
     * throws an exception if the message was too long, indicating the size of the message and the maximum room available inside the padding bytes.
     */
    bool insertMessage(string message);
};

#endif /* PIXELARRAYIN_HPP_ */
