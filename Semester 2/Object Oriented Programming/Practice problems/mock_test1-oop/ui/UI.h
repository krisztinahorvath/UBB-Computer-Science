#pragma once
#include <utility>

#include "Service.h"

class UI {
private:
    Service serv;

public:
    explicit UI(const Service s) : serv(s) {}
    void start();

private:
    static void print_menu();
    void list_all_ui();
    void add_player_ui();
    void list_given_team_ui();

};
