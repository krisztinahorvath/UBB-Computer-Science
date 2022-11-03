#ifndef GUI_H
#define GUI_H

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
    explicit GUI(Service serv, QWidget *parent = nullptr);
    ~GUI();

private:
    void populate_list();
    void connect_signals_slots();
    void show_by_priority();

private:
    Ui::GUI *ui;
};

#endif // GUI_H
