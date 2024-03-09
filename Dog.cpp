#include "Dog.h"
#include <vector>
#include<algorithm>
#include "Utils.h"

Dog::Dog(const std::string& name, const std::string& breed, int age, const std::string& photograph) :
    name{ name }, breed{ breed }, age{ age }, photograph{ photograph } {}

std::string Dog::getName() const {
    return this->name;
}

std::string Dog::getBreed() const {
    return this->breed;
}

int Dog::getAge() const {
    return this->age;
}

std::string Dog::getPhotograph() const {
    return this->photograph;
}

void Dog::setAge(int age) {
    this->age = age;
}

void Dog::setName(const std::string& name) {
    this->name = name;
}

void Dog::setBreed(const std::string& breed) {
    this->breed = breed;
}

void Dog::setPhotograph(const std::string& photograph) {
    this->photograph = photograph;
}

std::istream& Dog::read(std::istream& in)
{
    std::string line;
    std::getline(in, line);

    std::vector<std::string> tokens = tokenize(line, ',');

    for (auto it : tokens) {
        it.erase(std::remove_if(it.begin(), it.end(), [](std::string::value_type ch)
            { return !isalpha(ch); }
        ), it.end());
    }
    if (tokens.size() != 4)
        return in;
    if (tokens[0].empty())
        return in;
    if (tokens[1].empty())
        return in;
    if (tokens[3].empty())
        return in;
    this->name = tokens[0];
    this->breed = tokens[1];
    this->age = stoi(tokens[2]);
    this->photograph = tokens[3];
    return in;
}

std::ostream& operator<<(std::ostream& out, const Dog& dog)
{
    out << dog.getName() << "," << dog.getBreed() << "," << dog.getAge() << "," << dog.getPhotograph() << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Dog& dog)
{
    return dog.read(in);
}
