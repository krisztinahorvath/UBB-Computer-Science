#include <iostream>
#include "UI.h"
#include "Tests.h"

void add_players_ui(Service& s){
    s.add_player_serv("Nora_Mork", "NOR", "Larvik", 83);
    s.add_player_serv("Isabelle_Gullden", "SWE", "CSM_Bucuresti", 80);
    s.add_player_serv("Cristina_Neagu", "ROU", "Buducnost", 63);
    s.add_player_serv("Allison_Pineau", "FRA", "HCM_Baia_Mare", 82);
    s.add_player_serv("Ilina_Ekaterina", "RUS", "Rostov-Don", 80);
    s.add_player_serv("Ana_Iliescu", "NOR", "Larvik", 60);
    s.add_player_serv("Nerea_Pena", "ESP", "FTC-Rail_Cargo_Hungaria", 59);
    s.add_player_serv("Mirabela_Ionescu", "NOR", "Larvik", 100);
}

int main()
{
    {
        Tests::test_all();
        Repository repo = Repository();
        Service serv = Service(repo);

        add_players_ui(serv);

        UI ui_var = UI(serv);
        ui_var.start();

    }
    return 0;
}