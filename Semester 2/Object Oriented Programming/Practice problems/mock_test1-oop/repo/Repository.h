#pragma once
#include <string>
#include "DynamicVector.h"
#include "Player.h"

class Repository {
private:
    DynamicVector<Player> players;

public:
    Repository() = default;

    /**
     * Adds a player to the players repository
     * @param p Player, a player to be added
     * @return 1 - if the player doesn't already exist, so it was added successfully
     *         0 - otherwise
     */
    int add_player(const Player& p);

    /**
     *
     * @return
     */
    DynamicVector<Player> get_players() const { return this->players; }


private:
    /**
     * Finds a player by name and it returns its position in the repo
     * @param p Player, player that is being searched
     * @return position in the repo of player if exists
     *         -1 - otherwise
     */
    int find_player_by_name(const Player& p);
};

