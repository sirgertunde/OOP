#include "FileRepository.h"
#include <fstream>
#include <iostream>

void FileRepository::loadData() {
    std::ifstream in(this->path);
    while (!in.eof()) {
        Dog d;
        in >> d;
        if (!d.getName().empty())
            this->data.push_back(d);
    }
    in.close();
}

void FileRepository::saveData() {

    std::ofstream out(this->path);
    for (const auto& d : this->data) {
        out << d;
    }
    out.close();
}