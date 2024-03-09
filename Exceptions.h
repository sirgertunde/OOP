#pragma once
#include <string>
#include<exception>

#define VALUE_ERROR 1909
#define ELEM_ERROR 1910
#define INDEX_ERROR 1911
#define INPUT_ERROR 1912

class RepositoryException : public std::exception {
    std::string message;
public:
    RepositoryException(const std::string& message = "Repository error!") : message{ message } {}
    const char* what() const noexcept override;
};

class ValidationException : public std::exception {
    std::string message;
public:
    ValidationException(const std::string& message = "Validation error!") : message{ message } {}
    const char* what() const noexcept override;
};

class InputException : public std::exception {
    std::string message;
public:
    InputException(const std::string& message = "Invalid Input!") : message{ message } {}
    const char* what() const noexcept override;
};