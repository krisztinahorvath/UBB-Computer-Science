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
    this->ui->listWidget->clear();

    std::vector<Item> items = this->serv.get_sorted_items();

    for(auto i: items){
        QListWidgetItem* it = new QListWidgetItem(i.to_string().c_str());
        this->ui->listWidget->addItem(it);
    }
}

void GUI::connect_signals_slots() {
    QObject::connect(this->ui->name_lineEdit, &QLineEdit::textChanged, this, &GUI::filter_by_name_category);
    QObject::connect(this->ui->show_pushButton, &QPushButton::clicked, this, &GUI::sort_by_category);
}

void GUI::filter_by_name_category() {
    /// todo ***************
    std::string s = this->ui->name_lineEdit->text().toStdString();
    if(s.empty()){
        this->populate_list();
        return;
    }

    this->ui->listWidget->clear();
    std::vector<Item> items = this->serv.get_all_items();

    for(auto i: items){
        if(i.get_category().find(s) != 0 || i.get_name().find(s) != 0){
            QListWidgetItem* it = new QListWidgetItem(i.to_string().c_str());
            this->ui->listWidget->addItem(it);
        }
    }
}

void GUI::sort_by_category() {
    this->ui->category_listWidget->clear();
    std::string cat = this->ui->category_lineEdit->text().toStdString();
    std::vector<Item> items = serv.sort_by_quantity(cat);

    for(auto i: items){
        QListWidgetItem* it = new QListWidgetItem(i.to_string().c_str());
        this->ui->category_listWidget->addItem(it);
    }

}
