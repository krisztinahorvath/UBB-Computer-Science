#pragma once
#include <QWidget>
#include "Service.h"

namespace Ui {
class GUI;
}

class GUI : public QWidget
{
    Q_OBJECT

private:
    Service serv;

public:
    explicit GUI(Service s, QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUI *ui;

private:
    void populate_list();
    void connect_signals_slots();
    void show_duration();


};
