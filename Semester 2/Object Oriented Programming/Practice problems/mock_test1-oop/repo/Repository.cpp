#include "Repository.h"

int Repository::add_player(const Player &p) {
    if(find_player_by_name(p) == -1){
        this->players.add(p);
        return 1;
    }
    return 0;
}

int Repository::find_player_by_name(const Player &p) {
    for(int i = 0; i < this->players.get_size(); i++)
        if(p.get_name() == this->players.get_elem(i).get_name())
            return i;
    return -1;
}
