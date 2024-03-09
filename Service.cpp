#include "Service.h"
#include "Exceptions.h"
#include <iostream>
#include<algorithm>


AdminService::AdminService(Repository& r) : repo{ r } 
{
    repo.add(Dog{ "Lucky", "Caucasian", 1, "https://i.pinimg.com/originals/74/6c/f8/746cf88bf0622b95126e83ba8de899e7.jpg" });
    repo.add(Dog{ "Bear", "Pug", 4, "https://i.pinimg.com/originals/6b/a6/b7/6ba6b783944d3530552e1d7641bc4081.jpg" });
    repo.add(Dog{ "Bella", "Poodle", 3, "https://images.petpress.net/wp-content/uploads/2020/01/820B21F1-0732-44D8-9264-7C63ABA7318B.jpeg?strip=all&lossy=1&ssl=1" });
    repo.add(Dog{ "Goldy", "Golden Retriever", 2, "https://i.pinimg.com/originals/9a/8b/09/9a8b0969a28f09947840372a77376691.jpg" });
    repo.add(Dog{ "Rocky", "Rotweiller", 2, "https://i.pinimg.com/originals/39/4d/36/394d36591eefe7199995ee51988478a0.jpg" });
    repo.add(Dog{ "Daisy", "Beagle", 5, "https://i.pinimg.com/736x/32/ce/cc/32ceccf09732d991952d788c63cbcef6.jpg" });
    repo.add(Dog{ "Riley", "Teckel", 1, "https://64.media.tumblr.com/96e1b9ab3f9842fc32f809c9b90e99ae/tumblr_p3ll5d1Csc1wp3quco1_640.jpg" });
    repo.add(Dog{ "Zoe", "Bulldog", 2, "https://i.pinimg.com/originals/cf/d2/17/cfd21719cf38a30a78cf7aca3b7ce8ad.jpg" });
    repo.add(Dog{ "Jack", "Doberman", 4, "https://i.pinimg.com/originals/f4/d4/22/f4d42258ff69badc8123693f4b4caf8a.jpg" });
    repo.add(Dog{ "Lola", "Labrador", 2, "https://i.pinimg.com/originals/0e/83/b6/0e83b656ce5bbf743a43855dd8190045.jpg" });
}

void AdminService::add(const std::string& name, const std::string& breed, int age, const std::string& url) {
    
    this->validator.validateInput(name, breed, url, age);
    this->repo.add(Dog{ name, breed, age, url });
}

void AdminService::remove(const std::string& name) {
    
    this->validator.validateInput(name, "not null", "not null", 2);
    this->repo.remove(name);
}


void AdminService::update(const std::string& name, int age) {
    
    this->validator.validateInput(name, "not null", "not null", age);
    int index = this->repo.search(name);
    if (index == -1)
        throw RepositoryException("The element is not in the database!");
    this->repo[index].setAge(age);

}

void AdminService::update(const std::string& name, int updateType, const std::string& str) {
    
    this->validator.validateInput(name, str, str, 2);
    int index = this->repo.search(name);
    if (index == -1)
        throw RepositoryException("The element is not in the database!");
    switch (updateType) {
    case UPDATE_NAME:
        this->repo[index].setName(str);
        break;
    case UPDATE_BREED:
        this->repo[index].setBreed(str);
        break;
    case UPDATE_PHOTOGRAPH:
        this->repo[index].setPhotograph(str);
        break;
    default:
        break;
    }

}

std::vector<Dog> UserService::getDogListByFilter(const std::string& breed, int age) {
    
    std::vector<Dog> dogList;
    std::vector<Dog> copy = this->repo.getData();
    std::copy_if(copy.begin(), copy.end(), std::back_inserter(dogList),
        [&breed, age](const Dog& d) {
            return (breed.empty() || breed == d.getBreed()) && age >= d.getAge();
        });
    return dogList;
}

void UserService::adoptDog(const Dog& d) {
    
    this->adoptionList->adopt(d);
}

void UserService::init(int type) {
    if (type == 0) {
        this->adoptionList = new AdoptionListHTML("../adoption.html");
    }
    else {
        this->adoptionList = new AdoptionListCSV("../adoption.csv");
    }
}

void UserService::openAdoptionList() {
    this->adoptionList->open();
}