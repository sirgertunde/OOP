#include "Repository.h"
#include "Service.h"
#include "Exceptions.h"

class UI {

    AdminService admin;
    UserService user;

public:
    UI(AdminService& srv, UserService& usrv) : admin{ srv }, user{ usrv } {}
    void start();
    void adminPanel();
    void userPanel();

    void adminShow();
    void adminAdd();
    void adminRemove();
    void adminUpdate();

    void updateName();
    void updateAge();
    void updateBreed();
    void updatePhoto();


    void userShow(int option);
    void userAdoptionList();
    void openAdoptionList();

};