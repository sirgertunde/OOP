#pragma once
#include "Repository.h"
#include "Dog.h"
#include "AdoptionList.h"
#include "Validator.h"
#include <string>

#define UPDATE_BREED 99
#define UPDATE_NAME 100
#define UPDATE_PHOTOGRAPH 102

class AdminService {

    Repository& repo;
    Validator validator;

public:
    explicit AdminService(Repository& r);
    void add(const std::string&, const std::string&, int, const std::string&);
    void remove(const std::string&);
    void update(const std::string&, int, const std::string&);
    void update(const std::string&, int);
    Repository getRepo() const { return this->repo; }
};

class UserService {

    Repository& repo;
    AdoptionList* adoptionList;

public:
    explicit UserService(Repository& r) : repo{ r }, adoptionList{ nullptr } {}
    void init(int type);
    std::vector<Dog> getDogList() { return this->repo.getData(); }
    std::vector<Dog> getDogListByFilter(const std::string&, int);
    const std::vector<Dog>& getAdoptionList() { return this->adoptionList->get(); }
    void adoptDog(const Dog&);
    void openAdoptionList();
};