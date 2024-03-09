#include "Dog.h"
#include "UI.h"
#include "Service.h"
#include "FileRepository.h"
#include "Tests.h"

int main() {

    FileRepository repo { "repo.txt" };
    AdminService admin{ repo };
    UserService user{ repo };
    UI ui{ admin, user };
    ui.start();
    return 0;
}