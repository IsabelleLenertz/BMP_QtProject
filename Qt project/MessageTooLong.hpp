/*
 * MessageTooLong.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#ifndef MESSAGETOOLONG_HPP_
#define MESSAGETOOLONG_HPP_

/**
 * Exception class, use to communicate the maximum size message an image can contain.
 */

class MessageTooLong {
private:
    int messageSize;
    int maxMessageSize;

public:
    MessageTooLong();
    virtual ~MessageTooLong();
    MessageTooLong(int size, int maxSize);

    /**
     * Assessors
     */
    int getMessageSize();
    int getMaxMessageSize();
};

#endif /* MESSAGETOOLONG_HPP_ */
