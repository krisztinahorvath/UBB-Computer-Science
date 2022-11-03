#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>

GUI::GUI(Service s, QWidget *parent) :
    QWidget(parent), serv(s),
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
//    std::vector<Task> all_tasks = this->serv.get_all_tasks();
    std::vector<Task> all_tasks = this->serv.get_sorted();
    QFont font("Segoe UI", 12, 10, false);
    font.setBold(true);



    for(auto t: all_tasks){
        std::string ta = t.get_description() + " | " + std::to_string(t.get_estimated_duration()) + " | " + std::to_string(t.get_priority());

        QListWidgetItem* task = new QListWidgetItem(ta.c_str());

        if(t.get_priority() == 1){
            task->setFont(font);
            this->ui->task_listWidget->addItem(task);

        }
        else{
            this->ui->task_listWidget->addItem(QString::fromStdString(t.get_description() + " | " + std::to_string(t.get_estimated_duration()) + " | " + std::to_string(t.get_priority())));
        }
    }
}

void GUI::connect_signals_slots() {
    QObject::connect(this->ui->show_duration_pushButton, &QPushButton::clicked, this, &GUI::show_duration);
}

void GUI::show_duration() {
    std::string priority;
    priority = this->ui->lineEdit->text().toStdString();
    int duration = this->serv.get_task_priority(std::stoi(priority));
    if(duration == -1){
        QMessageBox::critical(this, "Error", "No tasks with this priority");
    }
    else{
        this->ui->show_duration_label->setText(QString::fromStdString(std::to_string(duration)));
    }
}
