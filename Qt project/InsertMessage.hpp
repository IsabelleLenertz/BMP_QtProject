/*
 * InsertMessage.hpp
 *
 *  Created on: Nov 12, 2015
 *      Author: Isabelle
 */

#ifndef INSERTMESSAGE_HPP_
#define INSERTMESSAGE_HPP_

#include <iostream>
#include "PixelArrayIn.hpp"
#include "MessageTooLong.hpp"

using namespace std;

class InsertMessage {
private:
    string message;
    PixelArrayIn* insertionObject;
    string imageAddress;
public:
    InsertMessage();
    InsertMessage(string newAddress, string newMessage);
    virtual ~InsertMessage();

    bool insertMessage();
    int maxMessageSize();
    bool setImageAddress(string newAddress);



};

#endif /* INSERTMESSAGE_HPP_ */
