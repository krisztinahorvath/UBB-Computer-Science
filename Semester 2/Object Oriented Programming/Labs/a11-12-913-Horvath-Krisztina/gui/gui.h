#pragma once
#include "services.h"
#include "Validator.h"

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QBoxLayout>


/// todo lab work 11

class GUI: public QWidget{
private:
    Service* serv;
    Validator valid;
    WatchList* watchList{};
    Repository* admin_repo;


    void setup_gui();
    void connect_signals_slots();
    void admin_mode();
    void user_mode();

public:
    GUI(Service* sr);
    ~GUI() override;

    GUI();
};

class Admin_gui: public QWidget{
private:
    Service* serv;
    QListWidget* user_repo;
    QLineEdit* title;
    void setup_gui();
    void connect_signals_slots();
    void filter();
    void populate_list();

public:
    Admin_gui(Service* s);
    ~Admin_gui() override;
};

class User_gui: public QWidget{
private:
    Service* serv;
    void setup_gui();

public:
    User_gui(Service* serv);
    ~User_gui() override;

};