#pragma once
#include <QWidget>
#include "services.h"
#include "Validator.h"
#include "adminform.h"
#include "userform.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

private:
    Service* serv;
    Validator valid;
    WatchList* watchList;
    Repository* admin_repo;

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();

private:
    Ui::MainForm *ui;
    void setup_connections_slots();

private slots:
    void admin_form();
    void user_form();
};


