#include <assert.h>
#include "Tests.h"
#include "Player.h"
#include "Repository.h"
#include "Service.h"

void Tests::test_add() {
    /// in repo
    Repository r = Repository();
    assert(r.get_players().get_size() == 0);
    Player p1 = Player("Nora_Mork", "NOR", "Larvik", 83);
    assert(r.add_player(p1) == 1);
    assert(r.add_player(p1) == 0);

    /// in serv
    Repository r1 = Repository();
    Service serv = Service(r1);
    assert(serv.add_player_serv("Nora_Mork", "NOR", "Larvik", 83) == 1);
    assert(serv.add_player_serv("Nora_Mork", "NOR", "Larvik", 83) == 0);

}

void Tests::test_all() {
    test_add();
    test_list_given_team();
}

void Tests::test_list_given_team() {
    Repository r = Repository();
    Service s = Service(r);
    s.add_player_serv("Nora_Mork", "NOR", "Larvik", 83);
    s.add_player_serv("Isabelle_Gullden", "SWE", "CSM_Bucuresti", 80);
    s.add_player_serv("Cristina_Neagu", "ROU", "Buducnost", 63);
    s.add_player_serv("Allison_Pineau", "FRA", "HCM_Baia_Mare", 82);
    s.add_player_serv("Ilina_Ekaterina", "RUS", "Rostov-Don", 80);
    s.add_player_serv("Ana_Iliescu", "NOR", "Larvik", 60);
    s.add_player_serv("Nerea_Pena", "ESP", "FTC-Rail_Cargo_Hungaria", 59);
    s.add_player_serv("Mirabela_Ionescu", "NOR", "Larvik", 100);
    DynamicVector<Player> sorted = s.list_all_given_team_serv("Larvik");
    Player p1 = Player("Ana_Iliescu", "NOR", "Larvik", 60);
    assert(sorted[0] == p1);
    Player p2 = Player("Nora_Mork", "NOR", "Larvik", 83);
    assert(sorted[1] == p2);
    Player p3 = Player("Mirabela_Ionescu", "NOR", "Larvik", 100);
    assert(sorted[2] == p3);
}
