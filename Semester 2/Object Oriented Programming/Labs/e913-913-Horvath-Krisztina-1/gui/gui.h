#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "Observer.h"
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
    explicit GUI(Service& s, QWidget *parent = nullptr);
    ~GUI();

    void populate_list_presenter();
    void populate_list_participants();
    void update() override;
    void connect_signals_slots();
    void add_question();
    void answer_question();

private:
    Ui::GUI *ui;
};

#endif // GUI_H
