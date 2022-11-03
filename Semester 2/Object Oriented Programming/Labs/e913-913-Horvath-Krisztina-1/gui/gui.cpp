#include "gui.h"
#include "ui_gui.h"
#include <iostream>
#include <QMessageBox>

GUI::GUI(Service& s,QWidget *parent) :
    QWidget(parent),serv(s),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    serv.addObserver(this);
    this->connect_signals_slots();
    this->populate_list_presenter();
    this->populate_list_participants();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::populate_list_presenter() {

    std::string title;
    std::stringstream x(this->windowTitle().toStdString());

    getline(x, title, '\n');
    std::cout << title;
    if(title == "Presenter"){
        this->ui->listWidget->clear();

        for(auto q: serv.get_questions_sorted_id()){
            QListWidgetItem* it = new QListWidgetItem(q.to_string().c_str());
            this->ui->listWidget->addItem(it);

        }
    }
    else{
        this->ui->listWidget->clear();

        for(auto q: serv.get_questions_sorted_score()){
            QListWidgetItem* it = new QListWidgetItem(q.to_string_part().c_str());
            if(serv.in_selected_questions(q.get_id())){
                it->setBackground(Qt::green);
            }

            this->ui->listWidget->addItem(it);
        }
    }
}

void GUI::update() {
    populate_list_presenter();
//    populate_list_participants();
}

void GUI::connect_signals_slots() {
    QObject::connect(ui->add_pushButton, &QPushButton::clicked, this, &GUI::add_question);
    QObject::connect(this->ui->answer_pushButton, &QPushButton::clicked, this, &GUI::answer_question);
}

void GUI::populate_list_participants() {


}

void GUI::add_question() {
    std::string id, text, answer, score;
    id = ui->id_q_lineEdit->text().toStdString();
    text = ui->text_q_lineEdit->text().toStdString();
    answer = ui->answer_q_lineEdit->text().toStdString();
    score = ui->score_q_lineEdit->text().toStdString();

    std::string name;
    std::stringstream x(this->windowTitle().toStdString());

    getline(x, name, '\n');

    if(name == "Presenter"){
        if(text.empty() || serv.find_q_id(stoi(id)) == 0 || id.empty() || answer.empty() || score.empty()){
            QMessageBox::critical(this, "error", "question with the same id already exists or empty text");
        }
        else{
            serv.add_question(stoi(id), text, answer, stoi(score));
            update();
        }
    }
}

void GUI::answer_question() {
    std::stringstream q(ui->listWidget->currentItem()->text().toStdString());

    std::string id, text, score;
    getline(q, id,';');
    getline(q, text, ';');
    getline(q,score,'\n');

    if(ui->listWidget->currentItem()->background().color() != Qt::green){
        ui->answer_pushButton->setEnabled(true);
        std::string answer = ui->answer_p_lineEdit->text().toStdString();

        std::string name;
        std::stringstream x(this->windowTitle().toStdString());

        getline(x, name, '\n');

        if(name != "Presenter"){
            int s = serv.answer_question(stoi(id), answer, name);
//            ui->answer_pushButton->setEnabled(false);
            if(s != -1){
                std::stringstream i;
                i << "Score: " << s;

                ui->score_label->setText(QString(  i.str().c_str()));
            }
            update();

        }
    }
}
