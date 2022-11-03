#pragma once

#include <QWidget>
#include "services.h"
#include "Validator.h"

namespace Ui {
class AdminForm;
}

class AdminForm : public QWidget
{
    Q_OBJECT
private:
    Service* serv;
    Validator valid;
    Repository* repo;

public:
    explicit AdminForm(Service* s, Repository* admin_repo, QWidget *parent = nullptr);
    ~AdminForm();

private:
    Ui::AdminForm *ui;
    void populate_list();
    void add_movie();
    void delete_movie();
    void update_movie();
    void connect_signals_slots();
    void clear_list_edits();


};
