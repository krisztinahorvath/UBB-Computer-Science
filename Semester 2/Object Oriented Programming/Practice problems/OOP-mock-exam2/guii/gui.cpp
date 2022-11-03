#include "gui.h"
#include "ui_gui.h"

GUI::GUI(Service& serv, QWidget *parent) :
    QWidget(parent), serv(serv),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    serv.addObserver(this);
    connect_signals_slots();
    populate_list();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::populate_list() {
    ui->listWidget->clear();
    std::vector<Question> q = this->serv.get_sorted_questions();
    for(auto i: q){
        QListWidgetItem* it = new QListWidgetItem(i.to_string().c_str());
        ui->listWidget->addItem(it);
    }
}

void GUI::update() {
    populate_list();
}

void GUI::connect_signals_slots() {
    QObject::connect(ui->search_question_lineEdit, &QLineEdit::textChanged, this, &GUI::search_question);
    QObject::connect(ui->add_q_pushButton, &QPushButton::clicked, this, &GUI::add_question);
    QObject::connect(ui->show_a_pushButton, &QPushButton::clicked, this, &GUI::show_answers);
}

void GUI::search_question() {
    std::stringstream x(this->windowTitle().toStdString());
    std::string wnd_name;
    getline(x, wnd_name, '\n');
    if(wnd_name == "Search Window"){

        std::string s = this->ui->search_question_lineEdit->text().toStdString();

        if(s.empty())
            populate_list();
        else{
            Question q = serv.get_matching_question(s);
            ui->listWidget->clear();

            QListWidgetItem* it = new QListWidgetItem(q.to_string().c_str());
            ui->listWidget->addItem(it);
        }
    }
}

void GUI::add_question() {
    std::stringstream x(this->windowTitle().toStdString());
    std::string name;
    getline(x, name, '\n');
    if(name != "Search Window"){
        std::string id, text;
        id = this->ui->id_q_lineEdit->text().toStdString();
        text = this->ui->q_lineEdit->text().toStdString();
        if(!text.empty()){
            serv.add_question_serv(name,text, stoi(id));
            update();
        }
    }

}

void GUI::show_answers() {
    this->ui->answer_listWidget->clear();
    std::stringstream x(this->ui->listWidget->currentItem()->text().toStdString());

    std::string id, text, name;
    getline(x, id, ';');
    getline(x, text, ';');
    getline(x, name, '\n');

    std::stringstream y(this->windowTitle().toStdString());
    std::string wnd_name;
    getline(y, wnd_name, '\n');

    std::vector<Answer> ans = serv.get_answers_for_question(stoi(id));
    for(auto a: ans){
        QListWidgetItem* it = new QListWidgetItem(a.to_string().c_str());
        if( a.get_name() == wnd_name){
            it->setBackground(Qt::yellow);
            ui->answer_listWidget->addItem(it);
        }
        else
            ui->answer_listWidget->addItem(it);


    }
}
