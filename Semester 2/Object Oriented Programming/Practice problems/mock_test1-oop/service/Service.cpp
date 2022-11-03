#include "Service.h"
#include <string>

int Service::add_player_serv(const std::string &name, const std::string &nationality, const std::string &team, int goals){
    Player p = Player(name, nationality, team, goals);

    return this->repo.add_player(p);
}

int Service::convert_to_int(const std::string& nr) {
    for(int i = 0; i < nr.size(); i++)
        if(!(nr[i] >= '0' && nr[i] <= '9'))
            return -1;
    return stoi(nr);
}

DynamicVector<Player> Service::list_all_given_team_serv(const std::string &team) {
    DynamicVector<Player> p;
    for(int i = 0; i < this->repo.get_players().get_size(); i++){
        Player play = this->repo.get_players().get_elem(i);
        if(play.get_team() == team)
            p.add(play);
    }
    return sort_by_goals(p);
}

DynamicVector<Player> Service::sort_by_goals(DynamicVector<Player>& p){
    Player aux;
    for(int i = 0; i < p.get_size() - 1; i++){
        for(int j = i + 1; j < p.get_size(); j++) {
            if (p[i].get_goals() > p[j].get_goals()) {
                aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
        }
    }
    return p;
}
