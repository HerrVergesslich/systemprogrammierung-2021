//
// Created by Finn Watermann on 02.01.2022.
//

#ifndef BLATT08_NULLPOINTEREXCEPTION_H
#define BLATT08_NULLPOINTEREXCEPTION_H

#include <stdexcept>

class NullPointerException : public std::runtime_error {
public:
    NullPointerException() : std::runtime_error("NullPointerException") {}
    NullPointerException(const char *message) : std::runtime_error(message) { }
};

#endif //BLATT08_NULLPOINTEREXCEPTION_H
