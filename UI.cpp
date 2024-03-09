#include "UI.h"
#include <string>
#include <iostream>

void UI::start() {
    std::string option;

    std::cout << "Choose one option (user/admin/exit)\n";
    std::cout << "> ";
    std::getline(std::cin, option);
    while (option != "exit") {
        if (option == "admin")
            this->adminPanel();
        else if (option == "user")
            this->userPanel();
        else
            std::cout << "Invalid option!\n";
        std::cout << "Choose one option (user/admin/exit)\n";
        std::cout << "> ";
        std::getline(std::cin, option);
    }
}

void printAdminMenu() {
    std::cout << "1. Add a dog\n2. Remove a dog\n3. Update a dog\n4. See all dogs\n0. Exit\n";
}

void UI::adminShow() {

    if (this->admin.getRepo().getSize() == 0) {
        std::cout << "The repo is empty!\n";
        return;
    }
    Repository r = this->admin.getRepo();
    for (const auto& item : this->admin.getRepo().getData())
        std::cout << "Dog name: " << item.getName() << ", breed: " << item.getBreed(),
        std::cout << ", age: " << item.getAge() << ", URL: " << item.getPhotograph() << ".\n";
    std::cout << "\n";

}

void UI::adminAdd() {
    std::string name, breed, url;
    int age;
    std::cout << "Enter the name of the dog: ";
    std::getline(std::cin, name);
    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed);
    std::cout << "Eenter the age of the dog: ";
    std::cin >> age;
    std::cout << "Enter the URL of the dog: ";
    std::cin >> url;
    this->admin.add(name, breed, age, url);
    std::cout << name << " has been added to the database.\n";

}

void UI::adminRemove() {
    std::string name;
    std::cout << "Enter the name of the dog: ";
    std::getline(std::cin, name);
    this->admin.remove(name);
    std::cout << name << " has been removed from the database.\n";
}

void UI::updateName() {

    std::string name, newName;
    std::cout << "Enter the actual name of the dog: ";
    std::getline(std::cin, name);
    std::cout << "Enter the new name of the dog : ";
    std::getline(std::cin, newName);
    this->admin.update(name, UPDATE_NAME, newName);
    std::cout << name << "'s name has been updated to " << newName << ".\n";
}

void UI::updateBreed() {

    std::string name, newBreed;
    std::cout << "Enter the actual name of the dog: ";
    std::getline(std::cin, name);
    std::cout << "Enter the new breed of the dog: ";
    std::getline(std::cin, newBreed);
    this->admin.update(name, UPDATE_BREED, newBreed);
    std::cout << name << "'s breed has been updated to " << newBreed << ".\n";

}

void UI::updateAge() {

    std::string name;
    int newAge;
    std::cout << "Enter the actual name of the dog: ";
    std::getline(std::cin, name);
    std::cout << "Enter the new age of the dog : ";
    std::cin >> newAge;
    this->admin.update(name, newAge);
    std::cout << name << "'s age has been updated to " << newAge << ".\n";

}

void UI::updatePhoto() {

    std::string name, newPhoto;
    std::cout << "Enter the actual name of the dog: ";
    std::getline(std::cin, name);
    std::cout << "Enter the new photograph of the dog: ";
    std::getline(std::cin, newPhoto);
    this->admin.update(name, UPDATE_PHOTOGRAPH, newPhoto);
    std::cout << name << "'s photo has been updated to " << newPhoto << ".\n";

}


void UI::adminUpdate() {
    std::string option;
    std::cout << "What do you want to update?(name, breed, age, photograph): ";
    std::getline(std::cin, option);
    if (option == "name")
        this->updateName();
    else if (option == "breed")
        this->updateBreed();
    else if (option == "age")
        this->updateAge();
    else if (option == "photograph")
        this->updatePhoto();
    else
        std::cout << "Invalid option!\n";

}

void UI::adminPanel() {

    while (true) {
        printAdminMenu();
        std::cout << "Choose an option: ";
        std::string option;
        std::getline(std::cin, option);
        std::cout << std::endl;
        if (option == "0")
            return;
        try {
            if (option == "1")
                this->adminAdd();
            else if (option == "2")
                this->adminRemove();
            else if (option == "3")
                this->adminUpdate();
            else if (option == "4")
                this->adminShow();
            else
                std::cout << "Invalid option!\n";
        }
        catch (std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }

}


void printUserMenu() {

    std::cout << "1. See all dogs\n2. See dogs by filter\n3. See adoption list\n4. Display the adoption list\n0. Exit\n";
}

void UI::userShow(int option) {

    std::vector<Dog> dogList;
    std::string input;
    if (option == 2) {
        std::string breed;
        int age;
        std::cout << "Enter the breed: ";
        std::getline(std::cin, breed);
        std::cout << "Enter the age: ";
        std::cin >> age;
        if (age < 0) {
            std::cout << "Age cannot be negative!\n";
            return;
        }
        dogList = this->user.getDogListByFilter(breed, age);
    }
    else
        dogList = this->user.getDogList();
    size_t size = dogList.size();
    if (size == 0) {
        std::cout << "Dog list is empty.\n";
        return;
    }
    int index = 0;
    while (true) {
        std::cout << "Dog name: " << dogList[index].getName() << ", breed: " << dogList[index].getBreed(),
            std::cout << ", age: " << dogList[index].getAge() << ", URL: " << "https://" << dogList[index].getPhotograph() << ".\n";

        std::string command = "start ";
        system(command.append(dogList[index].getPhotograph()).c_str());

        std::cout << "What do you want to do(adopt/next/exit): ";
        std::getline(std::cin, input);

        if (input == "exit")
            return;

        if (input == "next") {
            if (index >= dogList.size() - 1 && index > 0)
                index = 0;
            else if (index < dogList.size() - 1)
                index++;
        }
        else if (input == "adopt") {
            this->user.adoptDog(dogList[index]);
            this->admin.remove(dogList[index].getName());

            std::cout << dogList[index].getName() << " has been adopted.\n";
            dogList.erase(dogList.begin() + index);

            if (index >= dogList.size() - 1) {
                if (dogList.empty()) {
                    std::cout << "The list has emptied.\n";
                    return;
                }
                index = 0;
            }
        }
        else
            std::cout << "Invalid option.\n";
    }
}

void UI::userAdoptionList() {
    size_t size = this->user.getAdoptionList().size();
    if (size == 0) {
        std::cout << "The adoption list is empty.\n";
        return;
    }
    for (const auto& item : this->user.getAdoptionList())
        std::cout << "Dog name: " << item.getName() << ", breed: " << item.getBreed(),
        std::cout << ", age: " << item.getAge() << ", URL: " << item.getPhotograph() << ".\n";

}

void UI::userPanel() {

    std::string type;
    while (true) {
        std::cout << "How do you want to store your adoption list?(html/csv): \n";
        std::cout << "> ";
        std::getline(std::cin, type);
        if (type == "html") {
            this->user.init(0);
            break;
        }
        if (type == "csv") {
            this->user.init(1);
            break;
        }
        std::cout << "Invalid option!\n";
    }
    while (true) {
        printUserMenu();
        std::cout << "Choose an option: ";
        std::string option;
        std::getline(std::cin, option);
        std::cout << std::endl;
        if (option == "0")
            return;
        try {
            if (option == "1")
                this->userShow(0);
            else if (option == "2")
                this->userShow(2);
            else if (option == "3")
                this->userAdoptionList();
            else if (option == "4")
                this->openAdoptionList();
            else
                std::cout << "Invalid option!\n";
        }
        catch (std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
}

void UI::openAdoptionList() {
    this->user.openAdoptionList();
}