#include "Player.h"

Player::Player() {
    this->name = "";
    this->nationality = "";
    this->team = "";
    this->goals = 0;
}

Player::Player(const std::string &name, const std::string &nationality, const std::string &team, int goals) {
    this->name = name;
    this->nationality = nationality;
    this->team = team;
    this->goals = goals;
}

bool Player::operator==(const Player &p) {
    if(this->name == p.name && this->nationality == p.nationality && this->team == p.team && this->goals == p.goals)
        return true;
    return false;
}
