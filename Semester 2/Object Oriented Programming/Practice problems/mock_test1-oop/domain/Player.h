#pragma once
#include <string>
#include <iostream>

class Player {
private:
    std::string name;
    std::string nationality;
    std::string team;
    int goals;

public:
    Player();
    Player(const std::string& name, const std::string& nationality, const std::string& team, int goals);
    std::string get_name() const { return this->name; }
    std::string get_nationality() const { return this->nationality; }
    std::string get_team() const { return this->team; }
    int get_goals() const { return this->goals; }

    bool operator==(const Player& p);

};
