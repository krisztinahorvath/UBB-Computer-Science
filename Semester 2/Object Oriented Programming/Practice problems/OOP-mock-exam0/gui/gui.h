#pragma once
#include <QWidget>
#include "Service.h"
#include "Observer.h"

namespace Ui {
class GUI;
}

class GUI : public QWidget, public Observer
{
    Q_OBJECT
private:
    Service& serv;

public:
    explicit GUI(Service& s, QWidget *parent = nullptr);
    ~GUI();
    void populate_list();
    void update() override;
    void connect_signals_slots();
    void add_issue();
    void remove_issue();
    void resolve_issue();


private:
    Ui::GUI *ui;
};


