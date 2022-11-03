#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "Service.h"

namespace Ui {
class GUI;
}

class GUI : public QWidget, public Observer
{
    Q_OBJECT

private:
    Service& serv;

public:
    explicit GUI(Service &serv, QWidget *parent = nullptr);
    ~GUI();

    void populate_list();
    void update() override;
    void connect_signals_slots();
    void search_question();
    void add_question();
    void show_answers();

private:
    Ui::GUI *ui;
};

#endif // GUI_H
