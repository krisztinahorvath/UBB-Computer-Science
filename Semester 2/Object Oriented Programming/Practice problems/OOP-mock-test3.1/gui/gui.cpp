#include "gui.h"
#include "ui_gui.h"

GUI::GUI(Service serv, QWidget *parent) :
    QWidget(parent), serv(serv),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    this->connect_signals_slots();
    this->populate_list();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::populate_list() {
    this->ui->task_listWidget->clear();

    std::vector<Task> all_tasks = this->serv.get_sorted_tasks();

    for(auto t: all_tasks){
        QListWidgetItem* ta = new QListWidgetItem(t.to_string().c_str());

        if(t.get_priority() == 1){
            ta->setBackground(Qt::red);
            this->ui->task_listWidget->addItem(ta);
        }
        else
            this->ui->task_listWidget->addItem(ta);
    }

}

void GUI::connect_signals_slots() {
    QObject::connect(this->ui->priority_pushButton, &QPushButton::clicked, this, &GUI::show_by_priority);
}

void GUI::show_by_priority() {
    std::string p = this->ui->priority_lineEdit->text().toStdString();

    if(p.empty()){
        this->populate_list();
        return;
    }

    std::vector<Task> priority = serv.get_by_priority(stoi(p));

    this->ui->task_listWidget->clear();

//    std::vector<Task> all_tasks = this->serv.get_sorted_tasks();

    for(auto t: priority){
        QListWidgetItem* ta = new QListWidgetItem(t.to_string().c_str());

        if(t.get_priority() == 1){
            ta->setBackground(Qt::red);
            this->ui->task_listWidget->addItem(ta);
        }
        else
            this->ui->task_listWidget->addItem(ta);
    }

}
