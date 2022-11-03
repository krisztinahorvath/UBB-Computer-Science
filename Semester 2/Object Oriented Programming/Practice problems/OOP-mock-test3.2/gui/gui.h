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

private:
    void populate_list();
    void connect_signals_slots();
    void filter_by_name_category();
    void sort_by_category();

public:
    explicit GUI(Service serv, QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUI *ui;
};

#endif // GUI_H
