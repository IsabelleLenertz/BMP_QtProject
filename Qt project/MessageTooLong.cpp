/*
 * MessageTooLong.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#include "MessageTooLong.hpp"

MessageTooLong::MessageTooLong() {
    this->messageSize = 0;
    this->maxMessageSize = 0;
}
MessageTooLong::MessageTooLong(int size, int maxSize) {
    this->messageSize = size;
    this->maxMessageSize = maxSize;
}

MessageTooLong::~MessageTooLong() {
    // TODO Auto-generated destructor stub
}

int MessageTooLong::getMessageSize(){
    return this->messageSize;
}
int MessageTooLong::getMaxMessageSize(){
    return this->maxMessageSize;
}
