#pragma once
#include <string>
#include <iostream>


class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;

public:
    Dog() : breed{ "" }, name{ "" }, age{ 0 }, photograph{ "" } {}
    Dog(const std::string& name, const std::string& breed, int age, const std::string& photograph);
    std::string getBreed() const;
    std::string getName() const;
    int getAge() const;
    std::string getPhotograph() const;
    void setBreed(const std::string& breed);
    void setName(const std::string& name);
    void setAge(int age);
    void setPhotograph(const std::string& photograph);
    std::istream& read(std::istream& in);
    friend std::ostream& operator<<(std::ostream& out, const Dog& obj);
    friend std::istream& operator>>(std::istream& in, Dog& obj);
};