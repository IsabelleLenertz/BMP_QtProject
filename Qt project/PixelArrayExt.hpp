/*
 * PixelArrayExt.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#ifndef PIXELARRAYEXT_HPP_
#define PIXELARRAYEXT_HPP_

#include "PixelArray.hpp"
#include "MessageTooLong.hpp"


class PixelArrayExt: public PixelArray {
private:
    ifstream reader;
public:
    PixelArrayExt();
    PixelArrayExt(string newAddress);
    virtual ~PixelArrayExt();

    /**
     * Returns the message stored inside the bmp
     * returns an empty message if nothing was found.
     */
    string extractMessage();
};

#endif /* PIXELARRAYEXT_HPP_ */
