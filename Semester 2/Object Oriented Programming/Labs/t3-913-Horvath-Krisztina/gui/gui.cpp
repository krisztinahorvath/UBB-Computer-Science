#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>

GUI::GUI(Service serv, QWidget *parent) :
    QWidget(parent), serv(serv),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    connect_signals();
    populate_list();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::populate_list() {
    this->ui->listWidget->clear();

    std::vector<Weather> times = this->serv.get_sorted_times();

    for(auto t: times){
        QListWidgetItem* item = new QListWidgetItem(t.to_string().c_str());
        this->ui->listWidget->addItem(item);
    }
}

void GUI::filter() {
    this->ui->listWidget->clear();
    std::string prec = this->ui->prec_lineEdit->text().toStdString();
    std::vector<Weather> list = this->serv.get_all_times();
    for(auto t: list)
        if(t.get_prec_probability() < stoi(prec)){
            QListWidgetItem* item = new QListWidgetItem(t.to_string().c_str());
            this->ui->listWidget->addItem(item);
        }
}

void GUI::connect_signals() {
    QObject::connect(this->ui->prec_lineEdit, &QLineEdit::textChanged, this, &GUI::filter);
//    QObject::connect(this->ui->pushButton, &QPushButton, this, &GUI::total_time);
}


void GUI::total_time() {
    std::string descrip = this->ui->descrip_lineEdit->text().toStdString();
    std::string start = this->ui->start_lineEdit->text().toStdString();

    int time = this->serv.get_time(descrip, stoi(start));


}
