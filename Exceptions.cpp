#include "Exceptions.h"

const char* RepositoryException::what() const noexcept {
    return this->message.c_str();
}

const char* ValidationException::what() const noexcept {
    return this->message.c_str();
}

const char* InputException::what() const noexcept {
    return this->message.c_str();
}