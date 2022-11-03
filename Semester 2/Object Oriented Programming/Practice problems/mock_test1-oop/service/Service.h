#pragma once
#include <utility>
#include "Repository.h"

class Service {
private:
    Repository repo;

public:
    explicit Service(Repository r): repo(std::move(r)) {}
    Repository get_repo() const { return this->repo; }

    /**
     * Adds a player to the repo
     * @param name string, name of player
     * @param nationality string, nationality of player
     * @param team string, team of player
     * @param goals int, number of goals of player
     * @return 1 - if player added successfully(the name doesn't already exist in the players repo
     *         0 - otherwise
     */
    int add_player_serv(const std::string& name, const std::string& nationality, const std::string& team, const int goals );
    int convert_to_int(const std::string& nr);

    /**
     * Returns a dynamic array of all the players having a given team in ascending order
     * @param team string, the team that we are looking for
     * @return sorted dynamic array of players having the given team
     */
    DynamicVector<Player> list_all_given_team_serv(const std::string& team);

    /**
     * Sorts ascending an array of players by the number of goals.
     * @param p dynamic array, the array to be sorted by goals
     * @return
     */
    DynamicVector<Player> sort_by_goals(DynamicVector<Player>& p);
};