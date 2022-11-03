#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    admin_repo = new Repository();
    admin_repo->read_from_file();

    ui->setupUi(this);
    setup_connections_slots();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::setup_connections_slots() {
    QObject::connect(this->ui->admin_btn, SIGNAL(clicked()), this, SLOT(admin_form()));
    QObject::connect(this->ui->user_btn, SIGNAL(clicked()), this, SLOT(user_form()));
}

void MainForm::admin_form() {
    WatchList *user_repo = nullptr;
    if(this->ui->csvButton->isChecked())
        user_repo = new CSVWatchlist();
    if(this->ui->htmlButton->isChecked())
        user_repo = new HTMLWatchList();

    admin_repo->read_from_file();
    this->serv = new Service{*admin_repo, user_repo};
    AdminForm* a = new AdminForm{this->serv, admin_repo};
    a->show();
    a->resize(600, 400);
}

void MainForm::user_form() {
    WatchList *user_repo = nullptr;
    std::string type;
    if(this->ui->csvButton->isChecked()){
        user_repo = new CSVWatchlist();
        type = "csv";
    }

    if(this->ui->htmlButton->isChecked()) {
        user_repo = new HTMLWatchList();
        type = "html";
    }



    admin_repo->read_from_file();
    this->serv = new Service{*admin_repo, user_repo};

    UserForm* u = new UserForm{this->serv, user_repo, type};
    u->show();
    u->resize(600, 400);
}
