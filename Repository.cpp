#include "Repository.h"
#include "Exceptions.h"

int Repository::search(const std::string& name) {

    auto it = std::find_if(this->data.begin(), this->data.end(), [&name](const Dog& d) {
        return d.getName() == name;
        });
    if (it == this->data.end())
        return -1;
    int index = it - this->data.begin();
    return index;
}

void Repository::add(const Dog& dog) {

    int index = this->search(dog.getName());
    if (index != -1)
        throw RepositoryException("The element is already in the database!");
    this->data.push_back(dog);
}

void Repository::remove(const std::string& name) {

    int index = this->search(name);
    if (index == -1)
        throw RepositoryException("The element is not in the database!");
    this->data.erase(this->data.begin() + index);
}

Dog& Repository::operator[](int index) {

    if (index < 0 || index >= this->data.size())
        throw RepositoryException("Array index out of bounds!");
    return this->data[index];
}