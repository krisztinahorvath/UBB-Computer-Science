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
    void filter();
    void connect_signals();
    void total_time();

public:
    explicit GUI(Service serv, QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUI *ui;
};

#endif // GUI_H
