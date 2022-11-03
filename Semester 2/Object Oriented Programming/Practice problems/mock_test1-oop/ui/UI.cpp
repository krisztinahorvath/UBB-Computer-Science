#include "UI.h"
#include <iostream>
#include <string>

void UI::start() {
    while(true){
        print_menu();
        std::string cmd;
        std::getline(std::cin, cmd);
        if(cmd == "exit")
            break;
        if(cmd == "add"){
            std::cout << "\n";
            add_player_ui();
            continue;
        }
        if(cmd == "list"){
            std::cout << "\n";
            list_all_ui();
            continue;
        }
        if(cmd == "team"){
            std::cout << "\n";
            list_given_team_ui();
            continue;
        }
        std::cout <<"\n\tInvalid command!\n";
    }
}

void UI::print_menu() {
    std::cout << "\nMenu:\n";
    std::cout << "  add - add a player\n";
    std::cout << "  list - list all players\n";
    std::cout << "  team - list all players from a given team\n";
    std::cout << "  exit\n";
    std::cout << "Option: ";
}

void UI::add_player_ui() {
    std::string name, nationality, team, goals;
    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Nationality: ";
    std::getline(std::cin, nationality);

    std::cout << "Team: ";
    std::getline(std::cin, team);

    std::cout << "Goals: ";
    std::getline(std::cin, goals);

    int int_goals = serv.convert_to_int(goals);

    if(int_goals == -1)
        std::cout << "\n\tPlease make sure that you only introduce integers in the Goals field!\n";
    else{
        if(nationality.size() != 3)
            std::cout << "\n\tThe nationality should be exactly three letters!\n";
        /// todo check for name for correct form
        else if(serv.add_player_serv(name, nationality, team, int_goals) == 1)
            std::cout << "\n\tPlayer added successfully!\n";
        else
            std::cout << "\n\tError! Player already exists!\n";

    }
}

void UI::list_all_ui() {
    DynamicVector<Player> l = this->serv.get_repo().get_players();
    for(int i = 0; i < l.get_size(); i++){
        Player p = l.get_elem(i);
        std::cout << p.get_name() << " | " << p.get_nationality() << " | " + p.get_team() << " | " << p.get_goals() << "\n";

    }
}

void UI::list_given_team_ui() {
    std::string team;
    std::cout << "Team: ";
    std::getline(std::cin, team);

    DynamicVector<Player> l = this->serv.list_all_given_team_serv(team);
    for(int i = 0; i < l.get_size(); i++){
        Player p = l.get_elem(i);
        std::cout << p.get_name() << " | " << p.get_nationality() << " | " + p.get_team() << " | " << p.get_goals() << "\n";

    }
}


