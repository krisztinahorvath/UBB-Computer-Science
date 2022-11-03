#pragma once
#include <QWidget>
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include "services.h"
#include "Validator.h"

namespace Ui {
class UserForm;
}

class UserForm : public QWidget
{
    Q_OBJECT

private:
    Service* serv;
    Validator valid;
    WatchList* watchList;
    std::string type;

public:
    explicit UserForm(Service* s, WatchList* watch, std::string type, QWidget *parent = nullptr);
    ~UserForm();

private:
    Ui::UserForm *ui;
    void populate_list(const std::vector<Movie>& v);
    void display_by_genre();
    void delete_from_watchlist();
    void open_in_app();
    void add_to_watchlist();
    void next_in_list();
    void exit_from_list();
    void connect_signals_slots();
    void display_watchlist();
};

