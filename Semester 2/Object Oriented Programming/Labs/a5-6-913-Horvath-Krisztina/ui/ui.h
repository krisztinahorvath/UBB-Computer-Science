#pragma once
#include "services.h"

class UI
{
private:
    Service serv;

public:
    UI(const Service s): serv(s) {}

    void start();
    void admin_mode();
    void user_mode();

private:
    static void print_menu();
    static void print_menu_admin();
    static void print_menu_user();
    static void print_watchlist_menu();
    void list_movies();
    void add_movie_ui();
    void remove_movie_ui();
    void update_movie_ui();

    /// a6 - user
    void display_by_genre_ui();
    void list_watchlist_all();
    void delete_from_watchlist_ui();

};
